#include "App.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <algorithm>
#include <cmath>
#include <vector>

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

bool    checkCorners(AppConfig& config, Pos* pos, Corner &corner){
    if (pos->x <= config.playground_margin.x
        && pos->y <= config.playground_margin.y)
        corner = Corner::NW;
    else if (pos->x <= config.playground_margin.x
        && pos->y >= config.playground_limit.y)
        corner = Corner::SW;
    else if (pos->x >= config.playground_limit.x
        && pos->y <= config.playground_margin.y)
        corner = Corner::NE;
    else if (pos->x >= config.playground_limit.x && pos->y >= config.playground_limit.y)
        corner = Corner::SE;
    else
        return false;
    return true;
}

void    handleCellCorners(AppConfig &config, Vec2 *movement, std::vector<std::pair<float, Cell*>>& others, Corner &c){
    int x_sign = 1;
    int y_sign = 1;
    if (c == Corner::NW)
    {
        if (!others.empty())
        {
            if (others[0].second->getPos().x - config.playground_margin.x
                < others[0].second->getPos().y - config.playground_margin.y)
                movement->setValues(1, 0);
            else
                movement->setValues(0, 1);
            return ;
        }
    }
    else if (c == Corner::NE)
    {
        if (!others.empty())
        {
            if (config.playground_limit.x - others[0].second->getPos().x
                < others[0].second->getPos().y - config.playground_margin.y)
                movement->setValues(-1, 0);
            else
                movement->setValues(0, 1);
            return ;
        }
        x_sign *= -1;
    }
    else if (c == Corner::SW)
    {
        if (!others.empty())
        {
            if (others[0].second->getPos().x - config.playground_margin.x
                <  config.playground_limit.y - others[0].second->getPos().y)
                movement->setValues(1, 0);
            else
                movement->setValues(0, -1);
            return ;
        }
        y_sign *= -1;
    }
    else if (c == Corner::SE)
    {
        if (!others.empty())
        {
            if (config.playground_limit.x - others[0].second->getPos().x
                <  config.playground_limit.y - others[0].second->getPos().y)
                movement->setValues(-1, 0);
            else
                movement->setValues(0, -1);
            return ;
        }
        x_sign *= -1;
        y_sign *= -1;
    }
    movement->setValues(x_sign, y_sign);
}

bool    checkLimits(AppConfig& config, Pos *pos, Side& side){
    if (pos->x <= config.playground_margin.x)
        side = Side::W;
    else if (pos->x >= config.playground_limit.x)
        side = Side::E;
    else if (pos->y <= config.playground_margin.y)
        side = Side::N;
    else if (pos->y >= config.playground_limit.y)
        side = Side::S;
    else
        return false;
    return true;
}


void    handleCellLimits(AppConfig &config, Vec2 *movement, std::vector<std::pair<float, Cell*>>& others, Side &s) {
    // float   m_x = 0;
    // float   m_y = 0;
    (void) config;
    if (s == Side::W)
    {
        movement->y >= 0 ? movement->y = 1 : movement->y = -1;
        if (!others.empty())
            movement->x = 0;
        else
            movement->x = 1;
    }
    else if (s == Side::E)
    {
        movement->y >= 0 ? movement->y = 1 : movement->y = -1;
        if (!others.empty())
            movement->x = 0;
        else
            movement->x = -1;
    }
    else if (s == Side::N)
    {
        movement->x >= 0 ? movement->x = 1 : movement->x = -1;
        if (!others.empty())
            movement->y = 0;
        else
            movement->y = 1;
    }
    else if (s == Side::S)
    {
        movement->x >= 0 ? movement->x = 1 : movement->x = -1;
        if (!others.empty())
            movement->y = 0;
        else
            movement->y = -1;
    }
}



























