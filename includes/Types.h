#pragma once

enum class CellType;
struct SDL_Color;

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

// struct Vec2 {
//     float x, y;
// };
//

struct Pos {
    float x, y;
    // Pos   operator+(Vec2& v) { return {x + v.x, y + v.y};};
};

struct SDL_Circle {
    float   x, y;
    int     radius;
};

