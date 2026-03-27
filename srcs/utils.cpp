#include "Cell.hpp"
#include "config.h"
#include <SDL3/SDL_stdinc.h>
#include <cassert>
#include <pch.h>

void setRenderDrawColor(SDL_Renderer *renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Color   createSDLColour(Uint8 r, Uint8 g, Uint8 b) {
    SDL_Color c = {r, g, b, 255};

    return c;
}

int getRandomMultiple(int min, int max, int multiple) {
    assert(multiple != 0);
    unsigned int seed = static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    int rand = std::uniform_int_distribution<>(min, max)(gen);
    int m = rand / multiple;
    return multiple * m;
}


int getRandomInt(int min, int max) {
    unsigned int seed = static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    int rand = std::uniform_int_distribution<>(min, max)(gen);
    return rand;
}

float getRandomFloat(float min, float max) {
    unsigned int seed = static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    return std::uniform_real_distribution<float>(min, max)(gen);
}

Pos    getRandomPos(AppConfig &config) {
    Pos p;
    p.x = getRandomInt(config.cell_size, config.playground_size.w - config.cell_size);
    p.y = getRandomInt(config.cell_size, config.playground_size.h - config.cell_size);
    return p;
}


void    cellCreationAssert(CellClass& c) {
    assert(static_cast<int>(c.type) >= 0);
    assert(c.speed[0] >= 0 && c.speed[1] >= 0 && c.speed[0] <=100 && c.speed[1] <=100);
    assert(c.vision[0] >= 0 && c.vision[1] >= 0 & c.vision[0] <=100 && c.vision[1] <=100);
}

void DrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius) {
    int32_t x = radius - 1;
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = tx - (radius << 1);

    while (x >= y) {
        SDL_RenderPoint(renderer, centerX + x, centerY - y);
        SDL_RenderPoint(renderer, centerX + x, centerY + y);
        SDL_RenderPoint(renderer, centerX - x, centerY - y);
        SDL_RenderPoint(renderer, centerX - x, centerY + y);
        SDL_RenderPoint(renderer, centerX + y, centerY - x);
        SDL_RenderPoint(renderer, centerX + y, centerY + x);
        SDL_RenderPoint(renderer, centerX - y, centerY - x);
        SDL_RenderPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - (radius << 1));
        }
    }
}

CellType   getCellTypeByString(std::string s) {
    if (s == "prey")
        return CellType::Prey;
    if (s == "predator")
        return CellType::Predator;
    return CellType::Default;
}
