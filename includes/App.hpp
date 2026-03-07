#ifndef APP_HPP
#define APP_HPP

#include "Playground.hpp"
#include "config.h"
#include "pch.h"

class App {

public:
    App(AppConfig&);
    ~App();

    int             init();
    void            update();
    void            render();

    SDL_Window      *getWindow();
    SDL_Renderer    *getRenderer();

private:
    AppConfig&      m_config;
    SDL_Window      *m_window = NULL;
    SDL_Renderer    *m_renderer = NULL;
    Playground      m_playground;


};
#endif
