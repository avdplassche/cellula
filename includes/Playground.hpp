#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "config.h"
#include "pch.h"
// #include "Cell.hpp"

class Playground {

public:
    Playground(AppConfig& app_config, SimConfig sim_config);
    ~Playground();
    void                draw(SDL_Renderer *renderer);
    void                update();

private:

    SDL_FRect           m_container_rect;
    // std::vector<Cell*>  m_v_cells;
    std::list<Cell*>    m_x_list;
    std::list<Cell*>    m_y_list;
    int                 m_cell_number;
    AppConfig&          m_app_config;


    void                m_checkCollisions(std::list<Cell*>, char);
    void                m_sortLists();
};

void    printCellXContainer(std::list<Cell *>& list);


#endif // !PLAYGROUND_HPP
