#include "Cell.hpp"
#include "config.h"
#include "logger.h"
#include "pch.h"
#include <SDL3/SDL_pixels.h>
#include <algorithm>
#include <iomanip>



Cell::Cell(AppConfig& appConfig, int id, Pos origin, int size, CellClass cellConfig): m_movement(0.0f, 0.0f) {
    m_size = size;
    cellCreationAssert(cellConfig);
    m_id = id;
    m_shape = {origin.x, origin.y, m_size};
    m_type = cellConfig.type;
    m_speed = getRandomFloat(cellConfig.speed[0], cellConfig.speed[1]) / 100;
    m_vision = getRandomInt(cellConfig.vision[0], cellConfig.vision[1]);
    m_pos = origin;

    m_shape.x = m_pos.x;
    m_shape.y = m_pos.y;

    m_color = cellConfig.color;

    m_movement = {0,0};
    m_friction = appConfig.f;
}

Cell::~Cell() {}

void    Cell::draw(SDL_Renderer* renderer) {
    setRenderDrawColor(renderer, m_color);
    DrawCircle(renderer, m_shape.x, m_shape.y, m_shape.radius);
}

void    Cell::setPos(Pos pos) {
    m_shape.x = pos.x;
    m_shape.y = pos.y;
    m_pos = pos;
}

////    Update Simulation

void    Cell::setState(CellState state) {
    this->m_state = state;
}

void    Cell::setOther(float distance, Cell* cell) {
    m_others.push_back({distance, cell});
}

//// Playground Update

void    Cell::emptyOthers() {
    m_others.clear();
}

void    Cell::updateMovement(AppConfig& config) {
    m_last_movement = {m_movement.x, m_movement.y};
    if (m_others.empty())
        mUpdateSoloRoutine(config);
    else
        mUpdateDependentRoutine();
}

void    Cell::checkMovementsLimits(AppConfig& config) {
    Corner corner;
    Side side;
    if (checkCorners(config, &m_pos, corner))
        handleCellCorners(config, &m_movement, m_others, corner);
    else if (checkLimits(config, &m_pos, side))
        handleCellLimits(config, &m_movement, m_others, side);
}

void    Cell::checkMovementsCollisions(AppConfig& config) {
    (void)config;
}

void    Cell::updatePos(AppConfig& config) {
    m_pos.x += m_movement.x * m_speed * config.simulation_speed;
    m_pos.y += m_movement.y * m_speed * config.simulation_speed;
    m_shape.x = m_pos.x;
    m_shape.y = m_pos.y;
}

int    Cell::checkDeath() {

    if (m_type == CellType::Predator)
        return 0;
    for (auto& other : m_others)
    {
        if (other.second->getType() == CellType::Prey)
            continue ;

        float dx = other.second->getPos().x - m_pos.x;
        float dy = other.second->getPos().y - m_pos.y;
        if ((dx * dx + dy * dy) <= m_size)
        {
            m_isAlive = false;
            return 1;
        }
        return 0;
    }
    return 0;
}


////    Getters

bool    Cell::isAlive() const { return m_isAlive; };

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

