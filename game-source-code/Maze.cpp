#include "Maze.h"
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

// Constructor
Maze::Maze() : width(0), height(0), startX(1), startY(1) {
    initializeDefaultMaze();  // Initialize a simple default maze for testing
}

// Destructor
Maze::~Maze() {
    // Nothing to clean up for now as vector manages its own memory
}

// Initializes a default maze layout for testing
void Maze::initializeDefaultMaze() {
    // Simple 10x10 maze layout for testing purposes
    width = 10;
    height = 10;
    layout = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell(CellType::Empty)));

    // Set maze walls
    for (int i = 0; i < width; i++) {
        layout[0][i] = Cell(CellType::Wall);
        layout[height - 1][i] = Cell(CellType::Wall);
    }
    for (int i = 0; i < height; i++) {
        layout[i][0] = Cell(CellType::Wall);
        layout[i][width - 1] = Cell(CellType::Wall);
    }

    // Make sure the start position at (1, 1) is not a wall
    layout[1][1] = Cell(CellType::Empty);  // Set the start position for Pac-Man to empty space
}

// Draws the maze on the screen
// We might need to make vertical and horizontal walls for pixel system
// Maybe two types of wall, wall vert and wall hori
void Maze::draw() const {
    DrawRectangle(0, 0, 10, 900, raylib::Color::DarkBlue());
    DrawRectangle(0, 0, 1600, 10, raylib::Color::DarkBlue());
    DrawRectangle(1590, 0, 10, 900, raylib::Color::DarkBlue());
    DrawRectangle(0, 890, 1600, 10, raylib::Color::DarkBlue());
}

// Checks if the given position is a wall
bool Maze::isWall(int x, int y) const {
    raylib::Rectangle placement{x, y, 1, 1};
    raylib::Vector2 posi{x, y};
    if(placement.CheckCollision(posi, 1))
    {
        return false;
    }
    return true;
}

// Returns the type of cell at the position
CellType Maze::getCellType(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return CellType::Wall;
    return layout[y][x].type;
}

// Returns maze width
int Maze::getWidth() const {
    return width;
}

// Returns maze height
int Maze::getHeight() const {
    return height;
}

// Returns starting X position for Pac-Man
int Maze::getStartX() const {
    return startX;
}

// Returns starting Y position for Pac-Man
int Maze::getStartY() const {
    return startY;
}

