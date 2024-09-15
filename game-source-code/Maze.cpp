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
    walls.push_back(Rectangle{0, 0, 10, 880});     // Left wall
    walls.push_back(Rectangle{0, 0, 1520, 10});    // Top wall
    walls.push_back(Rectangle{1520, 0, 10, 880});  // Right wall
    walls.push_back(Rectangle{0, 880, 1520, 10});  // Bottom wall

    // // Horizontal walls (top section)
    


    // // Vertical walls (sides)
    // walls.push_back(Rectangle{80, 80, 10, 240});   // Vertical wall
    // walls.push_back(Rectangle{400, 80, 10, 240});  // Vertical wall
    // walls.push_back(Rectangle{1240, 80, 10, 240}); // Vertical wall

    // // Central box (approximate the inner box)
    // walls.push_back(Rectangle{640, 320, 160, 10}); // Top horizontal wall of central box
    // walls.push_back(Rectangle{640, 560, 160, 10}); // Bottom horizontal wall of central box
    // walls.push_back(Rectangle{640, 320, 10, 240}); // Left vertical wall of central box
    // walls.push_back(Rectangle{870, 320, 10, 240}); // Right vertical wall of central box

    // // Bottom horizontal walls (mirroring top layout)
    walls.push_back(Rectangle{80, 800, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{80, 80, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{10, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{240, 800, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{80, 640, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{80, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{160, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{240, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{240, 480, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{160, 160, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{160, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{320, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{320, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{320, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{480, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{400, 640, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{480, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{560, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{400, 480, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{480, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{400, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{320, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{640, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{800, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{640, 800, 240, 10});   // Horizontal wall
    walls.push_back(Rectangle{640, 480, 240, 10});   // Horizontal wall
    walls.push_back(Rectangle{640, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{800, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{640, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{800, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{880, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{960, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1040, 640, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1360, 80, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1120, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1200, 800, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1200, 480, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1440, 720, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1360, 800, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1360, 640, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{960, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1040, 480, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1040, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1120, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1120, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1200, 480, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1280, 560, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1280, 400, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1200, 320, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1120, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1360, 240, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1280, 160, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{1360, 80, 80, 10});   // Horizontal wall
    walls.push_back(Rectangle{960, 240, 80, 10});   // Horizontal wall

    // // More vertical walls for more complexity
    // walls.push_back(Rectangle{240, 320, 10, 160});   // Vertical wall
    walls.push_back(Rectangle{160, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{240, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{80, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{80, 320, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{80, 80, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{160, 240, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{240, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{240, 80, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{320, 80, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{400, 80, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{480, 0, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{400, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{640, 0, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{560, 80, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{320, 480, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{560, 800, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{480, 640, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{560, 80, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{480, 400, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{560, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{400, 320, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{960, 800, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{560, 400, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{640, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{880, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{640, 400, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{880, 400, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{720, 240, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{800, 240, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{960, 400, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{960, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1120, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1040, 640, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1440, 80, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1040, 0, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{960, 80, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{880, 0, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1280, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1360, 720, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1280, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1040, 400, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1120, 320, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1200, 480, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1440, 560, 10, 80});  // Vertical wall
    walls.push_back(Rectangle{1440, 320, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1360, 240, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{1280, 80, 10, 250});  // Vertical wall
    walls.push_back(Rectangle{1200, 80, 10, 170});  // Vertical wall
    walls.push_back(Rectangle{1120, 80, 10, 80});  // Vertical wall

    walls.push_back(Rectangle{720, 640, 80, 80});   // Block
    walls.push_back(Rectangle{720, 80, 80, 80});   // Block
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

bool Maze::isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions. 
    for (const auto& wall : walls) {
        
        // CheckCollisionCircleRec checks for collision between a circle (Pac-Man) and a rectangle (wall).
        if (CheckCollisionRecs(Rectangle{(float)pacmanX-35, (float)pacmanY-35, 70, 70}, wall)) {
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

