-- Oscilloscope modes
local OSC_NONE = 0
local OSC_QEP = 1
local OSC_RAW_1 = 2
local OSC_IIR_1 = 3
local OSC_FIR_1 = 4
local OSC_RAW_2 = 5
local OSC_IIR_2 = 6
local OSC_FIR_2 = 7
local OSC_FFT = 8

-- Channel names
local CHANNEL_NAMES = {"QEP", "RAW1", "IIR1", "FIR1", "RAW2", "IIR2", "FIR2", "FFT"}

-- Indicator settings
local INDICATOR_ITEM_HEIGHT = 24
local INDICATOR_TIME = 3000
local INDICATOR_DELAY = 1000

-- Scale tables
local VERT_SCALE_TABLE = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400}
local HORZ_SCALE_TABLE = {1.0, 2.0, 4.0, 10.0, 20.0, 40.0, 100.0, 200.0, 1000.0, 2000.0, 4000.0}

-- Horizontal scroll constants
local NUM_SAMPLES_QEP = 29239
local NUM_SAMPLES_ANALOG = 4873
local HORZ_SCROLL_SPEED = 0.2
local HORZ_SCROLL_TIME = 29

oscilloscopeActive = false
local mainMenuLoaded = false
local channel1, channel2
local vertScale, horzScale
local vertScaleTime, horzScaleTime = 0, 0
local sampleOffset
local playing
local auto
local prevClockwise
local pressedButton, pressedIcon
local buttons, icons, smallIcons

-- Returns the icon frame index
local function getPressedIconFrame(pressed)
	local frame = pressed and 1 or 0
	if pressedButton == spritePlayUpButton then
		return playing and frame + 2 or frame
	elseif pressedButton == spritePlayDownButton then
		return auto and frame + 2 or frame
	else
		return frame
	end
end

-- Shows the oscilloscope
function showOscilloscope()
	if not oscilloscopeActive and mainMenuLoaded then
		oscilloscopeActive = true
		channel1, channel2 = OSC_FIR_1, OSC_FIR_2
		vertScale, horzScale = 0, 0
		sampleOffset = 0
		playing = true
		auto = true
		prevClockwise = balance:getIntParam("clockwise")

		balance:setVertScale(VERT_SCALE_TABLE[vertScale + 1])
		balance:setHorzScale(HORZ_SCALE_TABLE[horzScale + 1])
		balance:setSampleOffset(sampleOffset)
		balance:setPlaying(playing)
		balance:setOscMode(channel1, channel2)

		pressedButton, pressedIcon = nil, nil
		spritePlayUpIcon.frame, spritePlayDownIcon.frame = 2, 2
	end
end

-- Hides the oscilloscope
function hideOscilloscope()
	if oscilloscopeActive then
		oscilloscopeActive = false
		channel1, channel2 = OSC_NONE, OSC_NONE
		balance:setOscMode(channel1, channel2)
		balance:setParam("stop")
		balance:setIntParam("clockwise", prevClockwise)
	end
end

function onOscilloscopeInit()
end

