#include "config.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <cstdlib>
#include <pch.h>
#include <App.hpp>
#include <type_traits>
#include <vector>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>
#include "logger.h"


int main(int argc, char **argv) {

	SDL_Event event;
    std::string arg;

    if (argc == 2)
        arg = argv[1];
    else
        arg = "";

    YAML::Node app_file_config = YAML::LoadFile("config/config.yaml");
    if (app_file_config.IsNull())
    {
        newLog("Error opening config file", LOG_ERROR);
        return EXIT_FAILURE;
    }

    YAML::Node sim_file_config = YAML::LoadFile("config/simulations.yaml");
    if (sim_file_config.IsNull())
    {
        newLog("Error opening simulation config file", LOG_ERROR);
        return EXIT_FAILURE;
    }

    App app(arg, app_file_config, sim_file_config);
	if (app.init() == -1)
		return EXIT_FAILURE;

    newLog("App Initialized", LOG_INFO);

    bool    isPaused = false;

	while (true) {

		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED ||
                event.key.scancode == SDL_SCANCODE_ESCAPE) {
                SDL_Quit();
                return 0;
            }
            if (event.type == SDL_EVENT_KEY_DOWN 
                &&event.key.scancode == SDL_SCANCODE_SPACE)
                isPaused ? isPaused = false : isPaused = true;
		}
        if (!isPaused)
            app.update();
		app.render();
    }
	SDL_Quit();
	return 0;
}

