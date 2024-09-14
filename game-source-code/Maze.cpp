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
    // Outer walls
    walls.push_back(Rectangle{0, 0, 10, 900});     // Left wall
    walls.push_back(Rectangle{0, 0, 1600, 10});    // Top wall
    walls.push_back(Rectangle{1590, 0, 10, 900});  // Right wall
    walls.push_back(Rectangle{0, 890, 1600, 10});  // Bottom wall

    // // Horizontal walls (top section)
    // walls.push_back(Rectangle{90, 90, 160, 10});   // Horizontal wall
    // walls.push_back(Rectangle{400, 90, 240, 10});  // Horizontal wall
    // walls.push_back(Rectangle{880, 90, 240, 10});  // Horizontal wall
    // walls.push_back(Rectangle{1240, 90, 160, 10}); // Horizontal wall

    // // Vertical walls (sides)
    // walls.push_back(Rectangle{90, 90, 10, 240});   // Vertical wall
    // walls.push_back(Rectangle{400, 90, 10, 240});  // Vertical wall
    // walls.push_back(Rectangle{1240, 90, 10, 240}); // Vertical wall

    // // Central box (approximate the inner box)
    // walls.push_back(Rectangle{720, 320, 160, 10}); // Top horizontal wall of central box
    // walls.push_back(Rectangle{720, 560, 160, 10}); // Bottom horizontal wall of central box
    // walls.push_back(Rectangle{720, 320, 10, 240}); // Left vertical wall of central box
    // walls.push_back(Rectangle{870, 320, 10, 240}); // Right vertical wall of central box

    // // Bottom horizontal walls (mirroring top layout)
    // walls.push_back(Rectangle{90, 720, 160, 10});   // Horizontal wall
    // walls.push_back(Rectangle{400, 720, 240, 10});  // Horizontal wall
    // walls.push_back(Rectangle{880, 720, 240, 10});  // Horizontal wall
    // walls.push_back(Rectangle{1240, 720, 160, 10}); // Horizontal wall

    // // More vertical walls for more complexity
    // walls.push_back(Rectangle{240, 320, 10, 160});   // Vertical wall
    // walls.push_back(Rectangle{1240, 320, 10, 160});  // Vertical wall

    // Continue mapping the rest of the maze
};


// Draws the maze on the screen
// We might need to make vertical and horizontal walls for pixel system
// Maybe two types of wall, wall vert and wall hori
// void Maze::draw() const {
//     for (const auto& wall : walls) {
//         DrawRectangleRec(wall, raylib::Color::DarkBlue());
//     }
// }



// Checks if Pac-Man is colliding with any wall in the custom walls.
// Takes in Pac-Man's X, Y coordinates and his radius, and checks for collision with each wall.
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions.
    for (const auto& wall : walls) {
        // CheckCollisionCircleRec checks for collision between a circle (Pac-Man) and a rectangle (wall).
        if (CheckCollisionCircleRec({ static_cast<float>((pacmanX)), static_cast<float>((pacmanY)) }, pacmanRadius, wall)) {
            return true;  // Collision detected, return true.
        }
    }
    return false;  // No collision detected, return false.
}

// Checks if Pac-Man is colliding with a given rectangle (specified by the rectangle's coordinates).
// Takes in Pac-Man's X, Y coordinates and radius, as well as the rectangle to check against.
bool Maze::isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const {
    // Use Raylib's CheckCollisionCircleRec to detect a collision between Pac-Man and the rectangle.
    return CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, rect);
}

// Getter to access the walls vector.
// This allows other objects or functions to access the vector of walls in the maze.
const std::vector<Rectangle>& Maze::getWalls() const {
    return walls;
}


// Getter function that returns the maze height.
// Like the width, the height is not currently set explicitly but could be used for future features.
int Maze::getHeight() const {
    return height;
}

// Getter function to return the starting X position of Pac-Man in the maze.
// This is initialized as `startX = 10` in the constructor.
int Maze::getStartX() const {
    return startX;
}

// Getter function to return the starting Y position of Pac-Man in the maze.
// This is initialized as `startY = 10` in the constructor.
int Maze::getStartY() const {
    return startY;
}

