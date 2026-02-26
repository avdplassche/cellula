#include "Cell.hpp"
#include "config.h"
#include "pch.h"


CellClass   preyConfig() {
    CellClass prey;

    prey.type = CellType::Prey;
    prey.color =  Color_Palette::PREY;
    prey.speed[0] = 50;
    prey.speed[1] = 60;
    prey.vision[0] = 4;
    prey.vision[1] = 6;
    return prey;
}

