-- Stats screen settings
local STATS_FADE_DELAY = 200

-- Number of days in months
local MONTHS = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}

-- Maximum values table
local MAX_VALUES = {{10, 5}, {12, 6}, {15, 5}, {18, 6}, {20, 4}, {30, 6}, {40, 4}, {50, 5}, {60, 6}, {80, 4}, {90, 6}}

-- Inches range
local MIN_INCHES = 12
local MAX_INCHES = 24

local statsActive = false
local statsTime = 0
local statsMode, statsSubmode
local pressedButton
local day, month, year
local currMonth, currYear
local currDate = {}
local statsTitles, statsModes, monthNames
local stats = {}
local counters = {}
local numValues
local maxValue, numMarkers

-- Finds the nearest maximum value
local function findMaxValue(value)
	local scale = 1
	while true do
		for i, pair in ipairs(MAX_VALUES) do
			if value <= pair[1] * scale then
				return pair[1] * scale, pair[2]
			end
		end
		scale = scale * 10
	end
end

-- Updates the statistics
local function updateStats()
	if statsMode == STATS_DISKS or statsMode == STATS_WEIGHTS or statsMode == STATS_TIME then
		-- calculate current number of days
		if currMonth == month and currYear == year then
			numValues = day
		elseif currMonth == 2 and currYear % 4 == 0 then
			numValues = 29
		else
			numValues = MONTHS[currMonth]
		end

		-- initialize counters
		for i = 1, numValues do
			counters[i] = 0
		end

		-- perform SQL query
		if statsMode == STATS_DISKS then
			local query = string.format("SELECT * FROM Balance WHERE (Time BETWEEN '%04d-%02d-01 00:00:00' AND '%04d-%02d-%02d 23:59:59') AND (Result = 1)", currYear, currMonth, currYear, currMonth, numValues)
			if statsSubmode == 1 then
				query = query .. " AND (Mode = 0)"
			elseif statsSubmode == 2 then
				query = query .. " AND (Mode = 1)"
			end
			database:execQuery(query)

			while database:nextRow() do
				local date = database:getString("Time")
				local day = tonumber(date:sub(9, 10))
				counters[day] = counters[day] + 1
			end
		elseif statsMode == STATS_WEIGHTS then
		else
			database:execQuery(string.format("SELECT * FROM Time WHERE (Date BETWEEN '%04d-%02d-01' AND '%04d-%02d-%02d')", currYear, currMonth, currYear, currMonth, numValues))
			while database:nextRow() do
				local date = database:getString("Date")
				local day = tonumber(date:sub(9, 10))
				if statsSubmode == 0 then
					counters[day] = counters[day] + database:getFloat("TotalTime")
				elseif statsSubmode == 1 then
					counters[day] = counters[day] + database:getFloat("BalanceTime") + database:getFloat("WorkTime")
				else
					counters[day] = counters[day] + database:getFloat("IdleTime")
				end
			end
		end

		database:closeQuery()

		-- find the maximum value
		local maxCount = 0
		for i = 1, numValues do
			if counters[i] > maxCount then
				maxCount = counters[i]
			end
		end
		maxValue, numMarkers = findMaxValue(maxCount)

		-- fill the current statistics
		for i = 1, numValues do
			-- determine the value
			stats[i].text = tostring(i)
			stats[i].value = counters[i] / maxValue

			-- determine the weekend
			currDate.day, currDate.month, currDate.year = i, currMonth, currYear
			local date = os.date("*t", os.time(currDate))
			stats[i].weekend = date.wday == 1 or date.wday == 7
		end
	else
		-- determine the number of inches
		numValues = MAX_INCHES - MIN_INCHES + 1

		-- initialize counters
		for i = 1, numValues do
			counters[i] = 0
		end

		-- perform SQL query
		local query = string.format("SELECT * FROM Balance WHERE (Time BETWEEN '%04d-%02d-01 00:00:00' AND '%04d-%02d-31 23:59:59') AND (Result = 1)", currYear, currMonth, currYear, currMonth)
		if statsSubmode == 1 then
			query = query .. " AND (Mode = 0)"
		elseif statsSubmode == 2 then
			query = query .. " AND (Mode = 1)"
		end
		database:execQuery(query)

		while database:nextRow() do
			local diam = database:getFloat("Diam")
			local index = clamp(math.floor(diam + 0.5) - MIN_INCHES + 1, 1, numValues)
			counters[index] = counters[index] + 1
		end

		database:closeQuery()

		-- find the maximum value
		local maxCount = 0
		for i = 1, numValues do
			if counters[i] > maxCount then
				maxCount = counters[i]
			end
		end
		maxValue, numMarkers = findMaxValue(maxCount)

		-- set up inches
		for i = 1, numValues do
			stats[i].text = tostring(i + MIN_INCHES - 1)
			stats[i].value = counters[i] / maxValue
			stats[i].weekend = false
		end
	end
