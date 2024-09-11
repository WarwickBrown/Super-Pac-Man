#include "Maze.h"
#include <raylib-cpp.hpp>
#include <iostream>

// Constructor
Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    initializeCustomWalls();  // Initialize a simple default maze for testing
}

// Destructor
Maze::~Maze() {
    // Nothing to clean up for now as vector manages its own memory
}

// Initializes custom wall layout by manually adding rectangles
void Maze::initializeCustomWalls() {
    // Add custom rectangles to the walls vector
    walls.push_back(Rectangle{0, 0, 10, 900});     // Left wall
    walls.push_back(Rectangle{0, 0, 1600, 10});    // Top wall
    walls.push_back(Rectangle{1590, 0, 10, 900});  // Right wall
    walls.push_back(Rectangle{0, 890, 1600, 10});  // Bottom wall

    // You can add more custom rectangles here as needed for the maze layout
}

// // Initializes a default maze layout for testing
// void Maze::initializeDefaultMaze() {
//     // Simple 10x10 maze layout for testing purposes
//     width = 10;
//     height = 10;
//     layout = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell(CellType::Empty)));

//     // Clear the walls vector to make sure it's empty before repopulating
//     walls.clear();

//     // Set maze walls and add them to the walls vector
//     for (int i = 0; i < width; i++) {
//         layout[0][i] = Cell(CellType::Wall);
//         layout[height - 1][i] = Cell(CellType::Wall);

//         // Add top and bottom walls to the vector
//         walls.push_back(Rectangle{i * 50.0f, 0.0f, 50.0f, 50.0f});                  // Top wall
//         walls.push_back(Rectangle{i * 50.0f, (height - 1) * 50.0f, 50.0f, 50.0f});  // Bottom wall
//     }

//     for (int i = 0; i < height; i++) {
//         layout[i][0] = Cell(CellType::Wall);
//         layout[i][width - 1] = Cell(CellType::Wall);

//         // Add left and right walls to the vector
//         walls.push_back(Rectangle{0.0f, i * 50.0f, 50.0f, 50.0f});                  // Left wall
//         walls.push_back(Rectangle{(width - 1) * 50.0f, i * 50.0f, 50.0f, 50.0f});  // Right wall
//     }

//     // Make sure the start position at (1, 1) is not a wall
//     layout[1][1] = Cell(CellType::Empty);  // Set the start position for Pac-Man to empty space
// }

// Draws the custom walls on the screen
void Maze::draw() const {
    for (const auto& wall : walls) {
        DrawRectangleRec(wall, raylib::Color::DarkBlue());
    }
}

// Checks if Pac-Man is colliding with any wall in the custom walls
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions
    for (const auto& wall : walls) {
        if (CheckCollisionCircleRec({ static_cast<float>((pacmanX * 32)), static_cast<float>((pacmanY * 32)) }, pacmanRadius, wall)) {
            std::cout << "Collision" << std::endl;
            std::cout << "Ball Position: (" << pacmanX*32 << ", " << pacmanY*32 << ")\n";
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

