#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "Types.h"
#include "config.h"
#include "pch.h"
#include <SDL3/SDL_render.h>
#include <unordered_map>
// #include "Cell.hpp"

class Playground {

public:
    Playground();
    // Playground(AppConfig& app_config, SimConfig sim_config);
    ~Playground();
    void                init(SDL_Renderer *renderer, AppConfig& app_config, SimConfig& sim_config);
    void                update();
    double              getUpdateTime() const;
    void                draw();

private:
    SDL_Texture         *m_texture = NULL;
    SDL_FRect           m_render_rect;
    SDL_FRect           m_container_rect;
    SDL_Renderer        *m_renderer = NULL;
    std::list<Cell*>    m_x_list;
    std::list<Cell*>    m_y_list;
    int                 m_cell_number;
    AppConfig           m_app_config;
    FSize               m_size;

    void                m_initCellClassMap();
    void                m_checkCollisions(std::list<Cell*>, char);
    void                m_sortLists();
    
    double              m_updateTime;
    // const std::chrono::duration<double, std::milli> m_time;
    std::unordered_map<std::string, CellClass>    m_cellClassMap;
};

void    printCellXContainer(std::list<Cell *>& list);


#endif // !PLAYGROUND_HPP
