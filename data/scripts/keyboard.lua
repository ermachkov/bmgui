-- Keyboard settings
local ANIM_DELAY = 200
local MAX_DIGITS = 3

local keyboardActive = false
local keyboardTime = 0
local keyboardParam
local keyboardValue
local startX, startY
local endX, endY
local currType
local currFasteners
local currItem
local currHandler
local firstPress
local numPoints
local pressedKey, pressedKeyText
local keys, keyTexts

-- Returns the current keyboard value
local function getKeyboardValue()
	if currType == TYPE_INT or currType == TYPE_FLOAT then
		keyboardValue = formatNumber(balance:getFloatParam(keyboardParam))
	elseif currType == TYPE_IP then
		keyboardValue = profile:getString(keyboardParam)
	elseif currType == TYPE_PASSWORD then
		keyboardValue = "0"
	end
end

-- Sets the keyboard value
local function setKeyboardValue()
	-- save the entered value
	if currType == TYPE_INT or currType == TYPE_FLOAT then
		balance:setParam(keyboardParam, keyboardValue)
	elseif currType == TYPE_IP then
		-- normalize IP adress
		if keyboardValue:sub(-1) == "." then
			keyboardValue = keyboardValue .. "0"
		end
		while getNumChars(keyboardValue, ".") < 3 do
			keyboardValue = keyboardValue .. ".0"
		end

		-- save IP address
		profile:setString(keyboardParam, keyboardValue)
		profile:save()
		if keyboardParam == "server_addr" then
			balance:setServerAddr(keyboardValue)
		end
	end

	-- call the enter handler
	if currHandler then
		currHandler(keyboardValue)
	end
end

-- Shows the keyboard
function showKeyboard(x, y, x0, y0, param, type, fasteners, item, handler)
	if not keyboardActive then
		keyboardActive = true
		keyboardTime = 0
		keyboardParam = param
		startX, startY = x0, y0
		endX, endY = x, y
		currType = type
		currFasteners = fasteners
		currItem = item
		currHandler = handler
		firstPress = true
		getKeyboardValue()
		numPoints = getNumChars(keyboardValue, ".")
		pressedKey, pressedKeyText = nil, nil
	end
end

-- Hides the keyboard
function hideKeyboard()
	keyboardActive = false
	currItem = nil
end

-- Handles Enter key
local function onEnterKeyPress()
	hideKeyboard()
	spriteKeyEnter.frame, spriteKeyEnterText.frame = 0, 0
	setKeyboardValue()
end

-- Handles Backspace key
local function onBackspaceKeyPress()
	firstPress = false
	if #keyboardValue > 1 then
		if keyboardValue:sub(-1) == "." then
			numPoints = numPoints - 1
		end
		keyboardValue = keyboardValue:sub(1, -2)
	else
		keyboardValue = "0"
		numPoints = 0
	end
end

-- Handles Clear key
local function onClearKeyPress()
	firstPress = true
	getKeyboardValue()
	numPoints = getNumChars(keyboardValue, ".")
end

-- Handles Point key
local function onPointKeyPress()
	if currType == TYPE_FLOAT then
		if firstPress then
			firstPress = false
			keyboardValue = "0."
			numPoints = 1
		elseif numPoints == 0 and #keyboardValue < MAX_DIGITS then
			keyboardValue = keyboardValue .. "."
			numPoints = 1
		end
	elseif currType == TYPE_IP then
		if firstPress then
			firstPress = false
			keyboardValue = "0."
			numPoints = 1
		elseif numPoints < 3 and keyboardValue:sub(-1) ~= "." then
			keyboardValue = keyboardValue .. "."
			numPoints = numPoints + 1
		end
	end
end

-- Handles numeric keys
local function onNumericKeyPress(digit)
	if firstPress then
		firstPress = false
		keyboardValue = digit
		numPoints = 0
	elseif keyboardValue ~= "0" then
		if currType ~= TYPE_IP then
			if #keyboardValue < MAX_DIGITS + numPoints then
				keyboardValue = keyboardValue .. digit
			end
		else
			local index = keyboardValue:find("%.", -3)
			if #keyboardValue < 3 or index then
				local str = index and keyboardValue:sub(index + 1) or keyboardValue
				if tonumber(str .. digit) < 256 then
					keyboardValue = keyboardValue .. digit
				end
			end
		end
	else
		keyboardValue = digit
		numPoints = 0
	end
