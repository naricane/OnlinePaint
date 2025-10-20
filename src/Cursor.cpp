#include "Cursor.hpp"

void
Cursor::generate_from_brush(const Renderer& renderer, const Brush& brush)
{
	rect = brush.bounds.to_rect();

	texture = sdl::texture(SDL_CreateTexture(
		renderer.get(),
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		int(rect.w),
		int(rect.h)
	));
	SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
	SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);

	void* pixels;
	int pitch;
	SDL_LockTexture(texture.get(), nullptr, &pixels, &pitch);

	for (const auto& pixel : brush.pixels) {
		Vec2i p = {
			int(pixel.x - brush.bounds.left),
			int(pixel.y - brush.bounds.top),
		};

		((Uint32*)(pixels))[p.x * (pitch / 4) + p.y] = SDL_MapRGBA(
			SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB8888), nullptr, 100, 100, 100, 140
		);
	}

	SDL_UnlockTexture(texture.get());
}

void
Cursor::draw(const Renderer& renderer, Vec2 mouse_world) const
{
	if (texture) {
		Rect draw_rect = {
			rect.x + int(mouse_world.x),
			rect.y + int(mouse_world.y),
			rect.w,
			rect.h,
		};
		renderer.draw(texture, draw_rect);
	}
}
