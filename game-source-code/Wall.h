// Wall.h
#ifndef WALL_H
#define WALL_H

#include <raylib-cpp.hpp>

class Wall {
public:
    Wall(const Rectangle& rect, Color color = PINK);
    Rectangle rect;
    bool active;
    Color color;
};

#endif // WALL_H
