-- Sound severity levels
SOUND_IMPORTANT = 1
SOUND_NORMAL = 2

local soundQueue = {}
local isPlaying = false
local currSound

function onSoundInit()
	-- load sounds
	resourceManager:loadAllResources("sounds/ru/sounds.xml")

	-- general
	soundKey = Sound("soundKey")
	soundStartKey = Sound("soundStartKey")
	soundStopKey = Sound("soundStopKey")
	soundBalanceSuccess = Sound("soundBalanceSuccess")
	soundRuler = Sound("soundRuler")
	soundRulerSuccess = Sound("soundRulerSuccess")

	-- left weight
	soundLeftTable = {}
	for i = 5, 100, 5 do
		soundLeftTable[i] = Sound("soundLeft" .. tostring(i))
	end

	-- right weight
	soundRightTable = {}
	for i = 5, 100, 5 do
		soundRightTable[i] = Sound("soundRight" .. tostring(i))
	end

	-- other sounds
	soundRoundOn = Sound("soundRoundOn")
	soundRoundOff = Sound("soundRoundOff")
	soundSizesNotEntered = Sound("soundSizesNotEntered")
	soundWidthNotEntered = Sound("soundWidthNotEntered")
	soundDiamNotEntered = Sound("soundDiamNotEntered")
	soundOfsNotEntered = Sound("soundOfsNotEntered")
	soundAccel = Sound("soundAccel")
	soundMeasure = Sound("soundMeasure")
	soundDecel = Sound("soundDecel")
	soundEmergencyStop = Sound("soundEmergencyStop")
	soundWheelIsBalanced = Sound("soundWheelIsBalanced")
	soundUser1Selected = Sound("soundUser1Selected")
	soundUser2Selected = Sound("soundUser2Selected")
	soundMenu = Sound("soundMenu")
	soundUser1 = Sound("soundUser1")
	soundUser2 = Sound("soundUser2")
	soundOptions = Sound("soundOptions")
	soundAluDiskSelected = Sound("soundAluDiskSelected")
	soundSteelDiskSelected = Sound("soundSteelDiskSelected")
	soundTruckDiskSelected = Sound("soundTruckDiskSelected")
	soundNumSpikesSelected = Sound("soundNumSpikesSelected")
	soundStaticBalance = Sound("soundStaticBalance")
	soundDynamicBalance = Sound("soundDynamicBalance")
	soundBalance1Weight = Sound("soundBalance1Weight")
	soundBalance2Weight = Sound("soundBalance2Weight")
	soundSafeShutdown = Sound("soundSafeShutdown")
	soundShutdown = Sound("soundShutdown")
	soundAutoRotationLeft = Sound("soundAutoRotationLeft")
	soundAutoRotationRight = Sound("soundAutoRotationRight")
	soundBalance = Sound("soundBalance")
	soundCalibrationWheel = Sound("soundCalibrationWheel")
	soundCalibrationDisplay = Sound("soundCalibrationDisplay")
	soundRecalc = Sound("soundRecalc")
	soundOverload = Sound("soundOverload")
end

function playSound(level, ...)
	-- exit if another sound is already playing or sound level is not sufficient
	if isPlaying or level > profile:getInt("sound_level") then
		return false
	end

	-- add all sounds to queue
	for key, value in pairs(soundQueue) do
		soundQueue[key] = nil
	end

	for i, sound in ipairs{...} do
		soundQueue[i] = sound
	end

	-- initialize all counters
	isPlaying = true
	currSound = 1

	-- start the first sound
	soundQueue[currSound]:play()
	return true
end

function stopSound()
	if isPlaying then
		soundQueue[currSound]:stop()
		isPlaying = false
	end
end

function playSoundOrBeep(level, sound, ...)
	if not playSound(level, ...) then
		sound:play()
	end
end

function onSoundUpdate(delta)
	-- update the currently playing sound
	if isPlaying then
		if not soundQueue[currSound]:isPlaying() then
			-- select the next sound in queue
			currSound = currSound + 1
			if currSound <= #soundQueue then
				soundQueue[currSound]:play()
			else
				isPlaying = false

				-- HACK: shutdown after playing the special sound
				if soundQueue[1] == soundShutdown then
					--os.exit(0)
					os.execute("sudo shutdown -H now")
				end
			end
		end
	end
end
