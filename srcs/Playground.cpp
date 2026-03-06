#include "Playground.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <cassert>
#include <cmath>
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
        cell_id++;
    }
    update();
}

Playground::~Playground(){
    for (auto &c : m_x_list)
    {
        delete c;
    }
}

void    Playground::update() {
    for (auto& cell : m_x_list)
        cell->emptyOthers();
    m_sortLists();
    m_checkCollisions(m_x_list, 'x');
    m_checkCollisions(m_y_list, 'y');
    for (auto& cell : m_x_list)
        cell->updateMovement();
}


void    Playground::m_checkCollisions(std::list<Cell*> list, char axe){
    assert(axe == 'x' || axe == 'y');
    for (auto it = list.begin(); it != list.end(); ++it) {
        auto current = *it;
        auto forward_it = std::next(it);

        while (forward_it != list.end()) {
            auto other = *forward_it;
            if ((axe == 'x' && other->getPos().x - current->getPos().x > current->getVision())
                ||(axe == 'y' && other->getPos().y - current->getPos().y > current->getVision()))
                break;
            setCollision(current, other);
            ++forward_it;
        }
        if (it != list.begin()) {
            auto backward_it = std::prev(it);
            while (true) {
                auto other = *backward_it;
                if ((axe == 'x' && current->getPos().x - other->getPos().x > current->getVision())
                    || (axe == 'y' && current->getPos().y - other->getPos().y > current->getVision()))
                    break;
                setCollision(current, other);
                if (backward_it == list.begin())
                    break;
                --backward_it;
            }
        }
    }
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





