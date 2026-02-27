#ifndef CONFIG_H
# define CONFIG_H

#include "Types.h"
#include <SDL3/SDL.h>

namespace Window_Config {
	inline constexpr int WIDTH = 1920;
	inline constexpr int HEIGHT = 1200;
	inline constexpr const char* WINDOW_NAME = "Cellula";
	inline constexpr int CELL_SIZE = 4;
    inline constexpr int GRID_W = WIDTH / CELL_SIZE;
	inline constexpr int GRID_H = HEIGHT / CELL_SIZE;
    inline constexpr int MARGIN_X = 40;
    inline constexpr int MARGIN_Y = 40;
    inline constexpr int PLAYGROUND_WIDTH = WIDTH - MARGIN_X * 2;
    inline constexpr int PLAYGROUND_HEIGHT = HEIGHT - MARGIN_Y * 2 - 26;

	// inline constexpr int GRID_W = 1024 / CELL_SIZE;
	// inline constexpr int GRID_H = 1024 / CELL_SIZE;
	// inline constexpr int PLAYGROUND_WIDTH = GRID_W * CELL_SIZE;
	// inline constexpr int PLAYGROUND_HEIGHT = GRID_H * CELL_SIZE;
    inline constexpr int PLAYGROUND_POS_X = WIDTH / 2.0 - PLAYGROUND_WIDTH / 2.0;
    inline constexpr int PLAYGROUND_POS_Y = HEIGHT / 2.0 - PLAYGROUND_HEIGHT / 2.0;
    inline constexpr Size S_CELL_SIZE = {CELL_SIZE, CELL_SIZE};


}

namespace Grid_Config {

	inline constexpr int MARGIN = 50;
}

namespace Color_Palette {
	inline const SDL_Color MAIN_BACKGROUND = { 30,  30,  30, 255 };
	inline const SDL_Color SCOPE_BACKGROUND = { 50,  50,  50, 255 };
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
