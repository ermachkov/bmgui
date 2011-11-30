oscilloscopeActive = false
local mainMenuLoaded = false
local playing
local auto
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
		balance:setOscMode(1)
		playing = true
		auto = true
		pressedButton, pressedIcon = nil, nil
		spritePlayUpIcon.frame, spritePlayDownIcon.frame = 2, 2
	end
end

-- Hides the oscilloscope
function hideOscilloscope()
	if oscilloscopeActive then
		oscilloscopeActive = false
		balance:setOscMode(0)
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
			if pressedButton == spritePlayUpButton then
				playing = not playing
			elseif pressedButton == spritePlayDownButton then
				auto = not auto
			elseif pressedButton == spriteOscCloseButton then
				hideOscilloscope()
			end
		end
		pressedButton.frame, pressedIcon.frame = 0, getPressedIconFrame(false)
		pressedButton, pressedIcon = nil, nil
	end

	return true
end
