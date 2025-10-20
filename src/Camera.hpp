#pragma once
#include "Math.hpp"

class Camera
{
private:
	Vec2 offset = { 0.f, 0.f };
	float zoom_value = 1.f;
	int zoom_level = 0;

public:
	void zoom_in(int delta);
	void pan_around(Vec2 offset);

	Vec2 to_screen(Vec2 world) const;
	Rect to_screen(Rect world) const;
	Vec2 to_world(Vec2 screen) const;

	float zoom();
};
