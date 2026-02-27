#pragma once

////	External Libraries

#include <SDL3/SDL.h>

////	Std

#include <vector>
#include <list>

#include <algorithm>

#include <iostream>
#include <string>
#include <random>
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

////    Configurations (to me moved)

CellClass   preyConfig();
CellClass   predatorConfig();

SimConfig   simulation_01();
void        cellCreationAssert(CellClass& c);


////    Print / Debugs


template <typename T>
void printContainer(const T& container, const std::string& label = "Container") {
    std::cout << label << ": [ ";
    
    auto it = container.begin();
    while (it != container.end()) {
        std::cout << *it;
        if (++it != container.end()) {
            std::cout << ", ";
        }
    }
    
    std::cout << " ]" << std::endl;
}
