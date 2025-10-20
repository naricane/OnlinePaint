#pragma once
#include "Chunk.hpp"
#include "Math.hpp"
#include <vector>

struct Brush
{
	SidesRect bounds = {};
	std::vector<GlobalPixel> pixels;
};

Brush
circle_brush(int radius);
