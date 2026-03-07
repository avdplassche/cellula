#pragma once

enum class CellType;
struct SDL_Color;

/** int w, h;
 */
struct Size {
  int w, h;
};

/** int w, h;
 */
struct FSize {
  float w, h;
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

struct Pos {
    float x, y;
};

struct SDL_Circle {
    float   x, y;
    int     radius;
};

