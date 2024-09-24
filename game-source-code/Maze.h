#ifndef MAZE_H
#define MAZE_H

#include <vector>
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

    int getHeight() const { return height; }

    // Getter function to return the starting X position of Pac-Man in the maze.
    // This is initialized as `startX = 10` in the constructor.
    int getStartX() const { return startX; }

    // Getter function to return the starting Y position of Pac-Man in the maze.
    // This is initialized as `startY = 10` in the constructor.
    int getStartY() const { return startY; }

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
