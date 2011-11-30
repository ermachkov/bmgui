-- Angle table
local ANGLE_TABLE = {4, 36, 64, 110, 160, 230, 352, NUM_ANGLES}

-- Popup settings
local POPUP_ANIM_DELAY = 200

-- Auto alu indication time
local AUTO_ALU_TIME = 1000

local mainMenuLoaded = false
local blinkTime = 0
local pressedButton
local pressedButtonText
local autoAluPopup, errorPopup, updatePopup
local popups
local showAboutMessage = false
local aboutMessage = ""
local autoAluTime = 0

-- Returns the angle index from table
local function getAngleIndex(angle)
	for i, value in ipairs(ANGLE_TABLE) do
		if angle <= value then
			return 9 - i
		end
	end
	return 0
end

-- Returns the angle indices
local function getAngleIndices(currAngle, targetAngle)
	-- check if we are close to weight
	local diff = balance:getIntParam("clockwise") ~= 0 and (targetAngle - currAngle) or (currAngle - targetAngle)
	if math.abs(diff) <= balance:getIntParam("angleepsilon") then
		return 8, 8, 0, 0
	end

	-- select the indices
	local index1, index2
	if diff >= 0 then
		index1, index2 = getAngleIndex(NUM_ANGLES - diff), getAngleIndex(diff)
	else
		index1, index2 = getAngleIndex(-diff), getAngleIndex(NUM_ANGLES + diff)
	end

	-- check if we are opposite to weight
	if index1 == 1 and index2 == 1 then
		return 1, 1, 1, 1
	end

	-- return angle and arrow indices
	return index1, index2, index1 ~= 1 and 1 or 0, index2 ~= 1 and 1 or 0
end

-- Asks for password on update
local function askForUpdatePassword()
	local left = (SCREEN_WIDTH - (spriteRightFasteners.x + spriteRightFasteners:getWidth())) / 2
	local top = SCREEN_HEIGHT - (spriteBottomFasteners.y + spriteBottomFasteners:getHeight())
	showKeyboard(left, top, left, SCREEN_HEIGHT, "passwd", TYPE_PASSWORD, spriteBottomFasteners, nil,
		function(value) if checkPassword(value) then local str = profile:getString("available_update_version"); profile:setString("ignored_update_version", str); profile:save();
		graphics:hide(); os.execute(profile:getString("update_command")); graphics:show() end end)
end

function showAutoAluWeights()
	autoAluTime = AUTO_ALU_TIME
end

