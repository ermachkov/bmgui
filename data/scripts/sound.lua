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
end

function playSound(...)
	-- exit if another sound is already playing
	if isPlaying then
		return
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
			end
		end
	end
end
