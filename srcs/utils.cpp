#include <cassert>
#include <pch.h>

void setRenderDrawColor(SDL_Renderer *renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int getRandomMultiple(int min, int max, int multiple) {
    assert(multiple != 0);
    unsigned int seed = static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    //int rand = min + std::rand() % (max - min + 1);
    int rand = std::uniform_int_distribution<>(min, max)(gen);
    int m = rand / multiple;
    return multiple * m;
}


int getRandomInt(int min, int max) {
    unsigned int seed = static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    //int rand = min + std::rand() % (max - min + 1);
    return std::uniform_int_distribution<>(min, max)(gen);
}


Pos    getRandomPos() {
    Pos p;
    p.x = getRandomMultiple(Window_Config::PLAYGROUND_POS_X,
                                  Window_Config::PLAYGROUND_POS_X + Window_Config::PLAYGROUND_WIDTH,
                                  Window_Config::CELL_SIZE);
    p.y = getRandomMultiple(Window_Config::PLAYGROUND_POS_Y,
                                  Window_Config::PLAYGROUND_POS_Y + Window_Config::PLAYGROUND_HEIGHT,
                                  Window_Config::CELL_SIZE);
    return p;
}


void    cellCreationAssert(CellClass& c) {
    assert(static_cast<int>(c.type) >= 0);
    assert(c.speed[0] >= 0 && c.speed[1] >= 0 && c.speed[0] <=100 && c.speed[1] <=100);
    assert(c.vision[0] >= 0 && c.vision[1] >= 0 & c.vision[0] <=100 && c.vision[1] <=100);
}



