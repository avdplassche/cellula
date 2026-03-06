#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <algorithm>



Cell::Cell(int id, Pos origin, Size size, CellClass config): m_movement(0.0f, 0.0f) {
    (void)size;
    cellCreationAssert(config);
    m_id = id;
    // float w = size.w;
    // float h = size.h;
    // m_rect_shape = {origin.x, origin.y, w, h};
    m_shape = {origin.x, origin.y, Window_Config::CELL_SIZE};
    m_type = config.type;
    m_speed = getRandomFloat(config.speed[0], config.speed[1]) / 100;
    m_vision = getRandomInt(config.vision[0], config.vision[1]);
    m_pos = origin;
    m_color = config.color;
    m_movement = {0,0};
}

Cell::~Cell() {}

void    Cell::draw(SDL_Renderer* renderer) {
    setRenderDrawColor(renderer, m_color);
    // SDL_RenderFillRect(renderer, &m_rect_shape);
    DrawCircle(renderer, m_shape.x, m_shape.y, Window_Config::CELL_SIZE);
    // if (m_debug)
    // {
    //     DrawCircle(renderer,
    //                m_debug_circle.x,
    //                m_debug_circle.y,
    //                m_debug_circle.radius);
    // }
    // else
    // {
    //     setRenderDrawColor(renderer, Color_Palette::GREY_LINES);
    //     DrawCircle(renderer,
    //               m_shape.x + m_shape.w / 2,
    //               m_shape.y + m_shape.h / 2,
    //                m_vision);
    // }
}

void    Cell::setPos(Pos pos) {
    m_shape.x = pos.x;
    m_shape.y = pos.y;

    // m_rect_shape.x = pos.x;
    // m_rect_shape.y = pos.y;
    m_pos = pos;
}

////    Update Simulation

void    Cell::emptyOthers() {
    m_others.clear();
}

void    Cell::setState(CellState state) {
    this->m_state = state;
}

void    Cell::setOther(float distance, Cell* cell) {
    m_others.push_back({distance, cell});
}

void    Cell::updateMovement() {
    if (m_others.empty())
    {
        setState(CellState::Default);
        m_movement.setValues(0.0f, 0.0f);
        return ; // soon will need walk algo
    }
    auto other = std::min_element(m_others.begin(), m_others.end());
    m_movement.setValues(other->second->getPos().x - this->m_pos.x,
        other->second->getPos().y - this->m_pos.y);
    // Vec2 tot(0, 0);
    // for (auto cell : m_others) 
    //     tot.setValues(cell.second->getPos().x + tot.x, cell.second->getPos().y + tot.y);
    //  m_movement.setValues(tot.x / m_others.size(), tot.y / m_others.size());
    if (m_type == CellType::Prey && other->second->getType() == CellType::Predator)
    {
        m_movement.normalize();
        m_movement.inverse();
    }
    else if (m_type == CellType::Predator && other->second->getType() == CellType::Prey)
    {
        m_movement.normalize();

    }
    // setPos(m_pos + m_movement);
    updatePos();
    setDebugShape();
}

void    Cell::updatePos() {
    m_pos.x += m_movement.x * m_speed * Window_Config::SPEED;
    m_pos.y += m_movement.y * m_speed * Window_Config::SPEED;
    setPos(m_pos);
}


////    Getters


Pos     Cell::getPos() const { return m_pos;};

int     Cell::getID() const { return m_id;};

int     Cell::getVision() const { return m_vision;};

CellType    Cell::getType() const { return m_type;};

std::vector<std::pair<float, Cell*>> Cell::getMap() const {
    return this->m_others;
}

void    Cell::setDebugShape() {
    m_debug = true;
    // m_debug_circle.x = m_shape.x + m_shape.w / 2;
    // m_debug_circle.y = m_shape.y + m_shape.h / 2;
    m_debug_circle.radius = m_vision;
};