function onOscilloscopeUpdate(delta)
	-- check the background loading status
	if not mainMenuLoaded and isMainMenuLoaded() then
		mainMenuLoaded = true
		buttons = {spriteVertScaleUpButton, spriteVertScaleDownButton, spriteHorzScaleUpButton, spriteHorzScaleDownButton,
			spriteVertScrollUpButton, spriteVertScrollDownButton, spriteHorzScrollUpButton, spriteHorzScrollDownButton,
			spritePlayUpButton, spritePlayDownButton, spriteOscStartUpButton, spriteOscStartDownButton, spriteOscStopButton, spriteOscCloseButton}
		icons = {spriteVertScaleUpIcon, spriteVertScaleDownIcon, spriteHorzScaleUpIcon, spriteHorzScaleDownIcon,
			spriteVertScrollUpIcon, spriteVertScrollDownIcon, spriteHorzScrollUpIcon, spriteHorzScrollDownIcon,
			spritePlayUpIcon, spritePlayDownIcon, spriteOscStartUpIcon, spriteOscStartDownIcon, spriteOscStopIcon, spriteOscCloseButton}
		smallIcons = {spriteOscVertScaleIcon, spriteOscHorzScaleIcon, spriteOscChannelIcon, spriteOscVertScrollIcon, spriteOscPlayIcon, spriteOscStartIcon}
	end

	-- exit if not active
	if not oscilloscopeActive then
		return
	end

	-- handle currently pressed button
	if pressedButton then
		local x, y = mouse:getPosition()
		local pressed = pressedButton:isPointInside(x, y)
		pressedButton.frame, pressedIcon.frame = pressed and 1 or 0, getPressedIconFrame(pressed)
	end

	-- process horizontal scroll
	if (pressedButton == spriteHorzScrollUpButton or pressedButton == spriteHorzScrollDownButton) and not playing then
		local numSamples = channel1 ~= OSC_QEP and NUM_SAMPLES_ANALOG or NUM_SAMPLES_QEP
		local maxSamples = numSamples * HORZ_SCROLL_TIME
		local ofs = (delta / 1000.0) * HORZ_SCROLL_SPEED * (1.0 / HORZ_SCALE_TABLE[horzScale + 1]) * numSamples
		if pressedButton == spriteHorzScrollUpButton then
			sampleOffset = clamp(sampleOffset + ofs, -maxSamples, 0)
		else
			sampleOffset = clamp(sampleOffset - ofs, -maxSamples, 0)
		end
		balance:setSampleOffset(sampleOffset)
	end

	-- background
	graphics:setBlendMode(BLEND_DISABLE)
	spriteOscBack0:draw()
	spriteOscBack1:draw()
	graphics:setBlendMode(BLEND_ALPHA)

	-- display
	spriteOscDisplay0:draw()
	spriteOscDisplay1:draw()

	-- signal
	balance:drawOscilloscope(spriteOscDisplay0.x, spriteOscDisplay0.y, spriteOscDisplay1.x + spriteOscDisplay1:getWidth(), spriteOscDisplay1.y + spriteOscDisplay1:getHeight())

	-- buttons with icons
	spriteOscCloseButtonBack:draw()
	for i, button in ipairs(buttons) do
		button:draw()
		icons[i]:draw()
	end

	-- small icons
	for i, smallIcon in ipairs(smallIcons) do
		if smallIcon == spriteOscChannelIcon and not playing then
			spriteOscHorzScrollIcon:draw()
		else
			smallIcon:draw()
		end
	end

	-- draw oscilloscope information
	if channel1 ~= OSC_QEP and channel2 ~= OSC_QEP then
		local minSample1, minSample2, maxSample1, maxSample2 = balance:getMinMaxSamples()
		fontOscilloscope:drawText(50, 50, string.format("Channel1 = %s\nMin = %d\nMax = %d\nDiff = %d", CHANNEL_NAMES[channel1], minSample1, maxSample1, maxSample1 - minSample1), 1.0, 0.0, 0.0)
		fontOscilloscope:drawText(50, 580, string.format("Channel2 = %s\nMin = %d\nMax = %d\nDiff = %d", CHANNEL_NAMES[channel2], minSample2, maxSample2, maxSample2 - minSample2), 0.0, 1.0, 0.0)
	end

	-- decrement indicator counters
	vertScaleTime = math.max(vertScaleTime - delta, 0)
	horzScaleTime = math.max(horzScaleTime - delta, 0)

	-- vertical scale indicator
	if vertScaleTime ~= 0 then
		local alpha = vertScaleTime < INDICATOR_DELAY and vertScaleTime / INDICATOR_DELAY or 1.0
		spriteVertScaleIndicatorBack.alpha = alpha
		spriteVertScaleIndicatorBack:draw()

		if vertScale ~= 0 then
			local left, top = spriteVertScaleIndicatorFront.x, spriteVertScaleIndicatorFront.y
			local width, height = spriteVertScaleIndicatorFront:getWidth(), spriteVertScaleIndicatorFront:getHeight()
			spriteVertScaleIndicatorFront.alpha = alpha
			spriteVertScaleIndicatorFront:draw(left, top + (10 - vertScale) * INDICATOR_ITEM_HEIGHT, left + width, top + height, 0, (10 - vertScale) * INDICATOR_ITEM_HEIGHT, width, height)
		end
	end

	-- horizontal scale indicator
	if horzScaleTime ~= 0 then
		local alpha = horzScaleTime < INDICATOR_DELAY and horzScaleTime / INDICATOR_DELAY or 1.0
		spriteHorzScaleIndicatorBack.alpha = alpha
		spriteHorzScaleIndicatorBack:draw()

		if horzScale ~= 0 then
			local left, top = spriteHorzScaleIndicatorFront.x, spriteHorzScaleIndicatorFront.y
			local width, height = spriteHorzScaleIndicatorFront:getWidth(), spriteHorzScaleIndicatorFront:getHeight()
			spriteHorzScaleIndicatorFront.alpha = alpha
			spriteHorzScaleIndicatorFront:draw(left, top + (10 - horzScale) * INDICATOR_ITEM_HEIGHT, left + width, top + height, 0, (10 - horzScale) * INDICATOR_ITEM_HEIGHT, width, height)
		end
	end
end

function onOscilloscopeMouseDown(x, y, key)
	-- exit if not active
	if not oscilloscopeActive then
		return false
	end

	-- check buttons
	for i, button in ipairs(buttons) do
		if button:isPointInside(x, y) then
			pressedButton, pressedIcon = button, icons[i]
			pressedButton.frame, pressedIcon.frame = 1, getPressedIconFrame(true)
			break
		end
	end

	return true
