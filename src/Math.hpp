#pragma once
#include <SDL3/SDL_rect.h>

struct Rect
{
	float x;
	float y;
	float w;
	float h;

	SDL_FRect to_sdl_rect() const;
};

struct SidesRect
{
	float left;
	float top;
	float right;
	float bottom;

	Rect to_rect() const;
};

struct Vec2
{
	float x, y;
};

struct Vec2i
{
	int x, y;
};

namespace vector {

float
length(Vec2 v);

float
dot(Vec2 a, Vec2 b);

Vec2
normalize(Vec2 v);

float
angle(Vec2 a, Vec2 b);

}

inline Vec2
operator-(Vec2 v)
{
	return { -v.x, -v.y };
}

inline Vec2
operator+(Vec2 a, Vec2 b)
{
	return { a.x + b.x, a.y + b.y };
}

inline Vec2
operator-(Vec2 a, Vec2 b)
{
	return { a.x - b.x, a.y - b.y };
}

inline Vec2
operator*(Vec2 a, Vec2 b)
{
	return { a.x * b.x, a.y * b.y };
}

inline Vec2
operator*(Vec2 a, float x)
{
	return a * Vec2{ x, x };
}

inline Vec2
operator*(float x, Vec2 a)
{
	return a * Vec2{ x, x };
}

inline Vec2
operator/(Vec2 a, Vec2 b)
{
	return { a.x / b.x, a.y / b.y };
}

inline Vec2
operator/(Vec2 a, float x)
{
	return a / Vec2{ x, x };
}

inline Vec2&
operator+=(Vec2& a, Vec2 b)
{
	a = a + b;
	return a;
}

inline Vec2&
operator-=(Vec2& a, Vec2 b)
{
	a = a - b;
	return a;
}

inline Vec2&
operator*=(Vec2& a, Vec2 b)
{
	a = a * b;
	return a;
}

inline Vec2&
operator*=(Vec2& a, float b)
{
	a = a * b;
	return a;
}

inline Vec2&
operator/=(Vec2& a, Vec2 b)
{
	a = a / b;
	return a;
}

inline Vec2&
operator/=(Vec2& a, float b)
{
	a = a / b;
	return a;
}

namespace math {

float
clamp(float value, float min, float max);

float
deg_to_rad(float deg);

float
rad_to_deg(float rad);

}
