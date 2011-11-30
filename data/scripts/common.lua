-- Virtual screen size
SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 1024

-- Language codes
LANG_EN = 0
LANG_RU = 1
LANG_CN = 2

-- Balance states
STATE_IDLE = 0
STATE_BALANCE = 1
STATE_BALANCE_CAL0 = 2
STATE_BALANCE_CAL1 = 3
STATE_BALANCE_CAL2 = 4
STATE_BALANCE_CAL3 = 5
STATE_BALANCE_CAL4 = 6
STATE_RULER = 7
STATE_RULER_CAL0 = 8
STATE_RULER_CAL1 = 9
STATE_RULER_CAL2 = 10
STATE_RULER_CAL3 = 11
STATE_RULER_CAL_FAST = 12
STATE_RULER2 = 13
STATE_PROGRAMMING = 14
STATE_RRULER_3P_CAL0 = 15
STATE_RRULER_3P_CAL1 = 16
STATE_RRULER_3P_CAL2 = 17
STATE_RRULER_D_CAL0 = 18
STATE_RRULER_D_CAL1 = 19
STATE_RRULER_D_CAL2 = 20
STATE_BALANCE_1W_CAL_SAV = 21
STATE_BALANCE_1W_CAL_LD = 22

-- Balance substates
BALANCE_IDLE = 0
BALANCE_WAIT_COVER = 1
BALANCE_START = 2
BALANCE_MIN_SPEED = 3
BALANCE_STABLE_SPEED = 4
BALANCE_MEASURE = 5
BALANCE_WAIT_RESULTS = 6
BALANCE_DECEL = 7
BALANCE_FORWARD = 8
BALANCE_AUTO_ROTATION = 9
BALANCE_STOP = 10
BALANCE_BREAKER = 11

-- Ruler substates
RULER_IDLE = 0
RULER_MEASURE = 1
RULER_WAIT = 2
RULER_MEASURE_L = 3
RULER_DONTSHOW = 4
RULER_SHOW_L1 = 5
RULER_SHOW_L2 = 6
RULER_SHOW_L3 = 7

-- Disk modes
MODE_ALU   = 0
MODE_STEEL = 1
MODE_TRUCK = 2
MODE_ABS   = 3
MODE_STAT  = 4

-- Weight layouts
LAYOUT_1_5 = 0
LAYOUT_2_5 = 1
LAYOUT_1_4 = 2
LAYOUT_1_3 = 3
LAYOUT_2_3 = 4
LAYOUT_2_4 = 5

-- Static layouts
LAYOUT_1 = 0
LAYOUT_2 = 1
LAYOUT_3 = 2
LAYOUT_4 = 3
LAYOUT_5 = 4

-- Number of discrete angles
NUM_ANGLES = 720

-- Parameter types
TYPE_INT = 0
TYPE_FLOAT = 1
TYPE_IP = 2
TYPE_PASSWORD = 3

-- Main menu item states
ITEM_NORMAL = 0
ITEM_PRESSED = 1
ITEM_SELECTED = 2

-- Statistics modes
STATS_DISKS = 0
STATS_INCHES = 1
STATS_WEIGHTS = 2
STATS_TIME = 3

-- Globals
balanceState = STATE_IDLE
balanceSubstate = BALANCE_IDLE
balanceErrors0, balanceErrors1, balanceErrors2 = 0, 0, 0
balanceResult = 1 -- needed to be nonzero after startup
numErrors = 0
mousePressed = false
profile = nil
protocolValid = true

lang = LANG_EN
local translationEnabled = true
local translations = {TRANSLATION_EN, TRANSLATION_RU}
local translation = translations[lang + 1]

-- Sets the current language
function setLanguage(language)
	lang = language
	translation = translationEnabled and translations[lang + 1] or {}
end

-- Enables/disables the translation
function enableTranslation(enabled)
	translationEnabled = enabled
	translation = translationEnabled and translations[lang + 1] or {}
end

-- Translates the text string
function tr(text)
	return translation[text] or text
end

-- Generates mouse up event
function genMouseUp()
	local x, y = mouse:getPosition()
	onMouseUp(x, y, MOUSE_LEFT)
end

-- Unpacks the current layout
function unpackLayout(mask, mode)
	return math.floor(mask / 2 ^ (mode * 3)) % 8
end

