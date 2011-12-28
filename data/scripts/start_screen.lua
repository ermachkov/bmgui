startScreenActive = false
local pressedButton, pressedText
local currButton, currText
local oldPedal = 1

-- Draws the text
local function drawLabel(sprite, text, button)
	if button.frame ~= 0 then
		fontMessageText:drawText(sprite.x, sprite.y, text, 1.0, 1.0, 1.0)
	else
		fontMessageText:drawText(sprite.x, sprite.y, text, 92 / 255, 105 / 255, 140 / 255)
	end
end

-- Processes the pressed button
local function processButton(button)
	if button == spriteStartWorkButton then
		hideStartScreen()
	elseif button == spriteBalanceCalibrationButton then
		balance:setParam("keycal0")
		hideStartScreen()
	elseif button == spriteTouchscreenCalibrationButton then
		os.execute(profile:getString("cal_command", "balance_xinput_calibrator"))
	end
end

-- Shows the start screen
function showStartScreen()
	if not startScreenActive then
		startScreenActive = true
		spriteStartWorkButton.frame, spriteBalanceCalibrationButton.frame, spriteTouchscreenCalibrationButton.frame = 0, 0, 0
		pressedButton, pressedText = nil, nil
		currButton, currText = nil, nil
	end
end

-- Hides the start screen
function hideStartScreen()
	startScreenActive = false
end

function onStartScreenInit()
end

function onStartScreenUpdate(delta)
	-- exit if not active
	if not startScreenActive then
		return
	end

	-- exit from start screen if not idle
	if balanceState ~= STATE_IDLE then
		hideStartScreen()
		return
	end

	-- select the current button with wheel
	spriteStartWorkButton.frame, spriteBalanceCalibrationButton.frame, spriteTouchscreenCalibrationButton.frame = 0, 0, 0
	local angle = balance:getIntParam("wheelangle")
	if angle < NUM_ANGLES / 3 then
		currButton, currText = spriteStartWorkButton, spriteStartWorkText
	elseif angle < 2 * NUM_ANGLES / 3 then
		currButton, currText = spriteBalanceCalibrationButton, spriteBalanceCalibrationText
	else
		currButton, currText = spriteTouchscreenCalibrationButton, spriteTouchscreenCalibrationText
	end

	-- handle the pressed button
	if pressedButton then
		local x, y = mouse:getPosition()
		pressedButton.frame = isPointInside(x, y, pressedButton.x, pressedButton.y, pressedButton.x + pressedButton:getWidth(), pressedText.y + pressedText:getHeight()) and 1 or 0
	end

	-- handle the current button
	if currButton then
		currButton.frame = 1
	end

	-- background
	graphics:gradientFill(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 14 / 255, 61 / 255, 182 / 255, 1.0, 0.0, 0.0, 0.0, 1.0)

	-- panel
	spriteStartPanel0:draw()
	spriteStartPanel1:draw()

	-- buttons
	spriteStartWorkButton:draw()
	spriteBalanceCalibrationButton:draw()
	spriteTouchscreenCalibrationButton:draw()

	-- text
	drawLabel(spriteStartWorkText, tr("START\nWORK"), spriteStartWorkButton)
	drawLabel(spriteBalanceCalibrationText, tr("BALANCE\nCALIBRATION"), spriteBalanceCalibrationButton)
	drawLabel(spriteTouchscreenCalibrationText, tr("TOUCHSCREEN\nCALIBRATION"), spriteTouchscreenCalibrationButton)

	-- network icon
	if not profile:getBool("server_status", true) then
		spriteNetworkStatusIcon:draw()
	end

	-- mouse icon
	if profile:getInt("input_dev") == 1 then
		spriteMouseStatusIcon:draw()
	end

	-- handle the pedal
	local newPedal = math.floor(balance:getIntParam("spiinput") / 2 ^ 15) % 2
	if newPedal ~= 0 and oldPedal == 0 then
		processButton(currButton)
	end
	oldPedal = newPedal
end

function onStartScreenMouseDown(x, y, key)
	-- exit if not active
	if not startScreenActive then
		return false
	end

	-- check the buttons
	if isPointInside(x, y, spriteStartWorkButton.x, spriteStartWorkButton.y, spriteStartWorkButton.x + spriteStartWorkButton:getWidth(), spriteStartWorkText.y + spriteStartWorkText:getHeight()) then
		pressedButton, pressedText = spriteStartWorkButton, spriteStartWorkText
		pressedButton.frame = 1
		soundKey:play()
	elseif isPointInside(x, y, spriteBalanceCalibrationButton.x, spriteBalanceCalibrationButton.y, spriteBalanceCalibrationButton.x + spriteBalanceCalibrationButton:getWidth(), spriteBalanceCalibrationText.y + spriteBalanceCalibrationText:getHeight()) then
		pressedButton, pressedText = spriteBalanceCalibrationButton, spriteBalanceCalibrationText
		pressedButton.frame = 1
		soundKey:play()
	elseif isPointInside(x, y, spriteTouchscreenCalibrationButton.x, spriteTouchscreenCalibrationButton.y, spriteTouchscreenCalibrationButton.x + spriteTouchscreenCalibrationButton:getWidth(), spriteTouchscreenCalibrationText.y + spriteTouchscreenCalibrationText:getHeight()) then
		pressedButton, pressedText = spriteTouchscreenCalibrationButton, spriteTouchscreenCalibrationText
		pressedButton.frame = 1
		soundKey:play()
	end

	return true
end

function onStartScreenMouseUp(x, y, key)
	-- exit if not active
	if not startScreenActive then
		return false
	end

	-- release the pressed button if any
	if pressedButton then
		if isPointInside(x, y, pressedButton.x, pressedButton.y, pressedButton.x + pressedButton:getWidth(), pressedText.y + pressedText:getHeight()) then
			processButton(pressedButton)
		end
		pressedButton.frame = 0
		pressedButton, pressedText = nil, nil
	end

	return true
end
