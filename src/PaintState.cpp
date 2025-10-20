#include "PaintState.hpp"

void
PaintState::process_events(SDL_Event& event, const StateArgs& args)
{
	switch (event.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				dragging = true;
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				dragging = false;
			}
			break;
		case SDL_EVENT_MOUSE_MOTION:
			mouse_screen = { event.motion.x, event.motion.y };
			new_position = mouse_screen;
			if (dragging) {
				camera.pan_around(old_position - new_position);
			}
			old_position = new_position;
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			camera.pan_around(mouse_screen);
			camera.zoom_in(event.wheel.integer_y);
			camera.pan_around(-mouse_screen);

			cursor.generate_from_brush(args.renderer, brush);
			break;
	}
}

void
PaintState::process(const StateArgs& args)
{
	Vec2 mouse_world = camera.to_world(mouse_screen);
	Vec2i mouse_canvas = {
		int(mouse_world.x),
		int(mouse_world.y),
	};
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LEFT) {
		canvas.put_pixels(mouse_canvas, brush.pixels, brush.bounds, args.renderer);
	}
}

void
PaintState::draw(const StateArgs& args)
{
	args.renderer.set_camera(camera);
	canvas.draw(args.renderer);
	Vec2 mouse_world = camera.to_world(mouse_screen);
	cursor.draw(args.renderer, mouse_world);
}
