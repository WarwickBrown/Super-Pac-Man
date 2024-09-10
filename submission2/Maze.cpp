#include "Maze.h"
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

// Constructor
Maze::Maze() : width(0), height(0), startX(1), startY(1), ghostStartX(5), ghostStartY(5) {
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

    // // Set additional walls
    // layout[2][2] = Cell(CellType::Wall);
    // layout[3][2] = Cell(CellType::Wall);
    // layout[4][4] = Cell(CellType::Wall);
    // layout[5][6] = Cell(CellType::Wall);

    // // Set fruits and keys
    // layout[2][3] = Cell(CellType::Fruit);
    // layout[3][5] = Cell(CellType::Key);
}

// Loads maze layout from a file
void Maze::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open maze file: " << filename << std::endl;
        return;
    }

    file >> width >> height;
    layout = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell(CellType::Empty)));

    char cellChar;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file >> cellChar;
            switch (cellChar) {
                case '#': layout[y][x] = Cell(CellType::Wall); break;
                case '.': layout[y][x] = Cell(CellType::Fruit); break;
                case 'K': layout[y][x] = Cell(CellType::Key); break;
                default: layout[y][x] = Cell(CellType::Empty); break;
            }
        }
    }
}

// Draws the maze on the screen
void Maze::draw() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (layout[y][x].type) {
                case CellType::Wall:
                    DrawRectangle(x * 32, y * 32, 32, 32, DARKGRAY);
                    break;
                case CellType::Fruit:
                    DrawCircle(x * 32 + 16, y * 32 + 16, 8, ORANGE);
                    break;
                case CellType::Key:
                    DrawCircle(x * 32 + 16, y * 32 + 16, 8, YELLOW);
                    break;
                default:
                    break;
            }
        }
    }
}

// Checks if the given position is a wall
bool Maze::isWall(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return true;
    return layout[y][x].type == CellType::Wall;  // Check if the tile is a wall
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

// Returns starting X position for Ghost
int Maze::getGhostStartX() const {
    return ghostStartX;
}

// Returns starting Y position for Ghost
int Maze::getGhostStartY() const {
    return ghostStartY;
}
