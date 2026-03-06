#ifndef CELL_HPP
#define CELL_HPP

#include "Types.h"
#include "Vec2.hpp"
#include "pch.h"
#include <SDL3/SDL_mouse.h>

#include <map>

enum class CellType {Prey, Predator};
enum class CellState {Default, Escape, Attack};

class Cell {

public:
    Cell(int id, Pos origin, Size size, CellClass config);
    ~Cell();

    void    draw(SDL_Renderer* renderer);
    void    setPos(Pos pos);

    void    emptyOthers();
    void    updateMovement();
    void    updatePos();

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
    SDL_Circle       m_shape;

    Pos             m_pos;
    Vec2            m_movement;

    int             m_id;
    SDL_Color       m_color;
    CellType        m_type;
    CellState       m_state = CellState::Default;
    float           m_speed;
    // int             m_mult;
    // int             m_energy;
    int             m_vision;

    std::vector<std::pair<float, Cell*>> m_others;


    SDL_Circle  m_debug_circle;
    bool        m_debug = false;

};

#endif // !ve

