local new_img = glomp.image.load("assets/images/openFrameworks.png")

local keyboard 	= description.workon("glomp_keyboard")
local mouse 	= description.workon("glomp_mouse")
local time 		= description.workon("glomp_time")
local window 	= description.workon("glomp_window")

local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local gui_root 	= description.workon("gui_root", "simple_gui_root")
gui_root:set({
		width = window:get("width"),
		height = window:get("height"),
	})

local performance = description.workon("debug_performance_display", "simple_gui_label")

for counter = 1,1 do
	local props = 	{
						x = math.random(100, 800),
						y = math.random(100, 600),
						image = new_img,
						text = "Press me.\nNo. Really."
					}

	local new_image = description.workon("button_" .. counter, "simple_gui_button"):set(props)

	new_image.events:on("click", function (data, context)
		performance:toggle("visible")
	end)
	gui_root:get("children"):add(new_image)
end

window.events:on("resized", function (fields, window)
	gui_root:set({
			width = fields.width,
			height = fields.height
		})
end)

window.events:on("draw", function (data, caller) 
		gui_root.events:trigger("render", gui_root, gui_root)
	end)

mouse.events:on("moved", function (data, caller)
	gui_root.events:trigger("test_mouse_out", caller:all(), gui_root)
	gui_root.events:trigger("test_mouse_over", caller:all(), gui_root)
end)

mouse.events:on("dragged", function (data, caller)
	gui_root.events:trigger("test_mouse_dragged", caller:all(), gui_root)
end)

mouse.events:on("pressed", function (data, caller)
    data_store:each("definition_index:".."simple_gui_element", function (item, index)
            if item.fields.mouse_down then
                item:set("mouse_down", false)
            end
        end)

	gui_root.events:trigger("test_mouse_down", caller:all(), gui_root)
end)

mouse.events:on("released", function (data, caller)
    data_store:each("definition_index:".."simple_gui_element", function (item, index)
            if item.fields.mouse_down then
                item:set("mouse_down", false)
            end
        end)

	gui_root.events:trigger("test_mouse_released", caller:all(), gui_root)
end)

performance:set({
		x = 700,
		y = 40,
		color = 0xff0000,
		visible = false,
		font = theme_vals.font
	})

gui_root:get("children"):add(performance)

keyboard.events:when_equals("T", function()
		performance:toggle("visible")
	end, 0)

time.events:on("update_count", function()
		if not performance:get("visible") then
			return
		end

		local time_data = time:all()

		local text = string.format("Updates: %d\nElapsed: %f\nAverage: %f\nRunning: %f\nFPS: %d",
					time_data["update_count"],
					time_data["frame_time"],
					time_data["total_time"] / time_data["update_count"],
					time_data["total_time"],
					time_data["update_count"] / time_data["total_time"])

		performance:set("text", text)
	end, 0)
