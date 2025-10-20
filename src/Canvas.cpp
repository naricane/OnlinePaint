#include "Canvas.hpp"

bool
is_in_chunk(GlobalPixel gp, ChunkIndex i)
{
	int left = i.x * CHUNK_SIZE;
	int right = i.x * CHUNK_SIZE + CHUNK_SIZE - 1;
	int top = i.y * CHUNK_SIZE;
	int bottom = i.y * CHUNK_SIZE + CHUNK_SIZE - 1;

	return gp.x >= left && gp.x <= right && gp.y >= top && gp.y <= bottom;
}

void
Canvas::put_pixels(
	Vec2i offset,
	const std::vector<GlobalPixel>& pixels,
	SidesRect bounds,
	Renderer& renderer
)
{
	auto [top, left]
		= GlobalPixel{ int(offset.y + bounds.top), int(offset.x + bounds.left) }.chunk_index();
	auto [bottom, right]
		= GlobalPixel{ int(offset.y + bounds.bottom), int(offset.x + bounds.right) }.chunk_index();

	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			ChunkIndex index = ChunkIndex{ x, y };
			uint64_t key = index.key();
			Chunk& chunk = chunks[key];

			for (const auto& pixel : pixels) {
				GlobalPixel gp = { pixel.x + offset.x, pixel.y + offset.y };
				if (is_in_chunk(gp, index)) {
					chunk.set_pixel(gp.chunk_pixel());
				}
			}

			auto it = textures.find(key);
			if (it != textures.end()) {
				it->second.update(chunk);
			} else {
				auto [new_it, _] = textures.emplace(key, renderer);
				new_it->second.update(chunk);
			}
		}
	}
}

void
Canvas::draw(const Renderer& renderer)
{
	for (const auto& [key, value] : textures) {
		Vec2i index = {
			int32_t(key >> 32),
			int32_t(key),
		};
		Rect rect = {
			float(index.x * CHUNK_SIZE),
			float(index.y * CHUNK_SIZE),
			float(CHUNK_SIZE),
			float(CHUNK_SIZE),
		};

		renderer.draw(value.texture, rect);
	}
}
