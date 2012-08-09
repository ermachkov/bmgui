-- Disk menu settings
local MENU_FADE_DELAY = 100
local DIE_SCALE = 1.25
local DIE_ANIM_DELAY = 150

local menuActive = false
local menuTime = 0
local firstPress
local selMode
local selDie
local prevSelDie
local diskHighlights
local menuDies, menuTexts
local aluDies

-- Shows the disk menu
function showDiskMenu()
	if not menuActive then
		menuActive = true
		firstPress = true
		selMode = balance:getIntParam("mode")
		selDie = aluDies[(balance:getIntParam("split") == 0) and 1 or (balance:getIntParam("numsp") - 1)]
		selDie.time = 0
		prevSelDie = nil
		spriteDiskButton.frame, spriteDiskButtonText.frame = 1, lang * 2 + 1
	end
end

-- Hides the disk menu
function hideDiskMenu()
	if menuActive then
		menuActive = false
		spriteDiskButton.frame, spriteDiskButtonText.frame = 0, lang * 2
	end
end

function onDiskMenuInit()
	-- initialize sprite tables
	diskHighlights = {spriteSteelHighlight, spriteTruckHighlight, spriteAbsHighlight}
	menuDies = {spriteAluMenuDie, spriteSteelMenuDie, spriteTruckMenuDie, spriteAbsMenuDie}
	menuTexts = {spriteAluMenuText, spriteSteelMenuText, spriteTruckMenuText, spriteAbsMenuText}
	aluDies = {spriteAluDie, spriteAluDie3, spriteAluDie4, spriteAluDie5, spriteAluDie6, spriteAluDie7, spriteAluDie8, spriteAluDie9, spriteAluDie10, spriteAluDie11, spriteAluDie12, spriteAluDie13, spriteAluDie14}

	-- initialize alu dies
	for i, die in ipairs(aluDies) do
		local width, height = die:getWidth(), die:getHeight()
		die.x, die.y = die.x + width / 2, die.y + height / 2
		die:setHotSpot(width / 2, height / 2)
		die.split = i == 1 and 0 or 1
		die.numSpikes = i + 1
		die.time = 0
	end
end

function onDiskMenuUpdate(delta)
	-- check the disk menu state
	if menuActive then
		menuTime = math.min(menuTime + delta, MENU_FADE_DELAY)
	elseif menuTime > 0 then
		menuTime = math.max(menuTime - delta, 0)
	else
		return
	end

	-- handle mouse movements
	if menuActive and mousePressed then
		-- retrieve current mouse position
		local x, y = mouse:getPosition()

		-- check menu dies
		if spriteAluMenuDie:isPointInside(x, y) then
			if selMode ~= MODE_ALU then
				selMode = MODE_ALU
				balance:setIntParam("mode", selMode)
			end
		elseif spriteSteelMenuDie:isPointInside(x, y) then
			selMode = MODE_STEEL
		elseif spriteTruckMenuDie:isPointInside(x, y) then
			selMode = MODE_TRUCK
		elseif spriteAbsMenuDie:isPointInside(x, y) then
			selMode = MODE_ABS
		elseif selMode == MODE_ALU then
			-- check small alu dies
			local currDie = nil
			for i, die in ipairs(aluDies) do
				if die:isPointInside(x, y) then
					currDie = die
					break
				end
			end

			-- select new die if needed
			if currDie ~= selDie and (not firstPress or currDie) then
				if selDie then
					prevSelDie = selDie
				elseif currDie == prevSelDie then
					prevSelDie = nil
				end
				selDie = currDie
			end
		end
	end

	-- determine the menu opacity
	local alpha = menuTime / MENU_FADE_DELAY

	-- menu background
	if selMode == MODE_ALU then
		-- disk menu and submenu
		spriteDiskMenu.frame = 0
		spriteDiskMenu.alpha = alpha
		spriteDiskMenu:draw()
		spriteDiskSubmenu.alpha = alpha
		spriteDiskSubmenu:draw()

		-- small alu dies
		for i, die in ipairs(aluDies) do
			if die ~= selDie and die ~= prevSelDie then
				die:setScale(1.0)
				die.alpha = alpha
				die:draw()
			end
		end
	else
		-- disk menu
		spriteDiskMenu.frame = 1
		spriteDiskMenu.alpha = alpha
		spriteDiskMenu:draw()

		-- disk hightlights
		if selMode ~= MODE_STAT then
			local highlight = diskHighlights[selMode]
			highlight.alpha = alpha
			highlight:draw()
		end
	end

	-- previously selected small alu die
	if prevSelDie then
		prevSelDie.time = math.max(prevSelDie.time - delta, 0)
		prevSelDie:setScale(1.0 + (DIE_SCALE - 1.0) * (prevSelDie.time / DIE_ANIM_DELAY))
		prevSelDie.alpha = alpha
		if selMode == MODE_ALU then
			prevSelDie:draw()
		end
	end

	-- selected small alu die
	if selDie then
		selDie.time = math.min(selDie.time + delta, DIE_ANIM_DELAY)
		selDie:setScale(1.0 + (DIE_SCALE - 1.0) * (selDie.time / DIE_ANIM_DELAY))
		selDie.alpha = alpha
		if selMode == MODE_ALU then
			selDie:draw()
		end
	end

	-- menu dies
	for i, die in ipairs(menuDies) do
		local color = i == selMode + 1 and 0.6 or 1.0
		die.red, die.green, die.blue, die.alpha = color, color, color, alpha
		die:draw()
	end

	-- menu texts
	for i, text in ipairs(menuTexts) do
		local color = i == selMode + 1 and 0.6 or 1.0
		text.red, text.green, text.blue, text.alpha = color, color, color, alpha
		text:draw()
	end
end

function onDiskMenuMouseDown(x, y, key)
	-- exit if not active
	if not menuActive then
		return false
	end

	-- clear the first press flag
	firstPress = false

	-- close menu on disk button press
	if spriteDiskButton:isPointInside(x, y) then
		hideDiskMenu()
		soundKey:play()
		return true
	end

	-- check layout button press (TODO: not needed with per-pixel collisions)
	if spriteLayoutButton:isPointInside(x, y) then
		hideDiskMenu()
		showLayoutMenu()
		soundKey:play()
		return true
	end

	-- check for clicks outside the menu
	if not spriteDiskMenu:isPointInside(x, y) and (selMode ~= MODE_ALU or not spriteDiskSubmenu:isPointInside(x, y)) then
		hideDiskMenu()
		return false
	end

	return true
end

function onDiskMenuMouseUp(x, y, key)
	-- exit if not active
	if not menuActive then
		return false
	end

	-- check if a die was selected
	if selMode == MODE_ALU and selDie and selDie:isPointInside(x, y) then
		hideDiskMenu()
		balance:setIntParam("mode", selMode)
		balance:setIntParam("split", selDie.split)
		if selDie.split ~= 0 then
			balance:setIntParam("numsp", selDie.numSpikes)
		end
	elseif (selMode == MODE_STEEL or selMode == MODE_TRUCK or selMode == MODE_ABS) and menuDies[selMode + 1]:isPointInside(x, y) then
		hideDiskMenu()
		balance:setIntParam("mode", selMode)
	end

	return true
end