end

-- Returns true if the stats window is active
function isStatsActive()
	return statsActive
end

-- Shows the stats
function showStats(mode)
	if not statsActive and isMainMenuLoaded() then
		statsActive = true
		statsMode, statsSubmode = mode, 0
		pressedButton = nil
		local date = os.date("*t")
		day, month, year = date.day, date.month, date.year
		currMonth, currYear = month, year

		spriteStatsCloseButton.frame = 0

		updateStats()
	end
end

-- Hides the stats
function hideStats()
	statsActive = false
	statsTime = 0 -- TODO: Remove me when alpha in fonts will be fixed
end

function onStatsInit()
	enableTranslation(false)
	statsTitles = {tr("{stats_disks_title}"), tr("{stats_inches_title}"), tr("{stats_weights_title}"), tr("{stats_time_title}")}
	statsModes = {{tr("{stats_disks_all}"), tr("{stats_disks_alu}"), tr("{stats_disks_steel}")},
		{tr("{stats_inches_all}"), tr("{stats_inches_alu}"), tr("{stats_inches_steel}")},
		{tr("{stats_weights_all}"), tr("{stats_weights_clip}"), tr("{stats_weights_stick}")},
		{tr("{stats_time_total}"), tr("{stats_time_work}"), tr("{stats_time_idle}")}}
	monthNames = {tr("JANUARY"), tr("FEBRUARY"), tr("MARCH"), tr("APRIL"), tr("MAY"), tr("JUNE"), tr("JULY"), tr("AUGUST"), tr("SEPTEMBER"), tr("OCTOBER"), tr("NOVEMBER"), tr("DECEMBER")}
	enableTranslation(true)

	for i = 1, 31 do
		stats[i] = {}
	end
end

