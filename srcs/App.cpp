#include "App.hpp"
#include "config.h"
#include <SDL3/SDL_video.h>
#include <yaml-cpp/node/node.h>


App::App(std::string arg, YAML::Node& app_yaml, YAML::Node& sim_yaml) {
    fillAppConfig(app_yaml, m_config);
    m_config.simulation_name = arg;
    m_sim_configs.reserve(sim_yaml["simulations"].size());
    fillSimConfig(sim_yaml, m_sim_configs);
    int i = 0;
    for (auto& conf : m_sim_configs)
    {
        if (arg == conf.name)
            m_selected_config = i;
        i++;
    }
}

App::~App() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
}

int App::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    m_window = SDL_CreateWindow(m_config.window_name.c_str(), m_config.window_width,
                                m_config.window_height, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    SDL_SetRenderVSync(m_renderer, 1);
    m_playground.init(m_renderer, m_config, m_sim_configs[m_selected_config]);
    return 0;
}

void App::update() {
    m_playground.update();
}

void App::render() {
    setRenderDrawColor(m_renderer, Color_Palette::MAIN_BACKGROUND);
    SDL_RenderClear(m_renderer);
    m_playground.draw();
    SDL_RenderPresent(m_renderer);
}

SDL_Window *App::getWindow() { return m_window; }

SDL_Renderer *App::getRenderer() { return m_renderer; }
