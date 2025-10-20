#include "PaintState.hpp"

int
main()
{
	sdl::window window(SDL_CreateWindow("OnlinePaint", 1920, 1080, SDL_WINDOW_RESIZABLE));

	if (!window) {
		panic(SDL_GetError());
	}

	Renderer renderer = unwrap_or_abort(Renderer::make(window));
	bool running = true;
	SDL_Event event;

	PaintState paint_state;

	StateArgs args = { renderer };

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
			}
			paint_state.process_events(event, args);
		}

		paint_state.process(args);

		renderer.clear();
		paint_state.draw(args);
		renderer.display();
	}

	return 0;
}
