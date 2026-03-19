#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <algorithm>
#include <iomanip>



Cell::Cell(AppConfig& appConfig, int id, Pos origin, int size, CellClass cellConfig): m_movement(0.0f, 0.0f) {
    m_size = size;
    cellCreationAssert(cellConfig);
    m_id = id;
    // float w = size.w;
    // float h = size.h;
    // m_rect_shape = {origin.x, origin.y, w, h};
    m_shape = {origin.x, origin.y, m_size};
    m_type = cellConfig.type;
    m_speed = getRandomFloat(cellConfig.speed[0], cellConfig.speed[1]) / 100;
    m_vision = getRandomInt(cellConfig.vision[0], cellConfig.vision[1]);
    m_pos = origin;
    m_color = cellConfig.color;
    m_movement = {0,0};
    m_friction = appConfig.f;
}

Cell::~Cell() {}

void    Cell::draw(SDL_Renderer* renderer) {
    setRenderDrawColor(renderer, m_color);
    // SDL_RenderFillRect(renderer, &m_rect_shape);
    DrawCircle(renderer, m_shape.x, m_shape.y, m_shape.radius);
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
    //               m_shape.x,
    //               m_shape.y,
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

void    Cell::updateMovement(AppConfig& config) {
    m_last_movement = {m_movement.x, m_movement.y};
    if (m_others.empty())
    {

        mUpdateSoloRoutine(config);
        return ; // soon will need walk algo
    }
    if (m_type == CellType::Prey && m_pos.x <= config.playground_pos.x + 1)
    {
        m_movement.setValues(1, 0);
        return;
    }
    auto other = std::min_element(m_others.begin(), m_others.end());
    m_movement.setValues(other->second->getPos().x - this->m_pos.x,
        other->second->getPos().y - this->m_pos.y);
    if (m_type == CellType::Prey && other->second->getType() == CellType::Predator)
    {
        m_movement.normalize();
        m_movement.inverse();
    }
    else if (m_type == CellType::Predator && other->second->getType() == CellType::Prey)
    {
        m_movement.normalize();
    }
    setDebugShape();
}

void    Cell::mUpdateSoloRoutine(AppConfig& config) {

    // set the friction to max if the cell had a state
    if (m_state != CellState::Default)
    {
        m_friction = config.f;
        setState(CellState::Default);
    }
    normalizeFriction(&m_last_movement, m_friction);
    // if (m_last_movement.x > 0)
    // {
    //     m_last_movement.x -= m_friction;
    //     if (m_last_movement.x < 0)
    //         m_last_movement.x = 0;
    // }
    // else if (m_last_movement.x < 0)
    // {
    //     m_last_movement.x += m_friction;
    //     if (m_last_movement.x > 0)
    //         m_last_movement.x = 0;
    // }
    // if (m_last_movement.y > 0)
    // {
    //     m_last_movement.y -= m_friction;
    //     if (m_last_movement.y < 0)
    //         m_last_movement.y = 0;
    // }
    // else if (m_last_movement.y < 0)
    // {
    //     m_last_movement.y += m_friction;
    //     if (m_last_movement.y > 0)
    //         m_last_movement.y = 0;
    // }
    //
    m_movement.setValues(m_last_movement.x, m_last_movement.y);
    m_friction /= config.f_ratio;
    // m_friction -= m_friction / config.f_time;
    // if (m_friction < 0)
    if (m_friction < config.f / config.f_time)
        m_friction = 0;
    if (m_type == CellType::Predator)
        return;
    std::cout << "State : " << (int)m_state << '\n';
    std::cout << "Friction : " << std::setprecision(8) << m_friction << '\n';
    std::cout << "Movement : [" << std::setprecision(8)<< m_last_movement.x << ','<< m_last_movement.y << "]\n";
    // m_movement.setValues(0.0f, 0.0f);
}



void    Cell::updatePos(AppConfig& config) {
    if (m_pos.x <= config.playground_margin.x
        || m_pos.x >= config.playground_limit.x)
    {
        m_movement.x = 0;
        m_movement.y >= 0 ? m_movement.y = 1 : m_movement.y == -1;
    }
    if (m_pos.y <= config.playground_margin.y 
        || m_pos.y >= config.playground_limit.y)
    {
        m_movement.y = 0;
        m_movement.x >= 0 ? m_movement.x = 1 : m_movement.x == -1;
    }
    m_pos.x += m_movement.x * m_speed * config.simulation_speed;
    m_pos.y += m_movement.y * m_speed * config.simulation_speed;
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
    m_debug_circle.x = m_shape.x;
    m_debug_circle.y = m_shape.y;
    m_debug_circle.radius = m_vision;
};

