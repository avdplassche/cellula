#include "Playground.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"



Playground::Playground(SimConfig conf){ 

    m_container_rect = {Window_Config::PLAYGROUND_POS_X,
                        Window_Config::PLAYGROUND_POS_Y,
                        Window_Config::PLAYGROUND_WIDTH,
                        Window_Config::PLAYGROUND_HEIGHT};

    m_cell_number = conf.predator_number + conf.prey_number ;
    m_v_cells.reserve(m_cell_number);

    for (int i = 0; i < conf.prey_number; i++)
    {
        Cell *c = new Cell(getRandomPos(),
                           Window_Config::S_CELL_SIZE,
                           preyConfig());

        m_v_cells.push_back(c);
    }
    for (int i = 0; i < conf.predator_number; i++)
    {
        Cell *c = new Cell(getRandomPos(),
                           Window_Config::S_CELL_SIZE,
                            predatorConfig());
        m_v_cells.push_back(c);
    }

}

Playground::~Playground(){
    for (auto &c : m_v_cells)
    {
        delete c;
    }
}

void    Playground::update() {
    for (auto &c : m_v_cells)
    {
        c->updatePos();
    }

}

void    Playground::draw(SDL_Renderer *renderer) {
    // setRenderDrawColor(renderer, Color_Palette::GRID_LINES);
    // SDL_RenderRect(renderer, &m_container_rect);
    for (auto &cell : m_v_cells)
        cell->draw(renderer);
}