end

-- Returns true if keyboard is active
function isKeyboardActive()
	return keyboardActive
end

function onKeyboardInit()
	-- initialize sprite tables
	keys = {spriteKey0, spriteKey1, spriteKey2, spriteKey3, spriteKey4, spriteKey5, spriteKey6, spriteKey7, spriteKey8, spriteKey9,
		spriteKeyPoint, spriteKeyEnter, spriteKeyBackspace, spriteKeyClear}
	keyTexts = {spriteKey0Text, spriteKey1Text, spriteKey2Text, spriteKey3Text, spriteKey4Text, spriteKey5Text, spriteKey6Text, spriteKey7Text, spriteKey8Text, spriteKey9Text,
		spriteKeyPointText, spriteKeyEnterText, spriteKeyBackspaceText, spriteKeyClearText}
end

function onKeyboardUpdate(delta)
	-- check the keyboard state
	if keyboardActive then
		keyboardTime = math.min(keyboardTime + delta, ANIM_DELAY)
	elseif keyboardTime > 0 then
		keyboardTime = math.max(keyboardTime - delta, 0)
	else
		return
	end

	-- determine the keyboard position
	local coeff = keyboardTime / ANIM_DELAY
	local posX, posY = startX + coeff * (endX - startX), startY + coeff * (endY - startY)

	-- handle currently pressed key
	if pressedKey then
		local x, y = mouse:getPosition()
		x, y = x - posX, y - posY
		local frame = pressedKey:isPointInside(x, y) and 1 or 0
		pressedKey.frame, pressedKeyText.frame = frame, frame
	end

	-- fade the main screen
	graphics:fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 0.0, coeff * 0.75)

	-- highlight the editing element
	if currItem then
		-- draw the selected menu item
		drawMenuItem(currItem, ITEM_NORMAL, 1.0)
	elseif currType == TYPE_INT or currType == TYPE_FLOAT then
		-- draw the selected size
		local text = formatNumber(balance:getFloatParam(keyboardParam == "stick" and "realstick" or keyboardParam))
		if keyboardParam == "width" or keyboardParam == "stick" then
			spriteWidthStickBack:draw()
			if keyboardParam == "stick" then
				spriteStickIcon.frame, spriteWidthStickButton.frame = 1, 1
				drawVertSplittedSprite(spriteStickIcon, spriteWidthStickButton)
			else
				spriteWidthIcon.frame, spriteWidthStickButton.frame = 1, 1
				drawVertSplittedSprite(spriteWidthIcon, spriteWidthStickButton)
			end
			drawCenteredText(fontSizes, spriteWidthStickButton, text, 0.0, 0.0, 0.0)
		elseif keyboardParam == "diam" then
			spriteDiamBack:draw()
			spriteDiamButton.frame, spriteDiamIcon.frame = 1, 1
			drawVertSplittedSprite(spriteDiamButton, spriteDiamIcon)
			drawCenteredText(fontSizes, spriteDiamButton, text, 0.0, 0.0, 0.0)
		elseif keyboardParam == "offset" then
			spriteOfsBack:draw()
			spriteOfsButton.frame, spriteOfsIcon.frame = 1, 1
			drawVertSplittedSprite(spriteOfsButton, spriteOfsIcon)
			drawCenteredText(fontSizes, spriteOfsButton, text, 0.0, 0.0, 0.0)
		end
	end

	-- keyboard background
	spriteKeyboardBack:draw(posX + spriteKeyboardBack.x, posY + spriteKeyboardBack.y)

	-- keys and labels
	for i, key in ipairs(keys) do
		key:draw(posX + key.x, posY + key.y)
	end
	for i, text in ipairs(keyTexts) do
		text:draw(posX + text.x, posY + text.y)
	end

	-- display
	local display = currType ~= TYPE_PASSWORD and spriteKeyboardDisplay or spriteKeyboardDisplayPassword
	display:draw(posX + display.x, posY + display.y)

	-- text
	if currType == TYPE_PASSWORD and firstPress then
		local text = tr("Enter password")
		local width, height = fontSizes:getTextSize(text)
		fontSizes:drawText(posX + spriteKeyboardDisplayBack.x + (spriteKeyboardDisplayBack:getWidth() - width) / 2,
			posY + spriteKeyboardDisplayBack.y + (spriteKeyboardDisplayBack:getHeight() - height) / 2, text, 219 / 255, 0.0, 0.0)
	else
		-- format the text string
		local clipX = posX + spriteKeyboardDisplayBack.x
		local clipY = posY + spriteKeyboardDisplayBack.y
		local numZeros = 8 + numPoints - #keyboardValue
		local text = (numZeros > 0 and string.rep("0", numZeros) .. keyboardValue or keyboardValue):gsub("%d", "0")
		local width, height = fontKeyboardDisplay:getTextSize(text)
		local right = clipX + spriteKeyboardDisplayBack:getWidth()
		local top = clipY + (spriteKeyboardDisplayBack:getHeight() - height) / 2

		-- display text
		graphics:setClipRect(clipX, clipY, clipX + spriteKeyboardDisplayBack:getWidth(), clipY + spriteKeyboardDisplayBack:getHeight())
		if currType ~= TYPE_PASSWORD then
			fontKeyboardDisplay:drawText(right - width, top, text, 171 / 255, 206 / 255, 223 / 255)
		else
			fontKeyboardDisplay:drawText(right - width, top, text, 52 / 255, 28 / 255, 30 / 255)
		end
		width, height = fontKeyboardDisplay:getTextSize(keyboardValue)
		if currType ~= TYPE_PASSWORD then
			fontKeyboardDisplay:drawText(right - width, top, keyboardValue, 95 / 255, 136 / 255, 160 / 255)
		else
			fontKeyboardDisplay:drawText(right - width, top, keyboardValue, 219 / 255, 0.0, 0.0)
		end
		graphics:resetClipRect()
	end

	-- fasteners
	currFasteners:draw(posX + currFasteners.x, posY + currFasteners.y)
