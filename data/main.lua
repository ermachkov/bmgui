local statsTime = 0
local oldTotalTime, oldIdleTime, oldBalanceTime, oldWorkTime = 0, 0, 0, 0

-- Improved version of dofile()
function include(name)
	dofile(application:getDataDirectory() .. name)
end

-- Processes balance errors
local function processErrors(newErrors, oldErrors, offset)
	for i = 0, 31 do
		local code = i + offset
		if (code < 5 or code > 7) and (code ~= 19) then
			local newErr = math.floor(newErrors / 2 ^ i) % 2 ~= 0
			local oldErr = math.floor(oldErrors / 2 ^ i) % 2 ~= 0
			if newErr then
				numErrors = numErrors + 1
			end
			if newErr and not oldErr then
				addErrorToJournal(code)
			end
		end
	end
end

function onInit()
	-- make aliases to singleton objects
	application = Application:getSingleton()
	balance = Balance:getSingleton()
	database = Database:getSingleton()
	graphics = Graphics:getSingleton()
	keyboard = Keyboard:getSingleton()
	mouse = Mouse:getSingleton()
	resourceManager = ResourceManager:getSingleton()
	resourceQueue = ResourceQueue:getSingleton()

	-- load translations
	include("i18n/en.lua")
	include("i18n/ru.lua")
	include("i18n/cn.lua")

	-- load scripts
	include("scripts/common.lua")
	include("scripts/main_screen.lua")
	include("scripts/start_screen.lua")
	include("scripts/layout_menu.lua")
	include("scripts/disk_menu.lua")
	include("scripts/keyboard.lua")
	include("scripts/balance_progress.lua")
	include("scripts/main_menu.lua")
	include("scripts/message.lua")
	include("scripts/wizard.lua")
	include("scripts/stats.lua")
	include("scripts/oscilloscope.lua")

	-- load the system profile
	profile = Profile("")

	-- configure the virtual screen
	graphics:setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT)

	-- disable vertical synchronization
	--graphics:setVSync(false)

	-- set the current language
	setLanguage(profile:getInt("language", 0))

	-- create a balance table
	database:execQuery("CREATE TABLE IF NOT EXISTS Balance(" ..
		"Time TEXT PRIMARY KEY, " ..
		"User INTEGER, " ..
		"Mode INTEGER, " ..
		"Layout INTEGER, " ..
		"Width REAL, " ..
		"Diam REAL, " ..
		"Ofs INTEGER, " ..
		"Split INTEGER, " ..
		"NumSpikes INTEGER, " ..
		"Weight1 REAL, " ..
		"Angle1 REAL, " ..
		"Weight2 REAL, " ..
		"Angle2 REAL, " ..
		"Weight3 REAL, " ..
		"Angle3 REAL, " ..
		"Result INTEGER)")
	database:closeQuery()

	-- create a time table
	database:execQuery("CREATE TABLE IF NOT EXISTS Time(" ..
		"Date TEXT PRIMARY KEY, " ..
		"TotalTime REAL, " ..
		"IdleTime REAL, " ..
		"BalanceTime REAL, " ..
		"WorkTime REAL)")
	database:closeQuery()

	-- initialize the application
	onMainScreenInit()
	onStartScreenInit()
	onLayoutMenuInit()
	onDiskMenuInit()
	onKeyboardInit()
	onBalanceProgressInit()
	onMainMenuInit()
	onWizardInit()
	onStatsInit()
	onMessageInit()
	onOscilloscopeInit()

	-- show/hide mouse
	if profile:getInt("input_dev") == 2 then
		mouse:hideCursor()
	end

	-- show the start screen
	showStartScreen()

	-- show warning if touchscreen not found
	if profile:getInt("input_dev") == 0 then
		showMessage(tr("{no_touchscreen_text}"), MESSAGE_OK, MESSAGE_NO_TOUCHSCREEN)
	end
end

