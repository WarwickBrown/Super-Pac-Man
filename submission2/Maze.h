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

    void loadFromFile(const std::string& filename); // Loads maze layout from file
    void draw() const;  // Draws the maze on the screen
    bool isWall(int x, int y) const;  // Checks if the given position is a wall
    CellType getCellType(int x, int y) const;  // Returns the type of cell at the position
    int getWidth() const;  // Returns maze width
    int getHeight() const; // Returns maze height
    int getStartX() const; // Returns starting X position for Pac-Man
    int getStartY() const; // Returns starting Y position for Pac-Man
    int getGhostStartX() const; // Returns starting X position for Ghost
    int getGhostStartY() const; // Returns starting Y position for Ghost

private:
    std::vector<std::vector<Cell>> layout;  // 2D grid representing the maze
    int width;   // Width of the maze
    int height;  // Height of the maze
    int startX, startY;  // Starting position for Pac-Man
    int ghostStartX, ghostStartY;  // Starting position for the ghost(s)

    void initializeDefaultMaze();  // Initializes a default maze layout
};

#endif // MAZE_H
