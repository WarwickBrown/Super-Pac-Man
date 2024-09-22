#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <raylib-cpp.hpp>

class Maze {
public:
    struct Wall {
        Rectangle rect;
        bool active;
        Color color;
        Wall(const Rectangle& rect, Color color) : rect(rect), active(true), color(color) {}
    };

    Maze();  // Constructor to initialize the maze.
    ~Maze(); // Destructor to clean up any allocated memory (if applicable).

    // Function to draw the maze on the screen.
    void draw() const;

    // Checks if a given position in the maze (x, y coordinates) is a wall.
    bool isWall(int x, int y) const;

    // Returns the width of the maze (currently unused, but can be extended).
    int getWidth() const;

    // Returns the height of the maze (currently unused, but can be extended).
    int getHeight() const;

    // Returns the X-coordinate of Pac-Man's starting position in the maze.
    int getStartX() const;

    // Returns the Y-coordinate of Pac-Man's starting position in the maze.
    int getStartY() const;

    // Initializes custom walls in the maze by creating and positioning rectangle objects.
    void initialiseCustomWalls();

    // Checks if Pac-Man is colliding with a specific rectangle in the maze.
    bool isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const;

    // Checks if Pac-Man is colliding with any of the custom walls in the maze.
    bool isWall(int pacmanX, int pacmanY, int pacmanRadius) const;

    //CellType getCellType(int x, int y) const;  // Returns the type of cell at the position
    bool isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const;

    const std::vector<Maze::Wall>& getWalls() const;

    std::vector<Maze::Wall>& getWalls();

private:
    std::vector<Wall> walls;
    int width;   // Width of the maze
    int height;  // Height of the maze
    int startX, startY;  // Starting position for Pac-Man
};

#endif // MAZE_H
