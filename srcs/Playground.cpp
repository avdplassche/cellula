#include "Playground.hpp"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <SDL3/SDL_render.h>
#include <cassert>
#include <cmath>
#include <iterator>

Playground::Playground(){}


Playground::~Playground(){
    for (auto &c : m_x_list)
    {
        delete c;
    }
}

void    Playground::init(SDL_Renderer *renderer, AppConfig& app_config, SimConfig& sim_config) {
    m_app_config = app_config;
    std::cout << "Nb Predators : " <<   sim_config.predator_number << '\n';
    std::cout << "Nb Preys : " <<   sim_config.prey_number << '\n';
    m_renderer = renderer;
    m_texture = SDL_CreateTexture(renderer,
                                  SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET,
                                  m_size.w,
                                  m_size.h);
    m_size = app_config.playground_size;
    m_container_rect.w = app_config.playground_size.w + app_config.cell_size * 2;
    m_container_rect.h = app_config.playground_size.h + + app_config.cell_size * 2;
    m_container_rect.x = app_config.playground_pos.x - app_config.cell_size;
    m_container_rect.y = app_config.playground_pos.y - app_config.cell_size;
    m_cell_number = sim_config.predator_number + sim_config.prey_number;
    int cell_id = 0;

    for (int i = 0; i < sim_config.prey_number; i++)
    {
        Cell *c = new Cell(app_config, cell_id, getRandomPos(m_app_config),
                           app_config.cell_size,
                           preyConfig());
        m_x_list.push_back(c);
        m_y_list.push_back(c);
        cell_id++;
    }
    for (int i = 0; i < sim_config.predator_number; i++){
        Cell *c = new Cell(app_config, cell_id, getRandomPos(m_app_config),
                           app_config.cell_size,
                            predatorConfig());
        m_x_list.push_back(c);
        m_y_list.push_back(c);
        cell_id++;
    }

    update();
}

void    Playground::update() {
    for (auto& cell : m_x_list)
        cell->emptyOthers();
    m_sortLists();
    m_checkCollisions(m_x_list, 'x');
    m_checkCollisions(m_y_list, 'y');
    for (auto& cell : m_x_list)
    {
        cell->updateMovement(m_app_config);
        cell->updatePos(m_app_config);
    }
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


void    Playground::draw() {
    SDL_SetRenderTarget(m_renderer, m_texture);
    SDL_RenderClear(m_renderer);
    setRenderDrawColor(m_renderer, Color_Palette::GRID_LINES);
    SDL_RenderRect(m_renderer, &m_container_rect);
    for (auto &cell : m_x_list)
        cell->draw(m_renderer);
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderTexture(m_renderer, m_texture, NULL, NULL);
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