end

function onOscilloscopeMouseUp(x, y, key)
	-- exit if not active
	if not oscilloscopeActive then
		return false
	end

	-- release the pressed button if any
	if pressedButton then
		if pressedButton:isPointInside(x, y) then
			if pressedButton == spriteVertScaleUpButton then
				-- increase vertical scale
				vertScale = math.min(vertScale + 1, 10)
				vertScaleTime = INDICATOR_TIME
				balance:setVertScale(VERT_SCALE_TABLE[vertScale + 1])
			elseif pressedButton == spriteVertScaleDownButton then
				-- decrease vertical scale
				vertScale = math.max(vertScale - 1, 0)
				vertScaleTime = INDICATOR_TIME
				balance:setVertScale(VERT_SCALE_TABLE[vertScale + 1])
			elseif pressedButton == spriteHorzScaleUpButton then
				-- increase horizontal scale
				horzScale = math.min(horzScale + 1, 10)
				horzScaleTime = INDICATOR_TIME
				balance:setHorzScale(HORZ_SCALE_TABLE[horzScale + 1])
			elseif pressedButton == spriteHorzScaleDownButton then
				-- decrease horizontal scale
				horzScale = math.max(horzScale - 1, 0)
				horzScaleTime = INDICATOR_TIME
				balance:setHorzScale(HORZ_SCALE_TABLE[horzScale + 1])
			elseif pressedButton == spriteHorzScrollUpButton then
				if playing then
					-- increment channel 1
					if channel1 == OSC_QEP then
						channel1, channel2 = OSC_RAW_1, OSC_RAW_1
					elseif channel1 == OSC_FIR_2 then
						channel1, channel2 = OSC_FFT, OSC_FFT
					elseif channel1 == OSC_FFT then
						channel1, channel2 = OSC_QEP, OSC_QEP
					else
						channel1 = channel1 + 1
					end
					balance:setOscMode(channel1, channel2)
				end
			elseif pressedButton == spriteHorzScrollDownButton then
				if playing then
					-- decrement channel 1
					if channel1 == OSC_QEP then
						channel1, channel2 = OSC_FFT, OSC_FFT
					elseif channel1 == OSC_RAW_1 then
						channel1, channel2 = OSC_QEP, OSC_QEP
					elseif channel1 == OSC_FFT then
						channel1, channel2 = OSC_FIR_2, OSC_FIR_2
					else
						channel1 = channel1 - 1
					end
					balance:setOscMode(channel1, channel2)
				end
			elseif pressedButton == spriteVertScrollUpButton then
				if playing then
					-- increment channel 2
					if channel2 == OSC_QEP then
						channel1, channel2 = OSC_RAW_1, OSC_RAW_1
					elseif channel2 == OSC_FIR_2 then
						channel1, channel2 = OSC_FFT, OSC_FFT
					elseif channel2 == OSC_FFT then
						channel1, channel2 = OSC_QEP, OSC_QEP
					else
						channel2 = channel2 + 1
					end
					balance:setOscMode(channel1, channel2)
				end
			elseif pressedButton == spriteVertScrollDownButton then
				if playing then
					-- decrement channel 2
					if channel2 == OSC_QEP then
						channel1, channel2 = OSC_FFT, OSC_FFT
					elseif channel2 == OSC_RAW_1 then
						channel1, channel2 = OSC_QEP, OSC_QEP
					elseif channel2 == OSC_FFT then
						channel1, channel2 = OSC_FIR_2, OSC_FIR_2
					else
						channel2 = channel2 - 1
					end
					balance:setOscMode(channel1, channel2)
				end
			elseif pressedButton == spritePlayUpButton then
				-- toggle play/pause mode
				playing = not playing
				balance:setPlaying(playing)
				sampleOffset = 0
				balance:setSampleOffset(sampleOffset)
			elseif pressedButton == spritePlayDownButton then
				-- toggle auto/wait mode
				auto = not auto
			elseif pressedButton == spriteOscStartUpButton then
				-- start driver in clockwise direction
				balance:setIntParam("clockwise", 1)
				balance:setParam("testdrv")
			elseif pressedButton == spriteOscStartDownButton then
				-- start driver in counter-clockwise direction
				balance:setIntParam("clockwise", 0)
				balance:setParam("testdrv")
			elseif pressedButton == spriteOscStopButton then
				-- stop driver
				balance:setParam("stop")
			elseif pressedButton == spriteOscCloseButton then
				-- exit from the oscilloscope mode
				hideOscilloscope()
			end
		end
		pressedButton.frame, pressedIcon.frame = 0, getPressedIconFrame(false)
		pressedButton, pressedIcon = nil, nil
	end

	return true
end
