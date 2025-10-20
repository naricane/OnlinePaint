#include "Math.hpp"
#include <cmath>

SDL_FRect
Rect::to_sdl_rect() const
{
	return { x, y, w, h };
}

Rect
SidesRect::to_rect() const
{
	return {
		left,
		top,
		std::abs(right - left) + 1,
		std::abs(top - bottom) + 1,
	};
}

namespace vector {

float
length(Vec2 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float
dot(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float
cross(Vec2 a, Vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

Vec2
normalize(Vec2 v)
{
	return { .x = v.x / length(v), .y = v.y / length(v) };
}

float
angle(Vec2 a, Vec2 b)
{
	return std::atan2(cross(a, b), dot(a, b));
}

}

namespace math {

float
clamp(float value, float min, float max)
{
	if (value > max) {
		return max;
	} else if (value < min) {
		return min;
	} else {
		return value;
	}
}

float
deg_to_rad(float deg)
{
	return deg * M_PI / 180.f;
}

float
rad_to_deg(float rad)
{
	return rad * 180.f / M_PI;
}

}
