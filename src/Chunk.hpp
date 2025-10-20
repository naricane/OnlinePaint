#pragma once

#include "Renderer.hpp"
#include <array>
#include <cstdint>

const uint16_t CHUNK_SIZE = 512;

struct PixelColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct ChunkPixel
{
	int x;
	int y;
};

struct ChunkIndex
{
	int x;
	int y;

	uint64_t key();
};

struct GlobalPixel
{
	int x;
	int y;

	ChunkIndex chunk_index();
	ChunkPixel chunk_pixel();
};

struct Chunk
{
	std::array<PixelColor, CHUNK_SIZE * CHUNK_SIZE> pixels;

	Chunk();
	void set_pixel(ChunkPixel chunk_pixel);
};

struct ChunkTexture
{
	sdl::texture texture;

	ChunkTexture(Renderer& renderer);
	void update(Chunk chunk);
};
