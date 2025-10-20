#include "Renderer.hpp"

Renderer::Renderer(sdl::renderer sdl_renderer)
	: sdl_renderer(std::move(sdl_renderer))
{
	SDL_SetRenderVSync(sdl_renderer.get(), -1);
}

Renderer::Renderer(Renderer&& other)
{
	sdl_renderer = std::move(other.sdl_renderer);
}

std::expected<Renderer, SdlError>
Renderer::make(const sdl::window& window)
{
	sdl::renderer sdl_renderer(SDL_CreateRenderer(window.get(), nullptr));
	if (!sdl_renderer) {
		return std::unexpected(SdlError{ SDL_GetError() });
	}

	return Renderer(std::move(sdl_renderer));
}

void
Renderer::set_camera(const Camera& camera)
{
	this->camera = camera;
}

void
Renderer::clear() const
{
	SDL_SetRenderDrawColor(sdl_renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(sdl_renderer.get());
}

void
Renderer::draw(const sdl::texture& texture, const Rect& rect) const
{
	SDL_FRect draw_rect = camera.to_screen(rect).to_sdl_rect();
	SDL_RenderTexture(sdl_renderer.get(), texture.get(), nullptr, &draw_rect);
}

void
Renderer::display() const
{
	SDL_RenderPresent(sdl_renderer.get());
}
