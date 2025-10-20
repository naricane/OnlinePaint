#pragma once

#include "Camera.hpp"
#include "Error.hpp"
#include "SdlDeleters.hpp"
#include <SDL3/SDL.h>
#include <expected>

class Renderer
{
private:
	sdl::renderer sdl_renderer;
	Camera camera;

	Renderer(sdl::renderer sdl_renderer);

public:
	static std::expected<Renderer, SdlError> make(const sdl::window& window);
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&& other);

	SDL_Renderer* get() const { return sdl_renderer.get(); }

	void set_camera(const Camera& camera);
	void clear() const;
	void draw(const sdl::texture& texture, const Rect& rect) const;
	void display() const;
};
