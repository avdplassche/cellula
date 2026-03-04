#include "Playground.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
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
    m_sortLists();

}

Playground::~Playground(){
    for (auto &c : m_x_list)
    {
        delete c;
    }
}

void    Playground::update() {
    m_sortLists();
    m_checkCollisions();
    // m_updateMove();
}


void    Playground::m_checkCollisions(){

    for (auto it = m_x_list.begin(); it != m_x_list.end(); ++it) {
        auto current = *it;
        auto forward_it = std::next(it);

        while (forward_it != m_x_list.end()) {
            auto other = *forward_it;
            if (other->getPos().x - current->getPos().x > current->getVision())
                break;
            setCollision(current, other);
            ++forward_it;
        }
        if (it != m_x_list.begin()) {
            auto backward_it = std::prev(it);
            while (true) {
                auto other = *backward_it;
                if (current->getPos().x - other->getPos().x > current->getVision())
                    break;
                setCollision(current, other);
                if (backward_it == m_x_list.begin())
                    break;
                --backward_it;
            }
        }
    }
    for (auto it = m_y_list.begin(); it != m_y_list.end(); ++it) {
        auto current = *it;

        auto forward_it = std::next(it);
        while (forward_it != m_y_list.end()) {
            auto other = *forward_it;
            if (other->getPos().y - current->getPos().y > current->getVision())
                break;
            setCollision(current, other);
            ++forward_it;
        }

        if (it != m_y_list.begin()) {
            auto backward_it = std::prev(it);
            while (true) {
                auto other = *backward_it;
                if (current->getPos().y - other->getPos().y > current->getVision())
                    break;
                setCollision(current, other);
                if (backward_it == m_y_list.begin())
                    break;
                --backward_it;
            }
        }
    }
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





