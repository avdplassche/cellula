#ifndef APP_HPP
#define APP_HPP

#include "Playground.hpp"
#include "config.h"
#include <vector>
#include <yaml-cpp/node/node.h>

class App {

public:
    App(std::string argv, YAML::Node& app_yaml, YAML::Node& sim_yaml);
    ~App();

    int             init();
    void            update();
    void            render();

    SDL_Window      *getWindow();
    SDL_Renderer    *getRenderer();

private:
    int             m_selected_config = 0;
    AppConfig       m_config;
    SDL_Window      *m_window = NULL;
    SDL_Renderer    *m_renderer = NULL;
    Playground      m_playground;
    std::vector<SimConfig>  m_sim_configs;

};
#endif
