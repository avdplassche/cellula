#include "Playground.hpp"
#include "logger.h"
#include "Cell.hpp"
#include "config.h"
#include "pch.h"
#include <SDL3/SDL_render.h>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <filesystem>
#include <chrono>
#include <string>
#include <typeinfo>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <fstream>

Playground::Playground(){}


Playground::~Playground(){
    for (auto &c : m_x_list)
        delete c;
}

void    Playground::init(SDL_Renderer *renderer,
                         AppConfig& app_config,
                         SimConfig& sim_config) {
    m_app_config = app_config;
    m_renderer = renderer;
    m_size = app_config.playground_size;
    m_texture = SDL_CreateTexture(renderer,
                                  SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET,
                                  m_size.w,
                                  m_size.h);
    m_container_rect.w = app_config.playground_size.w + app_config.cell_size ;
    m_container_rect.h = app_config.playground_size.h + + app_config.cell_size;
    m_container_rect.x = app_config.playground_pos.x - app_config.cell_size;
    m_container_rect.y = app_config.playground_pos.y - app_config.cell_size;
    m_render_rect = m_container_rect;
    m_cell_number = sim_config.predator_number + sim_config.prey_number;
    int cell_id = 0;
    m_initCellClassMap();
    for (int i = 0; i < sim_config.prey_number; i++)
    {
        Cell *c = new Cell(app_config, cell_id,
                           getRandomPos(m_app_config),
                           app_config.cell_size,
                           m_cellClassMap["prey"]);
        m_x_list.push_back(c);
        m_y_list.push_back(c);
        cell_id++;
    }
    for (int i = 0; i < sim_config.predator_number; i++){
        Cell *c = new Cell(app_config, cell_id, getRandomPos(m_app_config),
                           app_config.cell_size,
                           m_cellClassMap["predator"]);
        m_x_list.push_back(c);
        m_y_list.push_back(c);
        cell_id++;
    }
    update();
}


void    Playground::m_initCellClassMap() {
    YAML::Node file = YAML::LoadFile(m_app_config.cell_type_file);
    const YAML::Node& cells = file["types"];
    
    for(auto type : cells)
    {
        CellClass c;
        std::string str = type["type"].as<std::string>();
        c.type = getCellTypeByString(str);
        c.color = createSDLColour(type["color"][0].as<Uint8>(),
                                  type["color"][1].as<Uint8>(),
                                  type["color"][2].as<Uint8>());
        c.speed[0] = type["speed"][0].as<float>();
        c.speed[1] = type["speed"][1].as<float>();
        c.vision[0] = type["vision"][0].as<float>();
        c.vision[1] = type["vision"][1].as<float>();
        m_cellClassMap.insert({str, c});
    }
}

void    Playground::update() {
    for (auto& cell : m_x_list)
        cell->emptyOthers();

    const auto start{std::chrono::steady_clock::now()};

    m_sortLists();
    const auto sorting_list{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> s1{sorting_list - start};
    std::cout << "Sorting time : " << s1 << "\n";

    m_checkCollisions(m_x_list, 'x');
    m_checkCollisions(m_y_list, 'y');
    const auto check_collision{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> s2{check_collision - sorting_list};
    std::cout << "Collision check time : " << s2 << "\n";

    
    for (auto& cell : m_x_list)
        cell->updateMovement(m_app_config);
    const auto update_movement{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> s3{update_movement - check_collision};
    std::cout << "Update movement time : " << s3 << "\n";

    for (auto& cell : m_x_list)
        cell->checkMovementsLimits(m_app_config);
    const auto movement_limits{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> s4{movement_limits - update_movement};
    std::cout << "Movement limit time : " << s4 << "\n";

    // for (auto& cell : m_x_list)
    //     cell->checkMovementsCollisions(m_app_config);
    // const auto movement_collision{std::chrono::steady_clock::now()};
    // const std::chrono::duration<double, std::milli> s4{movement_limits - update_movement};
    // std::cout << "Movement limit time : " << s4 << "\n";

    for (auto& cell : m_x_list)
        cell->updatePos(m_app_config);
    const auto pos_update{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> s6{pos_update - movement_limits};
    std::cout << "Pos update time : " << s6 << "\n\n";


    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double, std::milli> total{end - start};

    std::cout << "Update total time : " << total << "\n";
    m_updateTime = total.count();
    // std::cout << "Update total time : " << total.count() << "\n\n";
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
    for (auto &cell : m_x_list)
        cell->draw(m_renderer);
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderTexture(m_renderer, m_texture, NULL, &m_render_rect);
    setRenderDrawColor(m_renderer, Color_Palette::GRID_LINES);
    SDL_RenderRect(m_renderer, &m_container_rect);
}


double      Playground::getUpdateTime() const { return m_updateTime;}


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



