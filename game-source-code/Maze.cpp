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
    walls.push_back(Rectangle{0, 0, 10, 1000});     // Left wall
    walls.push_back(Rectangle{0, 0, 1720, 10});    // Top wall
    walls.push_back(Rectangle{1710, 0, 10, 1000});  // Right wall
    walls.push_back(Rectangle{0, 990, 1720, 10});  // Bottom wall

    // // Horizontal walls (top section)
    


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
    walls.push_back(Rectangle{90, 900, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{90, 90, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{10, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{270, 900, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{90, 720, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{90, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{180, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{270, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{270, 540, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{180, 180, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{180, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{360, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{360, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{360, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{540, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{450, 720, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{540, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{630, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{450, 540, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{540, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{450, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{360, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{720, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{900, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{720, 900, 270, 10});   // Horizontal wall
    walls.push_back(Rectangle{720, 540, 270, 10});   // Horizontal wall
    walls.push_back(Rectangle{720, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{900, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{720, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{900, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{990, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1080, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1170, 720, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1530, 90, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1260, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1350, 900, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1350, 540, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1620, 810, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1530, 900, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1530, 720, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1080, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1170, 540, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1170, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1260, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1260, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1350, 540, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1440, 630, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1440, 450, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1350, 360, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1260, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1530, 270, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1440, 180, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1530, 90, 90, 10});   // Horizontal wall
    walls.push_back(Rectangle{1080, 270, 90, 10});   // Horizontal wall

    // // More vertical walls for more complexity
    // walls.push_back(Rectangle{240, 320, 10, 160});   // Vertical wall
    walls.push_back(Rectangle{180, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{270, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{90, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{90, 360, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{90, 90, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{180, 270, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{270, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{270, 90, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{360, 90, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{450, 90, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{540, 0, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{450, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{720, 0, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{630, 90, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{360, 540, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{630, 900, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{540, 720, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{630, 90, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{540, 450, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{630, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{450, 360, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1080, 900, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{630, 450, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{720, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{990, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{720, 450, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{990, 450, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{810, 270, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{900, 270, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1080, 450, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1080, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1260, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1170, 720, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1620, 90, 10, 90});  // Vertical wall
    walls.push_back(Rectangle{1170, 0, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1080, 90, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{990, 0, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1440, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1530, 810, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1440, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1170, 450, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1260, 360, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1350, 540, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1620, 630, 10, 100});  // Vertical wall
    walls.push_back(Rectangle{1620, 360, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1530, 270, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{1440, 90, 10, 280});  // Vertical wall
    walls.push_back(Rectangle{1350, 90, 10, 190});  // Vertical wall
    walls.push_back(Rectangle{1260, 90, 10, 100});  // Vertical wall

    walls.push_back(Rectangle{810, 720, 100, 100});   // Block
    walls.push_back(Rectangle{810, 90, 100, 100});   // Block
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

