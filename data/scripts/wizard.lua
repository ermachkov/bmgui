-- Wizard screen settings
local WIZARD_FADE_DELAY = 200

local wizardActive = false
local wizardTime = 0
local mainMenuLoaded = false
local pressedButton, pressedButtonText
local balanceCalIcons, balanceCalHeaders, balanceCalTexts, balanceCalTexts2
local rulerCalIcons, rulerCalHeaders, rulerCalTexts, rulerCalTexts2
local rrulerCalIcons, rrulerCalHeaders, rrulerCalTexts, rrulerCalTexts2

-- Shows the wizard
function showWizard()
	if not wizardActive and mainMenuLoaded then
		wizardActive = true
		pressedButton, pressedButtonText = nil, nil

		spriteWizardNextButton.frame, spriteWizardCancelButton.frame, spriteWizardCloseButton.frame = 0, 0, 0
		spriteWizardNextButtonText.frame, spriteWizardCancelButtonText.frame = lang * 2, lang * 2
	end
end

-- Hides the wizard
function hideWizard()
	wizardActive = false
	wizardTime = 0 -- TODO: Remove me when alpha in fonts will be fixed
end

function onWizardInit()
end

function onWizardUpdate(delta)
	-- check the background loading status
	if not mainMenuLoaded and isMainMenuLoaded() then
		mainMenuLoaded = true

		enableTranslation(false)

		balanceCalIcons = {spriteBalanceCal0Icon, spriteBalanceCal1Icon, spriteBalanceCal2Icon, spriteBalanceCal3Icon}
		balanceCalHeaders = {tr("{wizard_balance_cal_0_header}"), tr("{wizard_balance_cal_1_header}"), tr("{wizard_balance_cal_2_header}"), tr("{wizard_balance_cal_3_header}")}
		balanceCalTexts = {tr("{wizard_balance_cal_0_text}"), tr("{wizard_balance_cal_1_text}"), tr("{wizard_balance_cal_2_text}"), tr("{wizard_balance_cal_3_text}")}
		balanceCalTexts2 = {tr("{wizard_balance_cal_0_text_2}"), tr("{wizard_balance_cal_1_text_2}"), tr("{wizard_balance_cal_2_text_2}"), tr("{wizard_balance_cal_3_text_2}")}

		rulerCalIcons = {spriteRulerCal0Icon, spriteRulerCal1Icon, spriteRulerCal2Icon, spriteRulerCal3Icon}
		rulerCalHeaders = {tr("{wizard_ruler_cal_0_header}"), tr("{wizard_ruler_cal_1_header}"), tr("{wizard_ruler_cal_2_header}"), tr("{wizard_ruler_cal_3_header}")}
		rulerCalTexts = {tr("{wizard_ruler_cal_0_text}"), tr("{wizard_ruler_cal_1_text}"), tr("{wizard_ruler_cal_2_text}"), tr("{wizard_ruler_cal_3_text}")}
		rulerCalTexts2 = {tr("{wizard_ruler_cal_0_text_2}"), tr("{wizard_ruler_cal_1_text_2}"), tr("{wizard_ruler_cal_2_text_2}"), tr("{wizard_ruler_cal_3_text_2}")}

		rrulerCalIcons = {spriteRulerCal0Icon, spriteRulerCal0Icon, spriteRulerCal0Icon, spriteRulerCal1Icon, spriteRulerCal2Icon}
		rrulerCalHeaders = {tr("{wizard_rruler_cal_0_header}"), tr("{wizard_rruler_cal_1_header}"), tr("{wizard_rruler_cal_2_header}"), tr("{wizard_rruler_cal_3_header}"), tr("{wizard_rruler_cal_4_header}")}
		rrulerCalTexts = {tr("{wizard_rruler_cal_0_text}"), tr("{wizard_rruler_cal_1_text}"), tr("{wizard_rruler_cal_2_text}"), tr("{wizard_rruler_cal_3_text}"), tr("{wizard_rruler_cal_4_text}")}
		rrulerCalTexts2 = {tr("{wizard_rruler_cal_0_text_2}"), tr("{wizard_rruler_cal_1_text_2}"), tr("{wizard_rruler_cal_2_text_2}"), tr("{wizard_rruler_cal_3_text_2}"), tr("{wizard_rruler_cal_4_text_2}")}

		enableTranslation(true)
	end

	-- check the wizard state
	if wizardActive then
		wizardTime = math.min(wizardTime + delta, WIZARD_FADE_DELAY)
	elseif wizardTime > 0 then
		wizardTime = math.max(wizardTime - delta, 0)
	else
		return
	end

	-- handle currently pressed button
	if pressedButton then
		local x, y = mouse:getPosition()
		pressedButton.frame = pressedButton:isPointInside(x, y) and 1 or 0
		if pressedButtonText then
			pressedButtonText.frame = pressedButton:isPointInside(x, y) and (lang * 2 + 1) or (lang * 2)
		end
	end

	-- fade the main screen
	local alpha = wizardTime / WIZARD_FADE_DELAY
	graphics:fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 0.0, alpha * 0.75)

	-- weight indicators
	if balanceState == STATE_BALANCE_CAL2 then
		drawRightWeight()
	elseif balanceState == STATE_BALANCE_CAL3 then
		drawLeftWeight()
	end

	-- wizard background
	spriteWizardBack.alpha = alpha
	spriteWizardBack:draw()

	-- buttons
	spriteWizardNextButton.alpha = alpha
	spriteWizardNextButton:draw()
	spriteWizardNextButtonText.alpha = alpha
	spriteWizardNextButtonText:draw()
	spriteWizardCancelButton.alpha = alpha
	spriteWizardCancelButton:draw()
	spriteWizardCancelButtonText.alpha = alpha
	spriteWizardCancelButtonText:draw()
	spriteWizardCloseButton.alpha = alpha
	spriteWizardCloseButton:draw()

	-- icon and text
	if balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3 then
		local index = balanceState - STATE_BALANCE_CAL0 + 1
		local icon = balanceCalIcons[index]
		icon.alpha = alpha
		icon:draw(spriteWizardIcon.x, spriteWizardIcon.y)
		spriteWizardIconGlass:draw()

		fontMessageHeader:drawText(spriteWizardHeader.x, spriteWizardHeader.y, tr(balanceCalHeaders[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText.x, spriteWizardText.y, tr(balanceCalTexts[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText2.x, spriteWizardText2.y, tr(balanceCalTexts2[index]), 0.0, 0.0, 0.0, alpha);
	elseif balanceState >= STATE_RULER_CAL0 and balanceState <= STATE_RULER_CAL3 then
		local index = balanceState - STATE_RULER_CAL0 + 1
		local icon = rulerCalIcons[index]
		icon.alpha = alpha
		icon:draw(spriteWizardIcon.x, spriteWizardIcon.y)
		spriteWizardIconGlass:draw()

		fontMessageHeader:drawText(spriteWizardHeader.x, spriteWizardHeader.y, tr(rulerCalHeaders[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText.x, spriteWizardText.y, tr(rulerCalTexts[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText2.x, spriteWizardText2.y, tr(rulerCalTexts2[index]), 0.0, 0.0, 0.0, alpha);
	elseif balanceState >= STATE_RRULER_3P_CAL0 and balanceState <= STATE_RRULER_D_CAL1 then
		local index = balanceState - STATE_RRULER_3P_CAL0 + 1
		local icon = rrulerCalIcons[index]
		icon.alpha = alpha
		icon:draw(spriteWizardIcon.x, spriteWizardIcon.y)
		spriteWizardIconGlass:draw()

		fontMessageHeader:drawText(spriteWizardHeader.x, spriteWizardHeader.y, tr(rrulerCalHeaders[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText.x, spriteWizardText.y, tr(rrulerCalTexts[index]), 0.0, 0.0, 0.0, alpha);
		fontMessageText:drawText(spriteWizardText2.x, spriteWizardText2.y, tr(rrulerCalTexts2[index]), 0.0, 0.0, 0.0, alpha);
	end
end

function onWizardMouseDown(x, y, key)
	-- exit if not active
	if not wizardActive then
		return false
	end

	-- check wizard buttons
	if spriteWizardNextButton:isPointInside(x, y) then
		pressedButton, pressedButtonText = spriteWizardNextButton, spriteWizardNextButtonText
		pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
		soundKey:play()
	elseif spriteWizardCancelButton:isPointInside(x, y) then
		pressedButton, pressedButtonText = spriteWizardCancelButton, spriteWizardCancelButtonText
		pressedButton.frame, pressedButtonText.frame = 1, lang * 2 + 1
		soundKey:play()
	elseif spriteWizardCloseButton:isPointInside(x, y) then
		pressedButton, pressedButtonText = spriteWizardCloseButton, nil
		pressedButton.frame = 1
		soundKey:play()
	end

	return true
end

function onWizardMouseUp(x, y, key)
	-- exit if not active
	if not wizardActive then
		return false
	end

	-- release the pressed button if any
	if pressedButton then
		-- check pressed buttons
		if pressedButton:isPointInside(x, y) then
			if pressedButton == spriteWizardNextButton then
				if balanceState >= STATE_BALANCE_CAL0 and balanceState <= STATE_BALANCE_CAL3 then
					balance:setParam("start")
				else
					balance:setParam("enter")
				end
			else
				balance:setParam("stop")
			end
		end

		pressedButton.frame = 0
		if pressedButtonText then
			pressedButtonText.frame = lang * 2
		end
		pressedButton, pressedButtonText = nil, nil
	end

	return true
end
