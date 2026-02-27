#ifndef CELL_HPP
#define CELL_HPP

#include "Types.h"
#include "pch.h"

enum class CellType {Prey, Predator};

class Cell {

public:
    // Cell();
    Cell(int id, Pos origin, Size size, CellClass config);
    ~Cell();

    void    draw(SDL_Renderer* renderer);
    void    setPos(Pos pos);
    void    updatePos();


    int     getID() const;
    Pos     getPos() const;
    int     getVision() const;

    void    setDebugShape();

private:
    SDL_FRect   m_shape;

    Pos         m_pos;

    int         m_id;
    SDL_Color   m_color;
    CellType    m_type;
    int         m_speed;
    // int         m_mult;
    // int         m_energy;
    int         m_vision;
    int         m_movement;


    SDL_FRect   m_debug_rect;
    bool        m_debug = false;

};

#endif // !ve

