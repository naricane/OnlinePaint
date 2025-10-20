#pragma once

#include "Brush.hpp"
#include "Renderer.hpp"

class Cursor
{
private:
	sdl::texture texture;
	Rect rect;

public:
	void generate_from_brush(const Renderer& renderer, const Brush& brush);
	void draw(const Renderer& renderer, Vec2 mouse_world) const;
};
