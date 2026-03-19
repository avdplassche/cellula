#pragma once

class Cell;

////	External Libraries

#include <SDL3/SDL.h>

////	Std

#include <vector>
#include <list>

#include <algorithm>

#include <iostream>
#include <string>

#include <cmath>
#include <random>
#include <chrono>


////	Config

#include "config.h"
#include "Types.h"

////    Utils


void	setRenderDrawColor(SDL_Renderer *renderer, SDL_Color color);
int     getRandomMultiple(int min, int max, int multiple);
int     getRandomInt(int min, int max);
float   getRandomFloat(float min, float max);
Pos     getRandomPos(AppConfig &);

void    DrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius);


void    setCollision(Cell *current, Cell *other);
void    normalizeFriction(Pos *movement, float f);


////    Structures

struct CellClass {
    CellType    type;
    SDL_Color   color;
    float       speed[2];
    float       vision[2];
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
