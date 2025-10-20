#include "Chunk.hpp"
#include <cmath>

uint64_t
ChunkIndex::key()
{
	return (uint64_t(uint32_t(x)) << 32) | uint64_t(uint32_t(y));
}

ChunkIndex
GlobalPixel::chunk_index()
{
	int chunk_size_bits = log2(CHUNK_SIZE);

	return {
		x >> chunk_size_bits,
		y >> chunk_size_bits,
	};
}

ChunkPixel
GlobalPixel::chunk_pixel()
{
	int chunk_size_bits = log2(CHUNK_SIZE);
	int chunk_size_mask = (1 << chunk_size_bits) - 1;

	return {
		x & chunk_size_mask,
		y & chunk_size_mask,
	};
}

Chunk::Chunk()
{
	pixels.fill({ 255, 255, 255 });
}

void
Chunk::set_pixel(ChunkPixel chunk_pixel)
{
	pixels[chunk_pixel.x + chunk_pixel.y * CHUNK_SIZE] = PixelColor{ 0, 0, 0 };
}

ChunkTexture::ChunkTexture(Renderer& renderer)
{
	texture = sdl::texture(SDL_CreateTexture(
		renderer.get(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, CHUNK_SIZE, CHUNK_SIZE
	));
	SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
}

void
ChunkTexture::update(Chunk chunk)
{
	SDL_UpdateTexture(texture.get(), nullptr, &chunk.pixels, CHUNK_SIZE * sizeof(PixelColor));
}
