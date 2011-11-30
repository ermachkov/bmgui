-- Layout menu settings
local MENU_FADE_DELAY = 100
local DIE_SCALE = 1.35
local DIE_ANIM_DELAY = 150

local menuActive = false
local menuTime = 0
local firstPress
local selDynMode
local selDie
local prevSelDie
local dynDies
local statDies
local lastMode = MODE_ALU

-- Shows the layout menu
function showLayoutMenu()
	if not menuActive then
		menuActive = true
		firstPress = true
		local mode = balance:getIntParam("mode")
		local layout = unpackLayout(balance:getIntParam("layout"), mode)
		selDynMode = mode ~= MODE_STAT
		selDie = selDynMode and dynDies[layout + 1] or statDies[layout + 1]
		selDie.time = 0
		prevSelDie = nil
		spriteLayoutButton.frame, spriteLayoutButtonText.frame = 1, lang * 2 + 1
		local frame = selDynMode and 0 or 1
		spriteLayoutMenu.frame, spriteLayoutSubmenu.frame = frame, frame
	end
end

-- Hides the layout menu
function hideLayoutMenu()
	if menuActive then
		menuActive = false
		spriteLayoutButton.frame, spriteLayoutButtonText.frame = 0, lang * 2
	end
end

function onLayoutMenuInit()
	-- initialize sprite tables
	dynDies = {spriteDynDie15, spriteDynDie25, spriteDynDie14, spriteDynDie13, spriteDynDie23, spriteDynDie24}
	statDies = {spriteStatDie1, spriteStatDie5, spriteStatDie2, spriteStatDie3, spriteStatDie4}

	-- initialize dyn dies
	for i, die in ipairs(dynDies) do
		local width, height = die:getWidth(), die:getHeight()
		die.x, die.y = die.x + width / 2, die.y + height / 2
		die:setHotSpot(width / 2, height / 2)
		die.dynMode = true
		die.layout = i - 1
		die.time = 0
	end

	-- initialize stat dies
	for i, die in ipairs(statDies) do
		local width, height = die:getWidth(), die:getHeight()
		die.x, die.y = die.x + width / 2, die.y + height / 2
		die:setHotSpot(width / 2, height / 2)
		die.dynMode = false
		die.layout = i - 1
		die.time = 0
	end
	statDies[1].layout, statDies[2].layout, statDies[3].layout, statDies[4].layout, statDies[5].layout = LAYOUT_1, LAYOUT_5, LAYOUT_2, LAYOUT_3, LAYOUT_4
end

function onLayoutMenuUpdate(delta)
	-- check the layout menu state
	if menuActive then
		menuTime = math.min(menuTime + delta, MENU_FADE_DELAY)
	elseif menuTime > 0 then
		menuTime = math.max(menuTime - delta, 0)
	else
		return
	end

	-- determine current mode and layout
	local mode = balance:getIntParam("mode")
	local layout = unpackLayout(balance:getIntParam("layout"), mode)

	-- handle mouse movements
	if menuActive and mousePressed then
		-- retrieve current mouse position
		local x, y = mouse:getPosition()

		-- check menu dies
		if spriteDynMenuDie:isPointInside(x, y) then
			selDynMode = true
			spriteLayoutMenu.frame, spriteLayoutSubmenu.frame = 0, 0
		elseif spriteStatMenuDie:isPointInside(x, y) then
			selDynMode = false
			spriteLayoutMenu.frame, spriteLayoutSubmenu.frame = 1, 1
		else
			-- check small dies
			local dies = selDynMode and dynDies or statDies
			local maxDies = (mode == MODE_ALU or mode == MODE_STAT) and #dies or (selDynMode and 1 or 2)
			local currDie = nil
			for i = 1, maxDies do
				local die = dies[i]
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
	spriteLayoutMenu.alpha = alpha
	spriteLayoutMenu:draw()
	spriteLayoutSubmenu.alpha = alpha
	spriteLayoutSubmenu:draw()
	local color = selDynMode and 0.6 or 1.0
	spriteDynMenuDie.red, spriteDynMenuDie.green, spriteDynMenuDie.blue, spriteDynMenuDie.alpha = color, color, color, alpha
	spriteDynMenuDie:draw()
	spriteDynMenuText.red, spriteDynMenuText.green, spriteDynMenuText.blue, spriteDynMenuText.alpha = color, color, color, alpha
	spriteDynMenuText:draw()
	color = selDynMode and 1.0 or 0.6
	spriteStatMenuDie.red, spriteStatMenuDie.green, spriteStatMenuDie.blue, spriteStatMenuDie.alpha = color, color, color, alpha
	spriteStatMenuDie:draw()
	spriteStatMenuText.red, spriteStatMenuText.green, spriteStatMenuText.blue, spriteStatMenuText.alpha = color, color, color, alpha
	spriteStatMenuText:draw()

	-- small dies
	local dies = selDynMode and dynDies or statDies
	local maxDies = (mode == MODE_ALU or mode == MODE_STAT) and #dies or (selDynMode and 1 or 2)
	for i = 1, maxDies do
		local die = dies[i]
		if die ~= selDie and die ~= prevSelDie then
			die:setScale(1.0)
			die.alpha = alpha
			die:draw()
		end
	end

	-- previously selected small die
	if prevSelDie then
		prevSelDie.time = math.max(prevSelDie.time - delta, 0)
		prevSelDie:setScale(1.0 + (DIE_SCALE - 1.0) * (prevSelDie.time / DIE_ANIM_DELAY))
		prevSelDie.alpha = alpha
		if prevSelDie.dynMode == selDynMode then
			prevSelDie:draw()
		end
	end

	-- selected small die
	if selDie then
		selDie.time = math.min(selDie.time + delta, DIE_ANIM_DELAY)
		selDie:setScale(1.0 + (DIE_SCALE - 1.0) * (selDie.time / DIE_ANIM_DELAY))
		selDie.alpha = alpha
		if selDie.dynMode == selDynMode then
			selDie:draw()
		end
	end
end

function onLayoutMenuMouseDown(x, y, key)
	-- exit if not active
	if not menuActive then
		return false
	end

	-- clear the first press flag
	firstPress = false

	-- close menu on layout button press
	if spriteLayoutButton:isPointInside(x, y) then
		hideLayoutMenu()
		soundKey:play()
		return true
	end

	-- check for clicks outside the menu
	if not spriteLayoutMenu:isPointInside(x, y) and not spriteLayoutSubmenu:isPointInside(x, y) then
		hideLayoutMenu()
		return false
	end

	return true
end

function onLayoutMenuMouseUp(x, y, key)
	-- exit if not active
	if not menuActive then
		return false
	end

	-- check if a die was selected
	if selDie and selDie:isPointInside(x, y) then
		hideLayoutMenu()
		local mode = balance:getIntParam("mode")
		if selDie.dynMode and mode == MODE_STAT then
			-- move from static mode to the last dynamic one
			mode = lastMode
			balance:setIntParam("mode", mode)
		elseif not selDie.dynMode and mode ~= MODE_STAT then
			-- move from dynamic mode to the static one
			mode, lastMode = MODE_STAT, mode
			balance:setIntParam("mode", mode)
		end
		balance:setIntParam("layout", packLayout(balance:getIntParam("layout"), selDie.layout, mode))
	end

	return true
end
