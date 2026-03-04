#ifndef CELL_HPP
#define CELL_HPP

#include "Types.h"
#include "pch.h"
#include <SDL3/SDL_mouse.h>
#include <unordered_map>

enum class CellType {Prey, Predator};
enum class CellState {Default, Escape, Attack};

class Cell {

public:
    Cell(int id, Pos origin, Size size, CellClass config);
    ~Cell();

    void    draw(SDL_Renderer* renderer);
    void    setPos(Pos pos);
    void    updatePos();

    void    setState(CellState);
    void    setOther(Cell*, CellType);

    int     getID() const;
    Pos     getPos() const;
    int     getVision() const;

    CellType    getType() const;
    std::unordered_map<Cell*, CellType> getMap() const;

    void    setDebugShape();

private:
    SDL_FRect       m_shape;

    Pos             m_pos;

    int             m_id;
    SDL_Color       m_color;
    CellType        m_type;
    CellState       m_state = CellState::Default;
    int             m_speed;
    // int             m_mult;
    // int             m_energy;
    int             m_vision;
    int             m_movement;

    std::unordered_map<Cell*, CellType> m_map;


    SDL_Circle  m_debug_circle;
    bool        m_debug = false;

};

#endif // !ve

