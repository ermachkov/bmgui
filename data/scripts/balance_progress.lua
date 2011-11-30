-- Balance progress screen settings
local BALANCE_PROGRESS_FADE_DELAY = 200

local balanceProgressActive = false
local balanceProgressTime = 0
local balanceFreq
local balanceTime
local accelTime
local measureTime
local balanceProgress

stopPressed = false

-- Shows the balance progress
function showBalanceProgress()
	if not balanceProgressActive then
		-- close all active menus
		genMouseUp()
		hideLayoutMenu()
		hideDiskMenu()
		hideMainMenu()
		hideKeyboard()
		hideStats()

		-- initialize the balance progress bar
		balanceProgressActive = true
		balanceFreq = balance:getFloatParam("drvfreq") / balance:getFloatParam("freqcoeff")
		balanceTime = 0.0
		accelTime = 0.0
		measureTime = balance:getIntParam("maxrot") / balanceFreq
		balanceProgress = 0.0
		stopPressed = false
	end
end

-- Hides the balance progress
function hideBalanceProgress()
	balanceProgressActive = false
end

function onBalanceProgressInit()
	-- set speedometer center hotspot
	local center = spriteSpeedometerCenter
	local hx, hy = center:getWidth() / 2, center:getHeight() / 2
	center.x, center.y = center.x + hx, center.y + hy
	center:setHotSpot(hx, hy)

	-- set speedometer arrow hotspot
	local arrow = spriteSpeedometerArrow
	hx, hy = center.x - arrow.x, center.y - arrow.y
	arrow.x, arrow.y = center.x, center.y
	arrow:setHotSpot(hx, hy)
end

function onBalanceProgressUpdate(delta)
	-- check the balance progress screen state
	if balanceProgressActive then
		balanceProgressTime = math.min(balanceProgressTime + delta, BALANCE_PROGRESS_FADE_DELAY)
	elseif balanceProgressTime > 0 then
		balanceProgressTime = math.max(balanceProgressTime - delta, 0)
	else
		return
	end

	-- update the balance progress
	local currFreq = balance:getIntParam("wheelspeed") * 10.0 / NUM_ANGLES
	if balance:getIntParam("testmode") == 0 then
		if stopPressed then
			balanceProgress = 0.0
		elseif balanceSubstate >= BALANCE_START and balanceSubstate < BALANCE_DECEL then
			-- increment the elapsed time
			balanceTime = balanceTime + delta / 1000.0

			-- estimate the acceleration time
			if balanceSubstate < BALANCE_MEASURE and currFreq > 0.01 then
				accelTime = balanceTime * balanceFreq / currFreq
			end

			-- estimate the balance progress
			local progress = balanceTime / (accelTime + measureTime)
			balanceProgress = clamp(progress, balanceProgress, 1.0)
		elseif balanceSubstate >= BALANCE_DECEL then
			balanceProgress = 1.0
		end
	end

	-- fade the main screen
	local alpha = balanceProgressTime / BALANCE_PROGRESS_FADE_DELAY
	graphics:fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 0.0, alpha * 0.75)

	-- progress bar
	spriteProgressBack.alpha = alpha
	spriteProgressBack:draw()
	local sprite = spriteProgressFront
	local width, height = sprite:getWidth() * balanceProgress, sprite:getHeight()
	sprite.alpha = alpha
	sprite:draw(sprite.x, sprite.y, sprite.x + width, sprite.y + height, 0, 0, width, height)

	-- text
	if balanceState == STATE_BALANCE then
		if balance:getIntParam("testmode") == 0 then
			spriteProgressText.alpha = alpha
			spriteProgressText:draw()
		else
			fontSizes:drawText(spriteProgressText.x, spriteProgressText.y, tr("{test_progress_text}"), 1.0, 1.0, 1.0, alpha)
		end
	elseif balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3 then
		fontSizes:drawText(spriteProgressText.x, spriteProgressText.y, tr("{cal_progress_text}"), 1.0, 1.0, 1.0, alpha)
	end

	-- speedometer
	local angle = math.max(currFreq / balanceFreq * 1.5 * math.pi, 0)
	spriteSpeedometerText.alpha = alpha
	spriteSpeedometerText:draw()
	spriteSpeedometerArrow.angle = angle
	spriteSpeedometerArrow.alpha = alpha
	spriteSpeedometerArrow:draw()
	spriteSpeedometerCenter.angle = angle
	spriteSpeedometerCenter.alpha = alpha
	spriteSpeedometerCenter:draw()
	drawCenteredText(fontSpeedometer, spriteSpeedometerSpeed, tostring(math.max(math.floor(currFreq * 60.0), 0)), 92 / 255, 99 / 255, 105 / 255)

	-- weights
	if balanceSubstate > BALANCE_MEASURE then
		spriteLeftWeight:draw()
		drawCenteredText(fontWeights, spriteLeftWeight, formatNumber(balance:getIntParam("rndweight0")), 0.0, 0.0, 0.0)
		spriteRightWeight:draw()
		drawCenteredText(fontWeights, spriteRightWeight, formatNumber(balance:getIntParam("rndweight1")), 0.0, 0.0, 0.0)
	end

	-- stop button
	spriteStopButton:draw()
	spriteStopButtonText:draw()
end

function onBalanceProgressMouseDown(x, y, key)
	-- exit if not active
	if not balanceProgressActive then
		return false
	end

	-- pass stop button events to the main screen
	if spriteStopButton:isPointInside(x, y) then
		stopPressed = true
		return false
	end

	return true
end

function onBalanceProgressMouseUp(x, y, key)
	-- pass all release events to the main screen
	return false
end