end

function onKeyboardMouseDown(x, y, key)
	-- exit if not active
	if not keyboardActive then
		return false
	end

	-- adjust the mouse coordinates
	x, y = x - endX, y - endY

	-- check the keyboard
	if spriteKeyboardBack:isPointInside(x, y) then
		-- test all keys
		for i, key in ipairs(keys) do
			if key:isPointInside(x, y) then
				pressedKey, pressedKeyText = key, keyTexts[i]
				pressedKey.frame, pressedKeyText.frame = 1, 1
				soundKey:play()
				break
			end
		end
	elseif not currFasteners:isPointInside(x, y) then
		-- hide the keyboard
		x, y = x + endX, y + endY
		hideKeyboard()
		if spriteWidthIcon:isPointInside(x, y) or spriteWidthStickButton:isPointInside(x, y) or
			spriteDiamIcon:isPointInside(x, y) or spriteDiamButton:isPointInside(x, y) or
			spriteOfsIcon:isPointInside(x, y) or spriteOfsButton:isPointInside(x, y) then
			soundKey:play()
		end
	end

	return true
end

function onKeyboardMouseUp(x, y, key)
	-- exit if not active
	if not keyboardActive then
		return false
	end

	-- adjust the mouse coordinates
	x, y = x - endX, y - endY

	-- release the pressed key if any
	if pressedKey then
		-- handle key press
		if pressedKey:isPointInside(x, y) then
			if pressedKey == spriteKeyEnter then
				onEnterKeyPress()
			elseif pressedKey == spriteKeyBackspace then
				onBackspaceKeyPress()
			elseif pressedKey == spriteKeyClear then
				onClearKeyPress()
			elseif pressedKey == spriteKeyPoint then
				onPointKeyPress()
			else
				for i, key in ipairs(keys) do
					if key == pressedKey then
						onNumericKeyPress(tostring(i - 1))
						break
					end
				end
			end
		end

		-- clear pressed key
		if pressedKey then
			pressedKey.frame, pressedKeyText.frame = 0, 0
			pressedKey, pressedKeyText = nil, nil
		end
	end

	return true
end
