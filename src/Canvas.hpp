#pragma once

#include "Chunk.hpp"
#include "Renderer.hpp"
#include <unordered_map>
#include <vector>

struct Canvas
{
	std::unordered_map<uint64_t, Chunk> chunks;
	std::unordered_map<uint64_t, ChunkTexture> textures;

	void put_pixel(GlobalPixel global_pixel, Renderer& renderer);
	void put_pixels(
		Vec2i offset,
		const std::vector<GlobalPixel>& pixels,
		SidesRect bounds,
		Renderer& renderer
	);
	void draw(const Renderer& renderer);
};
