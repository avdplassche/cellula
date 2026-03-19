#include "Cell.hpp"
#include "pch.h"
#include <algorithm>
#include <cmath>

/* In Playground.cpp */

void    setCollision(Cell *current, Cell *other) {

    float v_sq = current->getVision() * current->getVision();

    float dx = other->getPos().x - current->getPos().x;
    float dy = other->getPos().y - current->getPos().y;
    if ((dx * dx + dy * dy) <= v_sq && other->getType() != current->getType())
    {
        auto cellMap = current->getMap();
        auto it = std::find_if(cellMap.begin(), cellMap.end(), 
                                [other](const std::pair<float, Cell*>& element) {
                                    return element.second == other;
                                });
        if (it != cellMap.end())
            return ;
        if (current->getType() == CellType::Predator)
        {
            current->setState(CellState::Attack);
            current->setOther(std::sqrt(dx * dx + dy * dy), other);
        }
        else if (current->getType() == CellType::Prey)
        {
            current->setState(CellState::Escape);
            current->setOther(std::sqrt(dx * dx + dy * dy), other);
        }
        current->setDebugShape();
    }
}


/* In Cell.cpp */


void    normalizeFriction(Pos *movement, float f) {
    float x = movement->x;
    float y = movement->y;
    int r;
    float f_x;
    float f_y;

    if (f == 0)
    {
        movement->x = 0;
        movement->y = 0;
        return ;
    }
    if (x > 0)
        f_x = f * -1;
    else if (x < 0)
        f_x = f;
    else
        f_x = 0;
    if (y > 0)
        f_y = f * -1;
    else if (y < 0)
        f_y = f;
    else
        f_y = 0;
    if (fabs(x) > fabs(y))
    {
        r = x / y;
        movement->x += f_x;
        movement->y += f_y / r;
    }
    else if (fabs(y) < fabs(x))
    {
        r = y / x;
        movement->x += f_x / r;
        movement->y += f_y;
    }
    else
    {
        movement->x += f_x;
        movement->y += f_y;
    }
}