function onStatsUpdate(delta)
	-- check the stats state
	if statsActive then
		statsTime = math.min(statsTime + delta, STATS_FADE_DELAY)
	elseif statsTime > 0 then
		statsTime = math.max(statsTime - delta, 0)
	else
		return
	end

	-- handle currently pressed button
	if pressedButton then
		local x, y = mouse:getPosition()
		pressedButton.frame = pressedButton:isPointInside(x, y) and 1 or 0
	end

	-- fade the main screen
	local alpha = statsTime / STATS_FADE_DELAY
	graphics:fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 0.0, alpha * 0.75)

	-- stats background
	spriteStatsBack0.alpha = alpha
	spriteStatsBack1.alpha = alpha
	spriteStatsBack0:draw()
	spriteStatsBack1:draw()

	-- text
	drawHorzCenteredText(fontStatsHeader, spriteStatsHeader, tr(statsTitles[statsMode + 1]), 110 / 255, 110 / 255, 110 / 255)
	drawHorzCenteredText(fontStatsMonth, spriteStatsMonth, tr(monthNames[currMonth]), 80 / 255, 80 / 255, 80 / 255)
	drawHorzCenteredText(fontStatsMonth, spriteStatsYear, tostring(currYear), 80 / 255, 80 / 255, 80 / 255)

	-- X axis and bars
	local bar, step
	if statsMode == STATS_DISKS or statsMode == STATS_WEIGHTS or statsMode == STATS_TIME then
		bar = spriteStatsBar1
		step = (spriteStatsBar31.x - spriteStatsBar1.x) / 30
	else
		bar = spriteStatsBar1Thick
		step = (spriteStatsBar13Thick.x - spriteStatsBar1Thick.x) / (numValues - 1)
	end
	local left = bar.x
	for i = 1, numValues do
		-- bar
		local value = 1.0 - stats[i].value
		local barWidth, barHeight = bar:getWidth(), bar:getHeight()
		bar:draw(left, bar.y + value * barHeight, left + barWidth, bar.y + barHeight, 0, value * barHeight, barWidth, barHeight)

		-- text
		local text = stats[i].text
		local textWidth, textHeight = fontStatsAxis:getTextSize(text)
		if stats[i].weekend then
			fontStatsAxis:drawText(left + (bar:getWidth() - textWidth) / 2, spriteStatsTextX1.y + (spriteStatsTextX1:getHeight() - textHeight) / 2, text, 1.0, 0.0, 0.0)
		else
			fontStatsAxis:drawText(left + (bar:getWidth() - textWidth) / 2, spriteStatsTextX1.y + (spriteStatsTextX1:getHeight() - textHeight) / 2, text, 0.0, 0.0, 0.0)
		end

		-- increment bar coordinate
		left = left + step
	end

	-- Y axis
	local step = (spriteStatsBar1.y + spriteStatsBar1:getHeight() - spriteStatsTextYLast.y) / numMarkers
	local top = spriteStatsBar1.y + spriteStatsBar1:getHeight() - step
	for i = 1, numMarkers do
		local text = tostring(i * maxValue / numMarkers)
		local textWidth, textHeight = fontStatsAxis:getTextSize(text)
		fontStatsAxis:drawText(spriteStatsTextY1.x + (spriteStatsTextY1:getWidth() - textWidth) / 2, top, text, 1.0, 1.0, 1.0)
		top = top - step
	end

	-- buttons
	spriteStatsSelectButton.alpha = alpha
	spriteStatsSelectButton:draw()
	spriteStatsPrevButton.alpha = alpha
	spriteStatsPrevButton:draw()
	spriteStatsNextButton.alpha = alpha
	spriteStatsNextButton:draw()
	spriteStatsCloseButton.alpha = alpha
	spriteStatsCloseButton:draw()

	-- submode
	drawCenteredText(fontStatsMode, spriteStatsSelectButton, tr(statsModes[statsMode + 1][statsSubmode + 1]), 1.0, 1.0, 1.0)
end

function onStatsMouseDown(x, y, key)
	-- exit if not active
	if not statsActive then
		return false
	end

	-- check stats buttons
	if spriteStatsSelectButton:isPointInside(x, y) then
		pressedButton = spriteStatsSelectButton
		pressedButton.frame = 1
		soundKey:play()
	elseif spriteStatsPrevButton:isPointInside(x, y) then
		pressedButton = spriteStatsPrevButton
		pressedButton.frame = 1
		soundKey:play()
	elseif spriteStatsNextButton:isPointInside(x, y) then
		pressedButton = spriteStatsNextButton
		pressedButton.frame = 1
		soundKey:play()
	elseif spriteStatsCloseButton:isPointInside(x, y) then
		pressedButton = spriteStatsCloseButton
		pressedButton.frame = 1
		soundKey:play()
	end

	return true
end

function onStatsMouseUp(x, y, key)
	-- exit if not active
	if not statsActive then
		return false
	end

	-- release the pressed button if any
	if pressedButton then
		-- check pressed buttons
		if pressedButton:isPointInside(x, y) then
			if pressedButton == spriteStatsSelectButton then
				-- increment submode
				statsSubmode = statsSubmode + 1
				if statsSubmode > 2 then
					statsSubmode = 0
				end
				updateStats()
			elseif pressedButton == spriteStatsPrevButton then
				-- decrement current month
				if currYear > 2010 or currMonth > 1 then
					currMonth = currMonth - 1
					if currMonth < 1 then
						currMonth = 12
						currYear = currYear - 1
					end
					updateStats()
				end
			elseif pressedButton == spriteStatsNextButton then
				-- increment current month
				if currYear < year or currMonth < month then
					currMonth = currMonth + 1
					if currMonth > 12 then
						currMonth = 1
						currYear = currYear + 1
					end
					updateStats()
				end
			elseif pressedButton == spriteStatsCloseButton then
				hideStats()
			end
		end

		pressedButton.frame = 0
		pressedButton = nil
	end

	return true
end
