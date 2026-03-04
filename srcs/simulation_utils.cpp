#include "Cell.hpp"
#include "pch.h"


void    setCollision(Cell *current, Cell *other) {

    float v_sq = current->getVision() * current->getVision();

    float dx = other->getPos().x - current->getPos().x;
    float dy = other->getPos().y - current->getPos().y;
    if ((dx * dx + dy * dy) <= v_sq && other->getType() != current->getType())
    {
        if (current->getType() == CellType::Predator
            && current->getMap().find(other) == current->getMap().end()) 
        {
            current->setState(CellState::Attack);
            current->setOther(other, other->getType());
        }
        else if (current->getType() == CellType::Prey
            && current->getMap().find(other) == current->getMap().end()) 
        {
            current->setState(CellState::Escape);
            current->setOther(other, other->getType());
        }
        current->setDebugShape();
    }
}
