#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <raylib-cpp.hpp>

// // Enum to define different cell types in the maze
// enum class CellType {
//     Empty,  // Walkable space
//     Wall,   // Wall blocking movement
//     Fruit,  // Fruit to be collected
//     Key     // Key to unlock doors
// };

// // Cell structure to represent each cell in the maze
// struct Cell {
//     CellType type;  // Type of the cell (Empty, Wall, Fruit, Key)
//     bool isVisited; // To keep track of visited cells if needed

//     Cell(CellType type = CellType::Empty) : type(type), isVisited(false) {}
// };

class Maze {
public:
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

    // Provides read-only access to the vector of wall rectangles.
    const std::vector<Rectangle>& getWalls() const;

    // Initializes custom walls in the maze by creating and positioning rectangle objects.
    void initialiseCustomWalls();

    // Checks if Pac-Man is colliding with a specific rectangle in the maze.
    bool isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const;

    // Checks if Pac-Man is colliding with any of the custom walls in the maze.
    bool isWall(int pacmanX, int pacmanY, int pacmanRadius) const;

    //CellType getCellType(int x, int y) const;  // Returns the type of cell at the position
    bool isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const;


private:
    std::vector<Rectangle> walls;  // Vector to hold all wall rectangles
    int width;   // Width of the maze
    int height;  // Height of the maze
    int startX, startY;  // Starting position for Pac-Man
    // void initializeDefaultMaze();  // Initializes a default maze layout
    //std::vector<std::vector<Cell>> layout;  // 2D grid representing the maze
};

#endif // MAZE_H
