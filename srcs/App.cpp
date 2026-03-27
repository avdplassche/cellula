#include "App.hpp"
#include "config.h"
#include "logger.h"
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
        newLog(SDL_GetError(), LOG_ERROR);
        return -1;
    }
    m_window = SDL_CreateWindow(m_config.window_name.c_str(), m_config.window_width,
                                m_config.window_height, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        newLog(SDL_GetError(), LOG_ERROR);
        return -1;
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        newLog(SDL_GetError(), LOG_ERROR);
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
    const auto start{std::chrono::steady_clock::now()};
    setRenderDrawColor(m_renderer, Color_Palette::MAIN_BACKGROUND);
    SDL_RenderClear(m_renderer);
    m_playground.draw();
    SDL_RenderPresent(m_renderer);
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> total{end - start};
    std::cout << "Render total time : " << total << "\n\n";
    std::cout << "Frame fraction used : " << total.count() + m_playground.getUpdateTime() << " / " << 1000 / 60 << "\n\n";
    std::cout << "------------------\n\n";
}

SDL_Window *App::getWindow() { return m_window; }

SDL_Renderer *App::getRenderer() { return m_renderer; }

