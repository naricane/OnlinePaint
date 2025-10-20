#pragma once

#include "Brush.hpp"
#include "Canvas.hpp"
#include "Cursor.hpp"

struct StateArgs
{
	Renderer& renderer;
};

class PaintState
{
private:
	Canvas canvas;

	Vec2 mouse_screen;
	Camera camera;

	bool dragging = false;
	Vec2 new_position;
	Vec2 old_position;

	Brush brush = circle_brush(8);
	Cursor cursor;

public:
	void process_events(SDL_Event& event, const StateArgs& args);
	void process(const StateArgs& args);
	void draw(const StateArgs& args);
};
