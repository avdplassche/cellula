#include "Cell.hpp"
#include "config.h"
#include "pch.h"


Cell::Cell(Pos origin, Size size, CellClass config) {
    float w = size.w;
    float h = size.h;
    m_shape = {origin.x, origin.y, w, h};
    m_type = config.type;
    
    m_speed = getRandomInt(config.speed[0], config.speed[1]);
    m_vision = getRandomInt(config.vision[0], config.vision[1]);
    m_pos = origin;
    m_color = config.color;
    m_movement = 0;
}

Cell::~Cell() {}

void    Cell::draw(SDL_Renderer* renderer) {
    setRenderDrawColor(renderer, m_color);
    SDL_RenderRect(renderer, &m_shape);
}

void    Cell::setPos(Pos pos) {
    m_shape.x = pos.x;
    m_shape.y = pos.y;
    m_pos = pos;
}

void    Cell::updatePos() {

}