-- Draws left weight indicator
function drawLeftWeight()
	-- retrieve the current wheel angle
	local currAngle = balance:getIntParam("wheelangle")
	local showWeights = balanceState == STATE_IDLE or balanceState == STATE_RULER or (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and (balanceSubstate == BALANCE_IDLE or balanceSubstate >= BALANCE_DECEL)
	local showAngles = balanceState == STATE_IDLE or balanceState == STATE_RULER or (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and (balanceSubstate == BALANCE_IDLE or balanceSubstate >= BALANCE_AUTO_ROTATION)

	-- determine weight and angle
	local weight, preciseWeight, angle
	if balanceState ~= STATE_BALANCE_CAL3 then
		weight = balance:getIntParam("rndweight0")
		preciseWeight = balance:getFloatParam("weight0")
		angle = balance:getIntParam("wheelangle0")
	else
		weight = balance:getIntParam("calweight")
		preciseWeight = weight
		angle = NUM_ANGLES / 2
	end

	-- draw indicator
	if showAngles and weight ~= 0 then
		spriteLeftTopAngle.frame, spriteLeftBottomAngle.frame, spriteLeftTopArrow.frame, spriteLeftBottomArrow.frame = getAngleIndices(currAngle, angle)
	else
		spriteLeftTopAngle.frame, spriteLeftBottomAngle.frame, spriteLeftTopArrow.frame, spriteLeftBottomArrow.frame = 0, 0, 0, 0
	end

	drawHorzSplittedSprite(spriteLeftTopAngle, spriteLeftBottomAngle)

	if spriteLeftTopAngle.frame == 8 and spriteLeftBottomAngle.frame == 8 then
		spriteLeftGreenBack:draw()
	end

	spriteLeftTopArrow:draw()
	spriteLeftBottomArrow:draw()

	spriteLeftWeight:draw()

	if showWeights then
		if balanceState == STATE_IDLE and pressedButton == spriteStopButton then
			drawCenteredText(fontWeights, spriteLeftWeight, formatWeight(preciseWeight), 0.0, 0.0, 0.0)
		else
			drawCenteredText(fontWeights, spriteLeftWeight, formatNumber(weight), 0.0, 0.0, 0.0)
		end
	end
end

-- Draws right weight indicator
function drawRightWeight()
	-- retrieve the current wheel angle
	local currAngle = balance:getIntParam("wheelangle")
	local showWeights = balanceState == STATE_IDLE or balanceState == STATE_RULER or (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and (balanceSubstate == BALANCE_IDLE or balanceSubstate >= BALANCE_DECEL)
	local showAngles = balanceState == STATE_IDLE or balanceState == STATE_RULER or (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and (balanceSubstate == BALANCE_IDLE or balanceSubstate >= BALANCE_AUTO_ROTATION)

	-- determine weight and angle
	local weight, preciseWeight, angle
	local weight2, preciseWeight2, angle2
	if balanceState ~= STATE_BALANCE_CAL2 then
		weight = balance:getIntParam("rndweight1")
		preciseWeight = balance:getFloatParam("weight1")
		angle = balance:getIntParam("wheelangle1")

		weight2 = balance:getIntParam("rndweight2")
		preciseWeight2 = balance:getFloatParam("weight2")
		angle2 = balance:getIntParam("wheelangle2")
	else
		weight = balance:getIntParam("calweight")
		preciseWeight = weight
		angle = 0

		weight2 = 0
		preciseWeight2 = 0.0
		angle2 = 0
	end

	-- select between primary and secondary angles
	local showPrimaryAngle
	if weight2 == 0 then
		showPrimaryAngle = true
	elseif weight == 0 then
		showPrimaryAngle = false
	else
		local diff1 = math.abs(currAngle - angle)
		if diff1 > NUM_ANGLES / 2 then
			diff1 = NUM_ANGLES - diff1
		end
		local diff2 = math.abs(currAngle - angle2)
		if diff2 > NUM_ANGLES / 2 then
			diff2 = NUM_ANGLES - diff2
		end
		showPrimaryAngle = diff1 <= diff2
	end

	-- draw indicator
	if showAngles and (weight ~= 0 or weight2 ~= 0) then
		if showPrimaryAngle then
			spriteRightTopAngle.frame, spriteRightBottomAngle.frame, spriteRightTopArrow.frame, spriteRightBottomArrow.frame = getAngleIndices(currAngle, angle)
		else
			spriteRightTopAngle.frame, spriteRightBottomAngle.frame, spriteRightTopArrow2.frame, spriteRightBottomArrow2.frame = getAngleIndices(currAngle, angle2)
		end
	else
		spriteRightTopAngle.frame, spriteRightBottomAngle.frame, spriteRightTopArrow.frame, spriteRightBottomArrow.frame = 0, 0, 0, 0
	end

	-- HACK: suppress green indicators when secondary weight is active
	if not showPrimaryAngle and spriteRightTopAngle.frame == 8 and spriteRightBottomAngle.frame == 8 then
		spriteRightTopAngle.frame, spriteRightBottomAngle.frame = 0, 0
		drawHorzSplittedSprite(spriteRightTopAngle, spriteRightBottomAngle)
		spriteRightTopAngle.frame, spriteRightBottomAngle.frame = 8, 8
	else
		drawHorzSplittedSprite(spriteRightTopAngle, spriteRightBottomAngle)
	end

	local showWeight2 = balance:getIntParam("mode") == MODE_ALU and balance:getIntParam("split") ~= 0
	if showWeight2 then
		spriteRightBack2:draw()
	end

	if spriteRightTopAngle.frame == 8 and spriteRightBottomAngle.frame == 8 then
		if showPrimaryAngle then
			spriteRightGreenBack:draw()
		else
			spriteRightGreenBack2:draw()
		end
	end

	if showPrimaryAngle then
		spriteRightTopArrow:draw()
		spriteRightBottomArrow:draw()
	else
		spriteRightTopArrow2:draw()
		spriteRightBottomArrow2:draw()
	end

	spriteRightWeight:draw()
	if showWeight2 then
		spriteRightWeight2:draw()
	end

	if showWeights then
		if balanceState == STATE_IDLE and pressedButton == spriteStopButton then
			drawCenteredText(fontWeights, spriteRightWeight, formatWeight(preciseWeight), 0.0, 0.0, 0.0)
			if showWeight2 then
				drawCenteredText(fontWeights, spriteRightWeight2, formatWeight(preciseWeight2), 0.0, 0.0, 0.0)
			end
		else
			drawCenteredText(fontWeights, spriteRightWeight, formatNumber(weight), 0.0, 0.0, 0.0)
			if showWeight2 then
				drawCenteredText(fontWeights, spriteRightWeight2, formatNumber(weight2), 0.0, 0.0, 0.0)
			end
		end
	end
end

function onMainScreenInit()
	-- load sprites
	resourceManager:loadAllResources("sprites/main_screen/resources.xml")
	include("sprites/main_screen/sprites.lua")
	main_screen_createSprites()

	-- update button labels
	updateSpritesLanguage()

	-- disable functional buttons
	spriteMenuButton.frame, spriteHelpButton.frame = 2, 2
	spriteMenuButtonText.frame, spriteHelpButtonText.frame = lang * 3 + 2, lang * 3 + 2

	-- load fonts
	resourceManager:loadAllResources("fonts/main_screen.xml")
	fontSizes = CFont("fontSizes")
	fontWeights = CFont("fontWeights")
	fontWheel = CFont("fontWheel")
	fontMessageHeader = CFont("fontMessageHeader")
	fontMessageText = CFont("fontMessageText")
	fontMessageBox = CFont("fontMessageBox")
	fontKeyboardDisplay = CFont("fontKeyboardDisplay")
	fontSpeedometer = CFont("fontSpeedometer")

	-- load sounds
	resourceManager:loadAllResources("sounds/sounds.xml")
	soundKey = Sound("soundKey")
	soundStartKey = Sound("soundStartKey")
	soundStopKey = Sound("soundStopKey")
	soundBalanceSuccess = Sound("soundBalanceSuccess")
	soundRuler = Sound("soundRuler")
	soundRulerSuccess = Sound("soundRulerSuccess")

	-- init popups
	autoAluPopup = {back = spriteAutoAluPopupBack, icon = spriteAutoAluPopupIcon, active = false, time = 0}
	errorPopup = {back = spriteErrorPopupBack, icon = spriteErrorPopupIcon, label = spriteErrorPopupText, active = false, time = 0, text = "13"}
	updatePopup = {back = spriteUpdatePopupBack, icon = spriteUpdatePopupIcon, active = false, time = 0}
	popups = {autoAluPopup, errorPopup, updatePopup}

	-- read "About" message from the file
	local file = io.open("/etc/bminfo")
	if file then
		io.close(file)
		for line in io.lines("/etc/bminfo") do
			aboutMessage = aboutMessage .. line .. "\n"
		end
	end
end

function onMainScreenUpdate(delta)
	-- exit if not active
	if startScreenActive or oscilloscopeActive then
		return
	end

	-- increment blink counter
	blinkTime = blinkTime + delta
	if blinkTime >= 1000 then
		blinkTime = blinkTime - 1000
	end

	-- decrement auto alu counter
	autoAluTime = math.max(autoAluTime - delta, 0)

	-- retrieve current mouse position
	local x, y = mouse:getPosition()

	-- check the background loading status
	if not mainMenuLoaded and isMainMenuLoaded() then
		mainMenuLoaded = true
		spriteMenuButton.frame, spriteHelpButton.frame = 0, 0
		spriteMenuButtonText.frame, spriteHelpButtonText.frame = lang * 3, lang * 3
	end

	-- handle currently pressed button
	if pressedButton then
		pressedButton.frame = pressedButton:isPointInside(x, y) and 1 or 0
		if pressedButton == spriteUser1 then
			spriteUser2.frame = pressedButton.frame
		end
		if pressedButtonText then
			if pressedButton:isPointInside(x, y) then
				pressedButtonText.frame = pressedButtonText == spriteHelpButtonText and (lang * 3 + 1) or (lang * 2 + 1)
			else
				pressedButtonText.frame = pressedButtonText == spriteHelpButtonText and (lang * 3) or (lang * 2)
			end
		end
	end

	-- determine current mode and layout
	local mode = balance:getIntParam("mode")
	local layout = unpackLayout(balance:getIntParam("layout"), mode)

	-- background
	graphics:setBlendMode(BLEND_DISABLE)
	spriteMainScreenBack0:draw()
	spriteMainScreenBack1:draw()
	graphics:setBlendMode(BLEND_ALPHA)

	-- retrieve weight information
	local currAngle = balance:getIntParam("wheelangle")
	local weight1, weight2, weight3 = balance:getIntParam("rndweight0"), balance:getIntParam("rndweight1"), balance:getIntParam("rndweight2")
	local angle1, angle2, angle3 = balance:getIntParam("wheelangle0"), balance:getIntParam("wheelangle1"), balance:getIntParam("wheelangle2")
	local angleEpsilon = balance:getIntParam("angleepsilon")

	-- wheel
	spriteWheelBack:draw()
	if balanceState == STATE_IDLE or (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and (balanceSubstate == BALANCE_IDLE or balanceSubstate >= BALANCE_AUTO_ROTATION) then
		-- show left weight
		if weight1 ~= 0 then
			if layout == LAYOUT_1_3 or layout == LAYOUT_1_4 or layout == LAYOUT_1_5 then
				spriteWheelWeight1.frame = (math.abs(currAngle - angle1) <= angleEpsilon) and 1 or 0
				spriteWheelWeight1:draw()
			elseif layout == LAYOUT_2_3 or layout == LAYOUT_2_4 or layout == LAYOUT_2_5 then
				spriteWheelWeight2.frame = 0
				spriteWheelWeight2:draw()
			end
		end

		-- show right weight
		if weight2 ~= 0 or weight3 ~= 0 then
			if layout == LAYOUT_1_3 or layout == LAYOUT_2_3 then
				spriteWheelWeight3.frame = 0
				spriteWheelWeight3:draw()
			elseif layout == LAYOUT_1_4 or layout == LAYOUT_2_4 then
				spriteWheelWeight4.frame = (math.abs(currAngle - (weight2 ~= 0 and angle2 or angle3)) <= angleEpsilon) and 1 or 0
				spriteWheelWeight4:draw()
			elseif layout == LAYOUT_1_5 or layout == LAYOUT_2_5 then
				spriteWheelWeight5.frame = (math.abs(currAngle - (weight2 ~= 0 and angle2 or angle3)) <= angleEpsilon) and 1 or 0
				spriteWheelWeight5:draw()
			end
		end
	elseif balanceState == STATE_RULER then
		if balanceSubstate == RULER_MEASURE or balanceSubstate == RULER_DONTSHOW then
			if (mode ~= MODE_STAT and layout ~= LAYOUT_2_3) or (mode == MODE_STAT and layout == LAYOUT_1) then
				spriteWheelArrowMeasure1.frame = 0
				spriteWheelArrowMeasure1:draw()
				spriteWheelTarget1:draw()
				fontWheel:drawText(spriteWheelArrowForwardText1.x, spriteWheelArrowForwardText1.y, balance:getIntParam("rofs"), 0.0, 0.0, 0.0)
			elseif (mode ~= MODE_STAT and layout == LAYOUT_2_3) or (mode == MODE_STAT and layout == LAYOUT_2) then
				spriteWheelArrowMeasure2.frame = 0
				spriteWheelArrowMeasure2:draw()
				spriteWheelTarget2:draw()
				fontWheel:drawText(spriteWheelArrowForwardText2.x, spriteWheelArrowForwardText2.y, balance:getIntParam("rofs"), 0.0, 0.0, 0.0)
			elseif mode == MODE_STAT and layout == LAYOUT_3 then
				spriteWheelArrowMeasure3.frame = 0
				spriteWheelArrowMeasure3:draw()
				spriteWheelTarget3:draw()
				fontWheel:drawText(spriteWheelArrowForwardText3.x, spriteWheelArrowForwardText3.y, balance:getIntParam("rofs"), 0.0, 0.0, 0.0)
			end
		elseif balanceSubstate == RULER_MEASURE_L then
			spriteWheelArrowMeasure3.frame = 0
			spriteWheelArrowMeasure3:draw()
			spriteWheelTarget3:draw()
			fontWheel:drawText(spriteWheelArrowForwardText3.x, spriteWheelArrowForwardText3.y, balance:getIntParam("rstick"), 0.0, 0.0, 0.0)
		elseif balanceSubstate == RULER_SHOW_L1 then
			local dist = balance:getIntParam("weightdist")
			local frame = (math.abs(currAngle - angle1) <= angleEpsilon and dist == 0) and 1 or 0
			if layout == LAYOUT_1_3 then
				spriteWheelArrowInstall1.frame = dist >= 0 and 0 or 1
				spriteWheelArrowInstall1:draw()
				if spriteWheelWeight1.frame == 0 and frame == 1 then
					soundRuler:play()
				end
				spriteWheelWeight1.frame = frame
				spriteWheelWeight1:draw()
				if dist >= 0 then
					fontWheel:drawText(spriteWheelArrowForwardText1.x, spriteWheelArrowForwardText1.y, math.abs(dist), 0.0, 0.0, 0.0)
				else
					fontWheel:drawText(spriteWheelArrowBackwardText1.x, spriteWheelArrowBackwardText1.y, math.abs(dist), 0.0, 0.0, 0.0)
				end
			else
				spriteWheelArrowInstall2.frame = dist >= 0 and 0 or 1
				spriteWheelArrowInstall2:draw()
				if spriteWheelWeight2.frame == 0 and frame == 1 then
					soundRuler:play()
				end
				spriteWheelWeight2.frame = frame
				spriteWheelWeight2:draw()
				if dist >= 0 then
					fontWheel:drawText(spriteWheelArrowForwardText2.x, spriteWheelArrowForwardText2.y, math.abs(dist), 0.0, 0.0, 0.0)
				else
					fontWheel:drawText(spriteWheelArrowBackwardText2.x, spriteWheelArrowBackwardText2.y, math.abs(dist), 0.0, 0.0, 0.0)
				end
			end
		elseif balanceSubstate == RULER_SHOW_L2 or balanceSubstate == RULER_SHOW_L3 then
			local dist = balance:getIntParam("weightdist")
			local frame = (math.abs(currAngle - (balanceSubstate == RULER_SHOW_L2 and angle2 or angle3)) <= angleEpsilon and dist == 0) and 1 or 0
			spriteWheelArrowInstall3.frame = dist >= 0 and 0 or 1
			spriteWheelArrowInstall3:draw()
			if spriteWheelWeight3.frame == 0 and frame == 1 then
				soundRuler:play()
			end
			spriteWheelWeight3.frame = frame
			spriteWheelWeight3:draw()
			if dist >= 0 then
				fontWheel:drawText(spriteWheelArrowForwardText3.x, spriteWheelArrowForwardText3.y, math.abs(dist), 0.0, 0.0, 0.0)
			else
				fontWheel:drawText(spriteWheelArrowBackwardText3.x, spriteWheelArrowBackwardText3.y, math.abs(dist), 0.0, 0.0, 0.0)
			end
		end

		-- show auto alu weights
		if mode == MODE_ALU and autoAluTime ~= 0 and (balanceSubstate == RULER_MEASURE or balanceSubstate == RULER_DONTSHOW or balanceSubstate == RULER_MEASURE_L) then
			if layout == LAYOUT_1_3 then
				spriteWheelWeight1.frame = 2
				spriteWheelWeight1:draw()
			elseif layout == LAYOUT_2_3 then
				spriteWheelWeight2.frame = 2
				spriteWheelWeight2:draw()
			end

			if layout == LAYOUT_1_3 or layout == LAYOUT_2_3 then
				spriteWheelWeight3.frame = 2
				spriteWheelWeight3:draw()
			end
		end
	end

	-- functional buttons
	spriteMenuButton:draw()
	spriteMenuButtonText:draw()
	spriteHelpButton:draw()
	spriteHelpButtonText:draw()

	-- layout button
	spriteLayoutButton:draw()
	spriteLayoutButtonText:draw()
	spriteLayoutIcon.frame = (mode ~= MODE_STAT) and layout or (layout + 6)
	spriteLayoutIcon:draw()

	-- disk button
	spriteDiskButton:draw()
	spriteDiskButtonText:draw()
	spriteDiskIcon.frame = (mode == MODE_ALU and balance:getIntParam("split") ~= 0) and (balance:getIntParam("numsp") + 2) or mode
	spriteDiskIcon:draw()

	-- start button
	spriteStartButton:draw()
	spriteStartButtonText:draw()

	-- stop button
	spriteStopButton:draw()
	spriteStopButtonText:draw()

	-- width/stick size
	local red = math.floor(balanceErrors0 / 64) % 2 ~= 0 and blinkTime < 500
	spriteWidthStickBack:draw()
	spriteWidthStickButton.frame, spriteWidthIcon.frame, spriteStickIcon.frame = 0, 0, 0
	if mode == MODE_ALU and (layout == LAYOUT_1_3 or layout == LAYOUT_2_3) then
		drawVertSplittedSprite(red and spriteStickIconRed or spriteStickIcon, red and spriteWidthStickButtonRed or spriteWidthStickButton)
		local stick = balance:getIntParam("stick")
		if stick ~= 0 then
			drawCenteredText(fontSizes, spriteWidthStickButton, formatNumber(stick), 0.0, 0.0, 0.0)
		else
			drawCenteredText(fontSizes, spriteWidthStickButton, "Auto", 0.0, 0.0, 0.0)
		end
	else
		drawVertSplittedSprite(red and spriteWidthIconRed or spriteWidthIcon, red and spriteWidthStickButtonRed or spriteWidthStickButton)
		drawCenteredText(fontSizes, spriteWidthStickButton, formatNumber(balance:getFloatParam("width")), 0.0, 0.0, 0.0)
	end

	-- diameter size
	red = math.floor(balanceErrors0 / 16) % 2 ~= 0 and blinkTime < 500
	spriteDiamBack:draw()
	spriteDiamButton.frame, spriteDiamIcon.frame = 0, 0
	drawVertSplittedSprite(red and spriteDiamButtonRed or spriteDiamButton, red and spriteDiamIconRed or spriteDiamIcon)
	drawCenteredText(fontSizes, spriteDiamButton, formatNumber(balance:getFloatParam("diam")), 0.0, 0.0, 0.0)

	-- offset size
	red = math.floor(balanceErrors0 / 32) % 2 ~= 0 and blinkTime < 500
	spriteOfsBack:draw()
	spriteOfsButton.frame, spriteOfsIcon.frame = 0, 0
	drawVertSplittedSprite(red and spriteOfsButtonRed or spriteOfsButton, red and spriteOfsIconRed or spriteOfsIcon)
	drawCenteredText(fontSizes, spriteOfsButton, formatNumber(balance:getIntParam("offset")), 0.0, 0.0, 0.0)

	-- users switch
	spriteUsersBack:draw()
	spriteUsersLed:draw()
	if balance:getIntParam("user") == 0 then
		spriteUser1:draw()
		spriteUser1Text:draw()
	else
		spriteUser2:draw()
		spriteUser2Text:draw()
	end

	-- weight indicators
	drawLeftWeight()
	drawRightWeight()

	-- update popups
	autoAluPopup.active = balance:getIntParam("autoaluflag") ~= 0
	errorPopup.active = numErrors ~= 0
	errorPopup.text = tostring(numErrors)
	updatePopup.active = profile:getString("available_update_version") > profile:getString("ignored_update_version")

	-- popups
	for i, popup in ipairs(popups) do
		-- update popup state
		if popup.active then
			popup.time = math.min(popup.time + delta, POPUP_ANIM_DELAY)
		elseif popup.time > 0 then
			popup.time = math.max(popup.time - delta, 0)
		end

		-- draw popup
		if popup.time > 0 then
			local posY = (popup.time / POPUP_ANIM_DELAY - 1.0) * popup.back:getHeight()
			popup.back:draw(popup.back.x, posY + popup.back.y)
			popup.icon:draw(popup.icon.x, posY + popup.icon.y)
			if popup.text then
				local textWidth, textHeight = fontMessageText:getTextSize(popup.text)
				fontMessageText:drawText(popup.label.x + (popup.label:getWidth() - textWidth) / 2, posY + popup.label.y + (popup.label:getHeight() - textHeight) / 2, popup.text, 95 / 255, 136 / 255, 160 / 255)
			end
		end
	end

	-- draw about message
	if showAboutMessage then
		spriteAboutMessageBack:draw()
		fontMessageText:drawText(spriteAboutMessageText.x, spriteAboutMessageText.y, aboutMessage, 73 / 255, 73 / 255, 73 / 255)
	end

	-- draw cover message
	if (balanceState == STATE_BALANCE or (balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3)) and balanceSubstate == BALANCE_WAIT_COVER then
		spriteCoverMessageBack:draw()
		drawCenteredText(fontMessageBox, spriteCoverMessageText, tr("PUSH COVER!"), 69 / 255, 69 / 255, 69 / 255)
	end

	-- draw wheel message
	if math.floor(balanceErrors0 / (2 ^ 18)) % 2 ~= 0 then
		spriteWheelMessageBack:draw()
		drawCenteredText(fontMessageBox, spriteWheelMessageText, tr("ROTATE WHEEL!"), 69 / 255, 69 / 255, 69 / 255)
	end
end

function onMainScreenMouseDown(x, y, key)
	if showAboutMessage then
		showAboutMessage = false
	elseif spriteStartButton:isPointInside(x, y) then
		-- send "start" command
		pressedButton, pressedButtonText = spriteStartButton, spriteStartButtonText
		pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
		soundStartKey:play()
	elseif spriteStopButton:isPointInside(x, y) then
		-- send "stop" command
		pressedButton, pressedButtonText = spriteStopButton, spriteStopButtonText
		pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
		balance:setParam("stop")
		soundStopKey:play()
	elseif spriteLeftWeight:isPointInside(x, y) and balance:getIntParam("rndweight0") ~= 0 then
		-- send "rotate 0" command
		pressedButton, pressedButtonText = spriteLeftWeight, nil
		pressedButton.frame = 1
		balance:setIntParam("rotate", 0)
		soundKey:play()
	elseif spriteRightWeight:isPointInside(x, y) and balance:getIntParam("rndweight1") ~= 0 then
		-- send "rotate 1" command
		pressedButton, pressedButtonText = spriteRightWeight, nil
		pressedButton.frame = 1
		balance:setIntParam("rotate", 1)
		soundKey:play()
	elseif spriteRightWeight2:isPointInside(x, y) and balance:getIntParam("rndweight2") ~= 0 then
		-- send "rotate 2" command
		pressedButton, pressedButtonText = spriteRightWeight2, nil
		pressedButton.frame = 1
		balance:setIntParam("rotate", 2)
		soundKey:play()
	elseif spriteUser1:isPointInside(x, y) then
		-- send "user n" command
		pressedButton, pressedButtonText = spriteUser1, nil
		pressedButton.frame = 1
		balance:setIntParam("user", 1 - balance:getIntParam("user"))
		soundKey:play()
	elseif spriteLayoutButton:isPointInside(x, y) then
		-- enter the layout menu
		showLayoutMenu()
		soundKey:play()
	elseif spriteDiskButton:isPointInside(x, y) then
		-- enter the disk menu
		showDiskMenu()
		soundKey:play()
	elseif mainMenuLoaded and spriteMenuButton:isPointInside(x, y) then
		-- enter the main menu
		showMainMenu()
		soundKey:play()
	elseif mainMenuLoaded and spriteHelpButton:isPointInside(x, y) then
		-- show about dialog
		pressedButton, pressedButtonText = spriteHelpButton, spriteHelpButtonText
		pressedButton.frame, pressedButtonText.frame = 1, lang * 3 + 1
		showAboutMessage = true
		soundKey:play()
	elseif spriteWidthIcon:isPointInside(x, y) or spriteWidthStickButton:isPointInside(x, y) then
		local mode = balance:getIntParam("mode")
		local layout = unpackLayout(balance:getIntParam("layout"), mode)
		local param, type
		if mode == MODE_ALU and (layout == LAYOUT_1_3 or layout == LAYOUT_2_3) then
			param, type = "stick", TYPE_INT
		else
			param, type = "width", TYPE_FLOAT
		end
		local left = SCREEN_WIDTH - (spriteRightFasteners.x + spriteRightFasteners:getWidth())
		local top = spriteWidthStickButton.y + spriteWidthStickButton:getHeight()
		showKeyboard(left, top, SCREEN_WIDTH, top, param, type, spriteRightFasteners)
		soundKey:play()
	elseif spriteDiamIcon:isPointInside(x, y) or spriteDiamButton:isPointInside(x, y) then
		local left = spriteDiamIcon.x + spriteDiamIcon:getWidth()
		local top = SCREEN_HEIGHT - (spriteBottomFasteners.y + spriteBottomFasteners:getHeight())
		showKeyboard(left, top, left, SCREEN_HEIGHT, "diam", TYPE_FLOAT, spriteBottomFasteners)
		soundKey:play()
	elseif spriteOfsIcon:isPointInside(x, y) or spriteOfsButton:isPointInside(x, y) then
		local left = 0
		local top = spriteOfsButton.y + spriteOfsButton:getHeight()
		showKeyboard(left, top, -(spriteKeyboardBack.x + spriteKeyboardBack:getWidth()), top, "offset", TYPE_INT, spriteLeftFasteners)
		soundKey:play()
	end
end

function onMainScreenMouseUp(x, y, key)
	-- release pressed button
	if pressedButton then
		if pressedButton == spriteStartButton and pressedButton:isPointInside(x, y) then
			balance:setParam("start")
		elseif pressedButton == spriteUser1 then
			spriteUser2.frame = 0
		end

		pressedButton.frame = 0
		if pressedButtonText then
			pressedButtonText.frame = pressedButtonText == spriteHelpButtonText and lang * 3 or lang * 2
		end
		pressedButton, pressedButtonText = nil, nil
	end

	-- show error journal on error popup click
	if errorPopup.active and errorPopup.back:isPointInside(x, y) then
		showErrorJournal()
	end

	-- execute update command on update popup click
	if updatePopup.active and updatePopup.back:isPointInside(x, y) then
		showMessage(tr("{update_message_text}"), MESSAGE_YES_NO, MESSAGE_WARNING, askForUpdatePassword,
			function() local str = profile:getString("available_update_version"); profile:setString("ignored_update_version", str); profile:save() end)
	end
end
