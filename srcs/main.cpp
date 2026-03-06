#include <cstdlib>
#include <pch.h>
#include <App.hpp>
#include <type_traits>
#include <yaml-cpp/yaml.h>

int main() {

	App app;
	SDL_Event event;

    YAML::Node config = YAML::LoadFile("config/config.yaml");
    if (config.IsNull())
    {
        std::cerr << "Error opening config file" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << config["window"]["width"]<< std::endl;
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

