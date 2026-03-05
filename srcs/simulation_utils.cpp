#include "Cell.hpp"
#include "pch.h"
#include <algorithm>
#include <cmath>


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
