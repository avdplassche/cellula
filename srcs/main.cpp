#include "config.h"
#include <cstdlib>
#include <pch.h>
#include <App.hpp>
#include <type_traits>
#include <vector>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

int main() {

	SDL_Event event;
    YAML::Node app_file_config = YAML::LoadFile("config/config.yaml");
    if (app_file_config.IsNull())
    {
        std::cerr << "Error opening config file" << std::endl;
        return EXIT_FAILURE;
    }

    YAML::Node sim_file_config = YAML::LoadFile("config/simulations.yaml");

    // AppConfig  app_config;

    // fillAppConfig(app_file_config, app_config);
    App app(app_file_config, sim_file_config);
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

