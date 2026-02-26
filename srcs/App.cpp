#include "App.hpp"

App::App(): m_playground(simulation_01()) {}

App::~App() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
}

int App::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    std::cout << "SDL init\n";
    m_window = SDL_CreateWindow(Window_Config::WINDOW_NAME, Window_Config::WIDTH,
                                Window_Config::HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    std::cout << "Window Created\n";
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        std::cout << SDL_GetError() << '\n';
        return -1;
    }
    std::cout << "Renderer Created\n";
    SDL_SetRenderVSync(m_renderer, 1);

    return 0;
}

void App::update() {
    m_playground.update();
}

void App::render() {
    setRenderDrawColor(m_renderer, Color_Palette::MAIN_BACKGROUND);
    SDL_RenderClear(m_renderer);
    m_playground.draw(m_renderer);
    SDL_RenderPresent(m_renderer);
}

SDL_Window *App::getWindow() { return m_window; }

SDL_Renderer *App::getRenderer() { return m_renderer; }
