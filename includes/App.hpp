#ifndef APP_HPP
#define APP_HPP

#include "Playground.hpp"
#include "pch.h"

class App {

public:
    App();
    ~App();

    int             init();
    void            update();
    void            render();

    SDL_Window      *getWindow();
    SDL_Renderer    *getRenderer();

    private:
    SDL_Window      *m_window = NULL;
    SDL_Renderer    *m_renderer = NULL;
    Playground      m_playground;


};
#endif
