performance_timer = timer.new()

game_window = window.new()
game_window:init(game_options.screen_width, 
				game_options.screen_height,
				true)
game_frame_time = 0
game_time = 0
game_timer = timer.new()
game_input = input.new()
game_audio = audio.new()

active = true

function bind_actions(actions)
	for idx, row in ipairs(actions) do	
		game_input:bind(row[1], row[2], row[3])
	end
end

game_input:bind("quit", "key_down", keyboard.Q)
game_input:on("quit", function () 
	active = false
end)

game_input:on("fire", function ()
	zap:play()
	player:update(1.0)
end)

game_window:start_2d(game_options.screen_width, 
		game_options.screen_height,
		0, 0)

local elapsed_time = 1.0
function game_loop(callback)
	frames = 0
	while active do
		game_frame_time = game_timer:elapsed()
		game_time = game_time + game_frame_time
		if (game_frame_time > 0.2) then
			game_frame_time = 0.2
		end
		game_timer:reset()
		game_window:update()
		game_input:update()
		performance_timer:start()
		callback(game_frame_time)
		performance_timer:stop()
		performance_timer:stop()
		elapsed_frame_time = elapsed_frame_time + performance_timer:elapsed()
		frames = frames + 1
	end
	
	print ("Perf:","\nframes :", frames, "\nAvg Sec:", elapsed_frame_time / frames, "\nAvg FPS:", frames / elapsed_frame_time)

	return frames
end
