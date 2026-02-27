#include "Playground.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <iterator>



Playground::Playground(SimConfig conf){ 

    m_container_rect.w = Window_Config::PLAYGROUND_WIDTH;
    m_container_rect.h = Window_Config::PLAYGROUND_HEIGHT;
    m_container_rect.x = Window_Config::PLAYGROUND_POS_X;
    m_container_rect.y = Window_Config::PLAYGROUND_POS_Y;
    m_cell_number = conf.predator_number + conf.prey_number;
    int cell_id = 0;

    for (int i = 0; i < conf.prey_number; i++)
    {
        Cell *c = new Cell(cell_id, getRandomPos(),
                           Window_Config::S_CELL_SIZE,
                           preyConfig());
        m_x_list.push_back(c);
        m_y_list.push_back(c);
        cell_id++;
    }
    for (int i = 0; i < conf.predator_number; i++){
        Cell *c = new Cell(cell_id, getRandomPos(),
                            Window_Config::S_CELL_SIZE,
                            predatorConfig());
        m_x_list.push_back(c);
        m_y_list.push_back(c);
    }
    m_sortLists();

    for (auto it = m_x_list.begin(); it != std::prev(m_x_list.end()); ++it) {
        auto current = *it;
        auto next_cell = *std::next(it);

        std::cout << current->getPos().x << " - " << next_cell->getPos().x << '\n';
        if (next_cell->getPos().x - current->getPos().x <= current->getVision()) {
            current->setDebugShape();
    }
    }
}

Playground::~Playground(){
    for (auto &c : m_x_list)
    {
        delete c;
    }
}

void    Playground::update() {
    m_checkSimulation();
    // for (auto it = m_x_list.begin(); it != std::prev(m_x_list.end()); ++it) {
    //     auto current = *it;
    //     auto next_cell = *std::next(it);
    //
    //     if (next_cell->getPos().x - current->getPos().x <= current->getVision()) {
    //         current->setDebugShape();
    // }
}

void    Playground::m_checkSimulation(){
    m_sortLists();
    // for (Cell* cell : m_x_list)
    // {
    //     cell->
    //
    // }
    // check cells's states (maybe prey list / predator list)
    // change pos
}

void    Playground::m_sortLists() {
    m_x_list.sort([](const Cell* c1, const Cell* c2){
        return (c1->getPos().x < c2->getPos().x);
    });

    m_y_list.sort([](const Cell* c1, const Cell* c2){
        return (c1->getPos().y < c2->getPos().y);
    });
}


void    Playground::draw(SDL_Renderer *renderer) {
    setRenderDrawColor(renderer, Color_Palette::GRID_LINES);
    SDL_RenderRect(renderer, &m_container_rect);
    for (auto &cell : m_x_list)
        cell->draw(renderer);
}



void    printCellXContainer(std::list<Cell *>& list) {
    std::cout << "Cell list: [ ";
    
    auto it = list.begin();
    while (it != list.end()) {
        std::cout << (*it)->getID() << " - ";

        std::cout << (*it)->getPos().x;
        if (++it != list.end()) {
            std::cout << ", ";
        }
    }
    
    std::cout << " ]" << std::endl;
}





