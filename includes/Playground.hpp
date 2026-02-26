#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "pch.h"
#include "Cell.hpp"

class Playground {

public:
    Playground(SimConfig conf);
    ~Playground();
    void                draw(SDL_Renderer *renderer);
    void                update();

private:

    SDL_FRect           m_container_rect;
    std::vector<Cell*>   m_v_cells;
    int                 m_cell_number;
};

#endif // !PLAYGROUND_HPP
