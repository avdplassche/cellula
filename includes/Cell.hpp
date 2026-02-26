#ifndef CELL_HPP
#define CELL_HPP

#include "Types.h"
#include "pch.h"

enum class CellType {Prey, Predator};

class Cell {

public:
    // Cell();
    Cell(Pos origin, Size size, CellClass config);
    ~Cell();

    void    draw(SDL_Renderer* renderer);
    void    setPos(Pos pos);
    void    updatePos();


private:

    SDL_FRect   m_shape;
    Pos         m_pos;


    SDL_Color   m_color;
    CellType    m_type;
    int         m_speed;
    // int         m_mult;
    // int         m_energy;
    int         m_vision;
    int         m_movement;
};

#endif // !ve

