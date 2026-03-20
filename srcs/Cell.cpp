#include "Cell.hpp"
#include "config.h"
#include "pch.h"
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

void    Cell::emptyOthers() {
    m_others.clear();
}

void    Cell::setState(CellState state) {
    this->m_state = state;
}

void    Cell::setOther(float distance, Cell* cell) {
    m_others.push_back({distance, cell});
}

//// Playground Update

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
    setPos(m_pos);
}


void    Cell::mUpdateSoloRoutine(AppConfig& config) {

    // set the friction to max if the cell had a state
    if (m_state != CellState::Default)
    {
        m_friction = config.f;
        setState(CellState::Default);
    }
    normalizeFriction(&m_last_movement, m_friction);
    m_movement.setValues(m_last_movement.x, m_last_movement.y);
    m_friction /= config.f_ratio;
    if (m_friction < config.f / config.f_time)
        m_friction = 0;
}

void    Cell::mUpdateDependentRoutine(){
    auto other = std::min_element(m_others.begin(), m_others.end());
    m_movement.setValues(other->second->getPos().x - this->m_pos.x,
        other->second->getPos().y - this->m_pos.y);
    if (m_type == CellType::Prey && other->second->getType() == CellType::Predator)
    {
        m_movement.normalize();
        m_movement.inverse();
        m_state = CellState::Escape;
    }
    else if (m_type == CellType::Predator && other->second->getType() == CellType::Prey)
    {
        m_movement.normalize();
        m_state = CellState::Attack;
    }
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

