#pragma once

/** float x, y;
 */

enum class CellType;
struct SDL_Color;


struct Pos {
  float x, y;
};

/** int w, h;
 */
struct Size {
  int w, h;
};

/** int i, j;
 */
struct GridIdx {
  int i, j;
};

/** int col, row;
 */
struct GridSize {
  int col, row;
};

struct Vec2 {
    float x, y;
};



