#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Reader.h"

class Maze : public Reader {
public:
    struct Wall {
        Rectangle rect;
        bool active;
        Color color;
        Wall(const Rectangle& rect, Color color) : rect(rect), active(true), color(color) {}
    };

    Maze();  // Constructor to initialise the maze.
    ~Maze(); // Destructor to clean up any allocated memory (if applicable).

    int getHeight() const { return height; }

    // Getter function to return the starting X position of Pac-Man in the maze.
    int getStartX() const { return startX; }

    // Getter function to return the starting Y position of Pac-Man in the maze.
    int getStartY() const { return startY; }

    // Initializes custom walls in the maze by creating and positioning rectangle objects.
    void initialiseCustomWalls();

    // Checks if Pac-Man is colliding with any of the custom walls in the maze.
    bool isWall(int pacmanX, int pacmanY, int pacmanRadius) const;

    //CellType getCellType(int x, int y) const;  // Returns the type of cell at the position
    bool isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const;

    const std::vector<Maze::Wall>& getWalls() const { return walls; }

    std::vector<Maze::Wall>& getWalls() { return walls; }

private:
    std::vector<Wall> walls;
    int width;   // Width of the maze
    int height;  // Height of the maze
    int startX, startY;  // Starting position for Pac-Man
};

#endif // MAZE_H
