#ifndef CONFIG_H
# define CONFIG_H

#include "Types.h"
#include <SDL3/SDL.h>
#include <string>
#include <yaml-cpp/yaml.h>



struct AppConfig {

    float       window_width;
    float       window_height;
    std::string window_name;

    Pos         playground_margin;
    FSize       playground_size;
    Pos         playground_pos;
    Pos         playground_limit;

    float       cell_size;
    FSize       s_cell_size;

    std::string simulation_name;
    float       simulation_speed;
    float       f; //friction
    float       f_ratio;
    float       f_time;
};

struct SimConfig {
    int         id = 0;
    std::string name = "";
    int         prey_number = 0;
    int         predator_number = 0;
};

void    fillAppConfig(YAML::Node&, AppConfig&);
void    fillSimConfig(YAML::Node&, std::vector<SimConfig>&);
void    printConfig(AppConfig&);


namespace Color_Palette {
	inline const SDL_Color MAIN_BACKGROUND = { 20,  20,  20, 255 };
	inline const SDL_Color SCOPE_BACKGROUND = { 50,  50,  50, 255 };

	inline const SDL_Color GREY_LINES = { 80,  80,  80, 255 };
	inline const SDL_Color GRID_LINES = { 120,  120,  120, 255 };
	inline const SDL_Color SELECTED_GRID_LINES = { 220,  220,  220, 255 };
	inline const SDL_Color TEXT	   = { 255, 255, 255, 255 };

	inline const SDL_Color PLAIN    = { 160, 210, 45, 255 };
	inline const SDL_Color FOREST   = {  55, 130,  55, 255 };
	inline const SDL_Color ICE      = { 50, 135, 245, 255 };
	inline const SDL_Color DESERT   = { 235, 150, 150, 255 };
	inline const SDL_Color MOUNTAIN = { 140, 145, 160, 255 };

	inline const SDL_Color PURPLE_CHARACTER = {170, 51, 106, 255};


    inline const SDL_Color PREY     = { 120, 230, 120, 255 };
    inline const SDL_Color PREDATOR = { 210, 45, 45, 255 };
}



#endif
