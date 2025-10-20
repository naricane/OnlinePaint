#pragma once

#include <SDL3/SDL.h>
#include <memory>

template<typename T, void (*Destructor)(T*)>
struct free_fn
{
	void operator()(void* alloc) const { Destructor(static_cast<T*>(alloc)); }
};

template<typename T, void (*Destructor)(T*)>
using c_unique_ptr = std::unique_ptr<T, free_fn<T, Destructor>>;

namespace sdl {
using window = c_unique_ptr<SDL_Window, SDL_DestroyWindow>;
using renderer = c_unique_ptr<SDL_Renderer, SDL_DestroyRenderer>;
using texture = c_unique_ptr<SDL_Texture, SDL_DestroyTexture>;
}
