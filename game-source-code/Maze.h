#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <raylib-cpp.hpp>

// Enum to define different cell types in the maze
enum class CellType {
    Empty,  // Walkable space
    Wall,   // Wall blocking movement
    Fruit,  // Fruit to be collected
    Key     // Key to unlock doors
};

// Cell structure to represent each cell in the maze
struct Cell {
    CellType type;  // Type of the cell (Empty, Wall, Fruit, Key)
    bool isVisited; // To keep track of visited cells if needed

    Cell(CellType type = CellType::Empty) : type(type), isVisited(false) {}
};

class Maze {
public:
    Maze();  // Constructor
    ~Maze(); // Destructor

    void draw() const;  // Draws the maze on the screen
    bool isWall(int x, int y) const;  // Checks if the given position is a wall
    CellType getCellType(int x, int y) const;  // Returns the type of cell at the position
    int getWidth() const;  // Returns maze width
    int getHeight() const; // Returns maze height
    int getStartX() const; // Returns starting X position for Pac-Man
    int getStartY() const; // Returns starting Y position for Pac-Man
    const std::vector<Rectangle>& getWalls() const;  // To access the walls vector
    void initializeCustomWalls();  // Function to add custom rectangles
    bool isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const;
    bool isWall(int pacmanX, int pacmanY, int pacmanRadius) const;

private:
    std::vector<std::vector<Cell>> layout;  // 2D grid representing the maze
    std::vector<Rectangle> walls;  // Vector to hold all wall rectangles
    int width;   // Width of the maze
    int height;  // Height of the maze
    int startX, startY;  // Starting position for Pac-Man

    // void initializeDefaultMaze();  // Initializes a default maze layout
};

#endif // MAZE_H
