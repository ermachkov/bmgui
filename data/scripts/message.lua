-- Message box screen settings
local MESSAGE_FADE_DELAY = 200

-- Message types
MESSAGE_OK = 0
MESSAGE_YES_NO = 1

-- Message icons
MESSAGE_WARNING = 0
MESSAGE_ERROR = 1
MESSAGE_NO_TOUCHSCREEN = 2

local messageQueue = {}
local messageTime = 0
local pressedButton, pressedButtonText

-- Shows the message
function showMessage(text, type, icon, handler1, handler2)
	-- check if this message is already in the queue
	for i, message in ipairs(messageQueue) do
		if message.text == text then
			return
		end
	end

	-- initialize the first message
	if #messageQueue == 0 then
		messageTime = 0
		pressedButton, pressedButtonText = nil, nil
		spriteMessageIcon.frame = icon
		spriteMessageYesButton.frame, spriteMessageNoButton.frame, spriteMessageOkButton.frame = 0, 0, 0
		spriteMessageYesButtonText.frame, spriteMessageNoButtonText.frame, spriteMessageOkButtonText.frame = lang * 2, lang * 2, lang * 2
	end

	-- add message to the queue
	messageQueue[#messageQueue + 1] = {["text"] = text, ["type"] = type, ["icon"] = icon, ["handler1"] = handler1, ["handler2"] = handler2}
end

-- Hides the message
function hideMessage()
	if #messageQueue ~= 0 then
		table.remove(messageQueue, 1)
		if #messageQueue ~= 0 then
			local message = messageQueue[1]
			pressedButton, pressedButtonText = nil, nil
			spriteMessageIcon.frame = message.icon
			spriteMessageYesButton.frame, spriteMessageNoButton.frame, spriteMessageOkButton.frame = 0, 0, 0
			spriteMessageYesButtonText.frame, spriteMessageNoButtonText.frame, spriteMessageOkButtonText.frame = lang * 2, lang * 2, lang * 2
		end
	end
end

-- Returns true if message box is active
function isMessageActive()
	return #messageQueue ~= 0
end

function onMessageInit()
end

function onMessageUpdate(delta)
	-- exit if not active
	if #messageQueue == 0 then
		return
	end

	-- determine the current message
	local message = messageQueue[1]
	messageTime = math.min(messageTime + delta, MESSAGE_FADE_DELAY)

	-- handle currently pressed button
	if pressedButton then
		local x, y = mouse:getPosition()
		pressedButton.frame = pressedButton:isPointInside(x, y) and 1 or 0
		pressedButtonText.frame = pressedButton:isPointInside(x, y) and (lang * 2 + 1) or (lang * 2)
	end

	-- fade the main screen
	local alpha = messageTime / MESSAGE_FADE_DELAY
	graphics:fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 0.0, alpha * 0.75)

	-- message background
	spriteMessageBack.alpha = alpha
	spriteMessageBack:draw()

	-- buttons
	if message.type == MESSAGE_OK then
		spriteMessageOkButton.alpha = alpha
		spriteMessageOkButton:draw()
		spriteMessageOkButtonText.alpha = alpha
		spriteMessageOkButtonText:draw()
	elseif message.type == MESSAGE_YES_NO then
		spriteMessageYesButton.alpha = alpha
		spriteMessageYesButton:draw()
		spriteMessageYesButtonText.alpha = alpha
		spriteMessageYesButtonText:draw()
		spriteMessageNoButton.alpha = alpha
		spriteMessageNoButton:draw()
		spriteMessageNoButtonText.alpha = alpha
		spriteMessageNoButtonText:draw()
	end

	-- icon
	spriteMessageIcon.alpha = alpha
	spriteMessageIcon:draw()

	-- text
	fontMessageText:drawText(spriteMessageText.x, spriteMessageText.y, message.text, 0.0, 0.0, 0.0, alpha);
end

function onMessageMouseDown(x, y, key)
	-- exit if not active
	if #messageQueue == 0 then
		return false
	end

	-- determine the current message
	local message = messageQueue[1]

	-- check the buttons
	if message.type == MESSAGE_OK then
		if spriteMessageOkButton:isPointInside(x, y) then
			pressedButton, pressedButtonText = spriteMessageOkButton, spriteMessageOkButtonText
			pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
			soundKey:play()
		end
	elseif message.type == MESSAGE_YES_NO then
		if spriteMessageYesButton:isPointInside(x, y) then
			pressedButton, pressedButtonText = spriteMessageYesButton, spriteMessageYesButtonText
			pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
			soundKey:play()
		elseif spriteMessageNoButton:isPointInside(x, y) then
			pressedButton, pressedButtonText = spriteMessageNoButton, spriteMessageNoButtonText
			pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
			soundKey:play()
		end
	end

	return true
end

function onMessageMouseUp(x, y, key)
	-- exit if not active
	if #messageQueue == 0 then
		return false
	end

	-- determine the current message
	local message = messageQueue[1]

	-- release the pressed button if any
	if pressedButton then
		if pressedButton:isPointInside(x, y) then
			-- call event handler and hide message box
			if message.handler1 and (pressedButton == spriteMessageOkButton or pressedButton == spriteMessageYesButton) then
				message.handler1()
			elseif message.handler2 and pressedButton == spriteMessageNoButton then
				message.handler2()
			end
			hideMessage()
		else
			pressedButton.frame, pressedButtonText.frame = 0, lang * 2
			pressedButton, pressedButtonText = nil, nil
		end
	end

	return true
end
