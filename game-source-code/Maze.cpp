#include "Maze.h"
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

// Constructor
Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    initialiseCustomWalls();  // Initialize a simple default maze for testing
}

// Destructor
Maze::~Maze() {
    // Nothing to clean up for now as vector manages its own memory
}

// Initializes a default maze layout for testing
// void Maze::initializeDefaultMaze() {
//     // Simple 10x10 maze layout for testing purposes
//     width = 10;
//     height = 10;
//     layout = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell(CellType::Empty)));

//     // Set maze walls
//     for (int i = 0; i < width; i++) {
//         layout[0][i] = Cell(CellType::Wall);
//         layout[height - 1][i] = Cell(CellType::Wall);
//     }
//     for (int i = 0; i < height; i++) {
//         layout[i][0] = Cell(CellType::Wall);
//         layout[i][width - 1] = Cell(CellType::Wall);
//     }

//     // Make sure the start position at (1, 1) is not a wall
//     layout[1][1] = Cell(CellType::Empty);  // Set the start position for Pac-Man to empty space
// }

void Maze::initialiseCustomWalls() {
    // Add custom rectangles to the walls vector
    walls.push_back(Rectangle{0, 0, 10, 900});     // Left wall
    walls.push_back(Rectangle{0, 0, 1600, 10});    // Top wall
    walls.push_back(Rectangle{1590, 0, 10, 900});  // Right wall
    walls.push_back(Rectangle{0, 890, 1600, 10});  // Bottom wall
    walls.push_back(Rectangle{500,100,1000,10});
}

// Draws the maze on the screen
// We might need to make vertical and horizontal walls for pixel system
// Maybe two types of wall, wall vert and wall hori
// void Maze::draw() const {
//     for (const auto& wall : walls) {
//         DrawRectangleRec(wall, raylib::Color::DarkBlue());
//     }
// }



// Checks if Pac-Man is colliding with any wall in the custom walls
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions
    for (const auto& wall : walls) {
        if (CheckCollisionCircleRec({ static_cast<float>((pacmanX)), static_cast<float>((pacmanY)) }, pacmanRadius, wall)) {
            std::cout << "Collision" << std::endl;
            std::cout << "Ball Position: (" << (pacmanX) << ", " << (pacmanY) << ")\n";
            std::cout << "Object Position: (" << wall.x << ", " << wall.y << ", width: " << wall.width << ", height: " << wall.height << ")\n";

            return true;  // Collision detected
        }
    }
    return false;  // No collision detected
}

// Checks if Pac-Man is colliding with a given rectangle
bool Maze::isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const {
    return CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, rect);
}
// Getter to access the walls vector (if needed elsewhere)
const std::vector<Rectangle>& Maze::getWalls() const {
    return walls;
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