function onUpdate(delta)
	-- clear screen
	graphics:clear(0.0, 0.0, 0.0)

	-- check protocol
	if protocolValid and not balance:isProtocolValid() then
		protocolValid = false
		showMessage(tr("{invalid_protocol}"), MESSAGE_OK, MESSAGE_ERROR)
	end

	-- track balance state/substate changes
	local newBalanceState, newBalanceSubstate = balance:getIntParam("state"), balance:getIntParam("substate")

	-- handle state changes
	if newBalanceState == STATE_IDLE or newBalanceState == STATE_RULER then
		hideBalanceProgress()
		hideWizard()
	elseif newBalanceState == STATE_BALANCE or (newBalanceState >= STATE_BALANCE_CAL0 and newBalanceState <= STATE_BALANCE_CAL3) then
		if newBalanceSubstate == BALANCE_IDLE then
			hideBalanceProgress()
			showWizard()
		elseif newBalanceSubstate == BALANCE_WAIT_COVER then
			hideBalanceProgress()
			hideWizard()
		elseif newBalanceSubstate >= BALANCE_START and newBalanceSubstate < BALANCE_AUTO_ROTATION then
			showBalanceProgress()
			hideWizard()
		else
			hideBalanceProgress()
			hideWizard()
		end
	elseif (newBalanceState >= STATE_RULER_CAL0 and newBalanceState <= STATE_RULER_CAL3) or (newBalanceState >= STATE_RRULER_3P_CAL0 and newBalanceState <= STATE_RRULER_D_CAL1) then
		hideBalanceProgress()
		showWizard()
	end

	-- make beeps on certain events
	if newBalanceState == STATE_IDLE and balanceState == STATE_BALANCE and balanceSubstate ~= BALANCE_WAIT_COVER and not stopPressed then
		soundBalanceSuccess:play()
	elseif newBalanceState == STATE_RULER and newBalanceSubstate == RULER_WAIT and balanceState == STATE_RULER and (balanceSubstate == RULER_MEASURE or balanceSubstate == RULER_MEASURE_L) or
		newBalanceState == STATE_RULER_CAL0 and newBalanceSubstate == RULER_WAIT and balanceState == STATE_RULER_CAL0 and (balanceSubstate == RULER_MEASURE or balanceSubstate == RULER_MEASURE_L) then
		if balance:getIntParam("mode") == MODE_ALU and balance:getIntParam("autoalu") ~= 0 then
			showAutoAluWeights()
		end
		soundRulerSuccess:play()
	end

	-- save new balance state
	balanceState, balanceSubstate = newBalanceState, newBalanceSubstate

	-- track balance errors
	if isMainMenuLoaded() then
		local newBalanceErrors0, newBalanceErrors1, newBalanceErrors2 = balance:getFloatParam("errors0"), balance:getFloatParam("errors1"), balance:getFloatParam("errors2")
		numErrors = 0
		processErrors(newBalanceErrors0, balanceErrors0, 1)
		processErrors(newBalanceErrors1, balanceErrors1, 33)
		processErrors(newBalanceErrors2, balanceErrors2, 65)
		balanceErrors0, balanceErrors1, balanceErrors2 = newBalanceErrors0, newBalanceErrors1, newBalanceErrors2
	end

	-- track balance results
	local newBalanceResult = balance:getIntParam("result")
	if newBalanceResult ~= 0 and balanceResult == 0 then
		local mode = balance:getIntParam("mode")
		local layout = unpackLayout(balance:getIntParam("layout"), mode)
		local query = string.format("INSERT INTO Balance VALUES(datetime('now', 'localtime'), %s, %d, %d, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %d)",
			balance:getParam("user"), mode, layout, balance:getParam("width"), balance:getParam("diam"), balance:getParam("offset"),
			balance:getParam("split"), balance:getParam("numsp"), balance:getParam("weight0"), balance:getParam("angle0"),
			balance:getParam("weight1"), balance:getParam("angle1"), balance:getParam("weight2"), balance:getParam("angle2"), newBalanceResult)
		database:execQuery(query)
		database:closeQuery()
	end
	balanceResult = newBalanceResult

	-- write current time
	statsTime = statsTime + delta
	if statsTime >= 120000 then
		statsTime = 0
		local newTotalTime, newIdleTime, newBalanceTime, newWorkTime = balance:getIntParam("totaltime"), balance:getIntParam("idletime"), balance:getIntParam("balancetime"), balance:getIntParam("worktime")

		local date = os.date("%Y-%m-%d")
		database:execQuery(string.format("SELECT * FROM Time WHERE Date = '%s'", date))
		if database:nextRow() then
			local totalTime, idleTime, balanceTime, workTime = database:getFloat("TotalTime"), database:getFloat("IdleTime"), database:getFloat("BalanceTime"), database:getFloat("WorkTime")
			totalTime, idleTime, balanceTime, workTime = totalTime + sub32(newTotalTime, oldTotalTime) / 1000.0, idleTime + sub32(newIdleTime, oldIdleTime) / 1000.0, balanceTime + sub32(newBalanceTime, oldBalanceTime) / 1000.0, workTime + sub32(newWorkTime, oldWorkTime) / 1000.0
			database:closeQuery()
			database:execQuery(string.format("UPDATE Time SET TotalTime = %f, IdleTime = %f, BalanceTime = %f, WorkTime = %f WHERE Date = '%s'", totalTime, idleTime, balanceTime, workTime, date))
		else
			local totalTime, idleTime, balanceTime, workTime = sub32(newTotalTime, oldTotalTime) / 1000.0, sub32(newIdleTime, oldIdleTime) / 1000.0, sub32(newBalanceTime, oldBalanceTime) / 1000.0, sub32(newWorkTime, oldWorkTime) / 1000.0
			database:closeQuery()
			database:execQuery(string.format("INSERT INTO Time VALUES('%s', %f, %f, %f, %f)", date, totalTime, idleTime, balanceTime, workTime))
		end
		database:closeQuery()

		oldTotalTime, oldIdleTime, oldBalanceTime, oldWorkTime = newTotalTime, newIdleTime, newBalanceTime, newWorkTime
	end

	-- update modules
	onMainScreenUpdate(delta)
	onStartScreenUpdate(delta)
	onOscilloscopeUpdate(delta)
	onLayoutMenuUpdate(delta)
	onDiskMenuUpdate(delta)
	onBalanceProgressUpdate(delta)
	onMainMenuUpdate(delta)
	onKeyboardUpdate(delta)
	onWizardUpdate(delta)
	onStatsUpdate(delta)
	onMessageUpdate(delta)

	-- show current FPS
	--fontSizes:drawText(30, 30, string.format("FPS = %.2f", graphics:getFPS()), 0, 0, 0)
