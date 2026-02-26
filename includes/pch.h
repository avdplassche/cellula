#pragma once

////	External Libraries

#include <SDL3/SDL.h>

////	Std

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <chrono>

////	Config

#include "config.h"
#include "Types.h"

////    Utils


void	setRenderDrawColor(SDL_Renderer *renderer, SDL_Color color);
int     getRandomMultiple(int min, int max, int multiple);
int     getRandomInt(int min, int max);
Pos     getRandomPos();


////    Structures

struct CellClass {
    CellType    type;
    SDL_Color   color;
    int         speed[2];
    int         vision[2];
};

struct SimConfig {
    int         prey_number;
    int         predator_number;
};


CellClass   preyConfig();
CellClass   predatorConfig();

SimConfig   simulation_01();
