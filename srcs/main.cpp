#include <cstdlib>
#include <pch.h>
#include <App.hpp>

int main() {

	App app;
	SDL_Event event;

	if (app.init() == -1)
		return EXIT_FAILURE;
    std::cout << "App Initialized\n";

	while (true) {

		while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED ||
			event.key.scancode == SDL_SCANCODE_ESCAPE) {
			SDL_Quit();
			return 0;
		}
		// handleEvents(app, seh, &event);
		}
		app.update();
		app.render();
		}
	SDL_Quit();
	return 0;
}

