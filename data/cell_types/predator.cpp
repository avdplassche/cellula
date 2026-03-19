#include "config.h"
#include "pch.h"
#include "Cell.hpp"

CellClass   predatorConfig() {
    CellClass predator;

    predator.type = CellType::Predator;
    predator.color =  Color_Palette::PREDATOR;
    predator.speed[0] = 25;
    predator.speed[1] = 35;
    predator.vision[0] = 20;
    predator.vision[1] = 30;
    return predator;
}