end

function onMouseDown(x, y, key)
	-- ignore all mouse buttons except the left one
	if key ~= MOUSE_LEFT then
		return
	end

	-- set the mouse pressed flag
	mousePressed = true

	-- dispatch the event
	if not onMessageMouseDown(x, y, key) then
		if not onWizardMouseDown(x, y, key) then
			if not onStatsMouseDown(x, y, key) then
				if not onKeyboardMouseDown(x, y, key) then
					if not onMainMenuMouseDown(x, y, key) then
						if not onBalanceProgressMouseDown(x, y, key) then
							if not onDiskMenuMouseDown(x, y, key) then
								if not onLayoutMenuMouseDown(x, y, key) then
									if not onStartScreenMouseDown(x, y, key) then
										if not onOscilloscopeMouseDown(x, y, key) then
											onMainScreenMouseDown(x, y, key)
										end
									end
								end
							end
						end
					end
				end
			end
		end
	end
end

function onMouseUp(x, y, key)
	-- ignore all mouse buttons except the left one
	if key ~= MOUSE_LEFT then
		return
	end

	-- clear the mouse pressed flag
	mousePressed = false

	-- dispatch the event
	if not onMessageMouseUp(x, y, key) then
		if not onWizardMouseUp(x, y, key) then
			if not onStatsMouseUp(x, y, key) then
				if not onKeyboardMouseUp(x, y, key) then
					if not onMainMenuMouseUp(x, y, key) then
						if not onBalanceProgressMouseUp(x, y, key) then
							if not onDiskMenuMouseUp(x, y, key) then
								if not onLayoutMenuMouseUp(x, y, key) then
									if not onStartScreenMouseUp(x, y, key) then
										if not onOscilloscopeMouseUp(x, y, key) then
											onMainScreenMouseUp(x, y, key)
										end
									end
								end
							end
						end
					end
				end
			end
		end
	end
end

-- start the game engine if running under external Lua interpreter
if not Application then
	local dataDir = arg[0]:match("^.*[\\/]") or "./"
	GAME_COMMAND_LINE = "-d \"" .. dataDir .. "\""
	require("Balance")
end
