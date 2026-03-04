#include "Cell.hpp"
#include "config.h"
#include "pch.h"



Cell::Cell(int id, Pos origin, Size size, CellClass config) {

    cellCreationAssert(config);
    m_id = id;
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
    SDL_RenderFillRect(renderer, &m_shape);
    if (m_debug)
    {
        DrawCircle(renderer,
                   m_debug_circle.x,
                   m_debug_circle.y,
                   m_debug_circle.radius);
    }
    else
    {
        setRenderDrawColor(renderer, Color_Palette::GREY_LINES);
        DrawCircle(renderer,
                  m_shape.x + m_shape.w / 2,
                  m_shape.y + m_shape.h / 2,
                   m_vision);
    }
}

void    Cell::setPos(Pos pos) {
    m_shape.x = pos.x;
    m_shape.y = pos.y;
    m_pos = pos;
}

void    Cell::setState(CellState state) {
    this->m_state = state;
}


void    Cell::setOther(Cell* cell, CellType type) {
    m_map[cell] = type;
}

void    Cell::updatePos() {

}

Pos     Cell::getPos() const { return m_pos;};

int     Cell::getID() const { return m_id;};

int     Cell::getVision() const { return m_vision;};

CellType    Cell::getType() const { return m_type;};


std::unordered_map<Cell*, CellType> Cell::getMap() const {
    return this->m_map;
}

void    Cell::setDebugShape() {
    m_debug = true;
    m_debug_circle.x = m_shape.x + m_shape.w / 2;
    m_debug_circle.y = m_shape.y + m_shape.h / 2;
    m_debug_circle.radius = m_vision;
};

