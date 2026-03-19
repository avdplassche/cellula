#ifndef CELL_HPP
#define CELL_HPP

#include "App.hpp"
#include "Types.h"
#include "Vec2.hpp"
#include "config.h"
#include "pch.h"
#include <SDL3/SDL_mouse.h>

#include <map>

enum class CellType {Prey, Predator};
enum class CellState {Default, Escape, Attack};

class Cell {

public:
    Cell(AppConfig&, int id, Pos origin, int size, CellClass config);
    ~Cell();

    void    draw(SDL_Renderer* renderer);
    void    setPos(Pos pos);

    void    emptyOthers();
    void    updateMovement(AppConfig&);
    void    updatePos(AppConfig&);

    void    setState(CellState);
    void    setOther(Cell*, CellType);

    void    setOther(float distance, Cell* cell);
    int     getID() const;
    Pos     getPos() const;
    int     getVision() const;

    CellType    getType() const;
    std::vector<std::pair<float, Cell*>> getMap() const;

    void    setDebugShape();

private:
    // SDL_FRect       m_rect_shape;
    SDL_Circle      m_shape;
    int             m_size;

    Pos             m_pos;
    Vec2            m_movement;
    Pos             m_last_movement;
    float           m_friction;
    

    int             m_id;
    SDL_Color       m_color;
    CellType        m_type;
    CellState       m_state = CellState::Default;
    float           m_speed;
    // int             m_mult;
    // int             m_energy;
    int             m_vision;

    std::vector<std::pair<float, Cell*>> m_others;


    SDL_Circle      m_debug_circle;
    bool            m_debug = false;

    void            mUpdateSoloRoutine(AppConfig& config);
};

#endif 
