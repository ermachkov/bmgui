-- Oscilloscope modes
local OSC_NONE = 0
local OSC_QEP = 1
local OSC_RAW = 2
local OSC_FIR = 3
local OSC_IIR = 4

oscilloscopeActive = false
local mainMenuLoaded = false
local channel1, channel2
local vertScale
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
		channel1, channel2 = OSC_RAW, OSC_RAW
		vertScale = 1.0
		playing = true
		auto = true
		prevClockwise = balance:getIntParam("clockwise")

		balance:setVertScale(vertScale)
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
	end
	for i, icon in ipairs(icons) do
		icon:draw()
	end
	for i, smallIcon in ipairs(smallIcons) do
		if smallIcon == spriteOscChannelIcon and not playing then
			spriteOscHorzScrollIcon:draw()
		else
			smallIcon:draw()
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
				vertScale = vertScale * 2.0
				balance:setVertScale(vertScale)
			elseif pressedButton == spriteVertScaleDownButton then
				-- decrease vertical scale
				vertScale = vertScale / 2.0
				balance:setVertScale(vertScale)
			elseif pressedButton == spriteHorzScrollUpButton then
				-- increment channel 1
				if channel1 == OSC_QEP then
					channel1, channel2 = OSC_RAW, OSC_RAW
				elseif channel1 == OSC_IIR then
					channel1, channel2 = OSC_QEP, OSC_QEP
				else
					channel1 = channel1 + 1
				end
				balance:setOscMode(channel1, channel2)
			elseif pressedButton == spriteHorzScrollDownButton then
				-- decrement channel 1
				if channel1 == OSC_QEP then
					channel1, channel2 = OSC_IIR, OSC_IIR
				elseif channel1 == OSC_RAW then
					channel1, channel2 = OSC_QEP, OSC_QEP
				else
					channel1 = channel1 - 1
				end
				balance:setOscMode(channel1, channel2)
			elseif pressedButton == spriteVertScrollUpButton then
				-- increment channel 2
				if channel2 == OSC_QEP then
					channel1, channel2 = OSC_RAW, OSC_RAW
				elseif channel2 == OSC_IIR then
					channel1, channel2 = OSC_QEP, OSC_QEP
				else
					channel2 = channel2 + 1
				end
				balance:setOscMode(channel1, channel2)
			elseif pressedButton == spriteVertScrollDownButton then
				-- decrement channel 2
				if channel2 == OSC_QEP then
					channel1, channel2 = OSC_IIR, OSC_IIR
				elseif channel2 == OSC_RAW then
					channel1, channel2 = OSC_QEP, OSC_QEP
				else
					channel2 = channel2 - 1
				end
				balance:setOscMode(channel1, channel2)
			elseif pressedButton == spritePlayUpButton then
				-- toggle play/pause mode
				playing = not playing
				balance:setPlaying(playing)
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