-- Packs the current layout
function packLayout(mask, layout, mode)
	local mul = 2 ^ (mode * 3)
	local div = 2 ^ ((mode + 1) * 3)
	return math.floor(mask / div) * div + layout * mul + mask % mul
end

-- Formats a number
function formatNumber(num)
	local str = string.format("%.2f", num)
	if str:sub(-2) == "00" then
		return str:sub(1, -4)
	elseif str:sub(-1) == "0" then
		return str:sub(1, -2)
	else
		return str
	end
end

-- Formats a weight
function formatWeight(num)
	if num >= 100.0 then
		num = math.floor(num + 0.5)
	end

	local str = string.format("%.1f", num)
	if str:sub(-1) == "0" or #str > 4 then
		return str:sub(1, -3)
	else
		return str
	end
end

-- Calculates number of characters in string
function getNumChars(str, char)
	local code = char:byte()
	local count = 0

	for i = 1, #str do
		if str:byte(i) == code then
			count = count + 1
		end
	end

	return count
end

-- Checks the point against the rectangle
function isPointInside(x, y, x1, y1, x2, y2)
	return x >= x1 and x < x2 and y >= y1 and y < y2
end

-- Clamps the number
function clamp(value, minValue, maxValue)
	return math.max(minValue, math.min(maxValue, value))
end

-- Subtracts two 32-bit unsigned integer numbers
function sub32(x, y)
	return (x >= y) and (x - y) or (x - y + 4294967296);
end

-- Updates text sprites language
function updateSpritesLanguage()
	spriteMenuButtonText.frame = lang * 3 + 1
	spriteHelpButtonText.frame = lang * 3
	spriteStartButtonText.frame = lang * 2
	spriteStopButtonText.frame = lang * 2
	spriteLayoutButtonText.frame = lang * 2
	spriteDiskButtonText.frame = lang * 2
	spriteDynMenuText.frame = lang
	spriteStatMenuText.frame = lang
	spriteAluMenuText.frame = lang
	spriteSteelMenuText.frame = lang
	spriteTruckMenuText.frame = lang
	spriteAbsMenuText.frame = lang
	spriteProgressText.frame = lang
	spriteSpeedometerText.frame = lang
end

-- Checks the entered password
function checkPassword(value)
	if value == profile:getString("password", "679") then
		password = value
		return true
	else
		showMessage(tr("{invalid_password}"), MESSAGE_OK, MESSAGE_ERROR)
		return false
	end
end

-- Draws horizontally splitted sprite
function drawHorzSplittedSprite(sprite1, sprite2)
	sprite1:draw(sprite1.x, sprite1.y, sprite1.x + sprite1:getWidth(), sprite1.y + sprite1:getHeight() - 1, 0, 0, sprite1:getWidth(), sprite1:getHeight() - 1)
	sprite2:draw(sprite2.x, sprite2.y + 1, sprite2.x + sprite2:getWidth(), sprite2.y + sprite2:getHeight(), 0, 1, sprite2:getWidth(), sprite2:getHeight())
end

-- Draws vertically splitted sprite
function drawVertSplittedSprite(sprite1, sprite2)
	sprite1:draw(sprite1.x, sprite1.y, sprite1.x + sprite1:getWidth() - 1, sprite1.y + sprite1:getHeight(), 0, 0, sprite1:getWidth() - 1, sprite1:getHeight())
	sprite2:draw(sprite2.x + 1, sprite2.y, sprite2.x + sprite2:getWidth(), sprite2.y + sprite2:getHeight(), 1, 0, sprite2:getWidth(), sprite2:getHeight())
end

-- Draws the centered text inside the sprite
function drawCenteredText(font, sprite, text, r, g, b, a)
	local textWidth, textHeight = font:getTextSize(text)
	font:drawText(sprite.x + (sprite:getWidth() - textWidth) / 2, sprite.y + (sprite:getHeight() - textHeight) / 2, text, r or 1.0, g or 1.0, b or 1.0, a or 1.0)
end

-- Draws the horizontally centered text inside the sprite
function drawHorzCenteredText(font, sprite, text, r, g, b, a)
	local textWidth, textHeight = font:getTextSize(text)
	font:drawText(sprite.x + (sprite:getWidth() - textWidth) / 2, sprite.y, text, r or 1.0, g or 1.0, b or 1.0, a or 1.0)
end
