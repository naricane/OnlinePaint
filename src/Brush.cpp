#include "Brush.hpp"

Brush
circle_brush(int radius)
{
	Brush brush;
	brush.pixels.clear();

	int x = 0;
	int y = -radius;
	int p = -radius;
	while (x < -y) {
		if (p > 0) {
			y += 1;
			p += 2 * (x + y) + 1;
		} else {
			p += 2 * x + 1;
		}

		brush.pixels.emplace_back(GlobalPixel{ x, y });
		brush.pixels.emplace_back(GlobalPixel{ -x, y });
		brush.pixels.emplace_back(GlobalPixel{ x, -y });
		brush.pixels.emplace_back(GlobalPixel{ -x, -y });
		brush.pixels.emplace_back(GlobalPixel{ y, x });
		brush.pixels.emplace_back(GlobalPixel{ -y, x });
		brush.pixels.emplace_back(GlobalPixel{ y, -x });
		brush.pixels.emplace_back(GlobalPixel{ -y, -x });

		x += 1;
	}

	brush.bounds = {};
	for (const auto& pixel : brush.pixels) {
		if (pixel.x > brush.bounds.right) {
			brush.bounds.right = pixel.x;
		}
		if (pixel.x < brush.bounds.left) {
			brush.bounds.left = pixel.x;
		}
		if (pixel.y > brush.bounds.bottom) {
			brush.bounds.bottom = pixel.y;
		}
		if (pixel.y < brush.bounds.top) {
			brush.bounds.top = pixel.y;
		}
	}

	return brush;
}
