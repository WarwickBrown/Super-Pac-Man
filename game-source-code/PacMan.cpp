#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

// Constructor
PacMan::PacMan(int startX, int startY) 
    : x(startX), y(startY), dx(0), dy(0), radius(16) {}

// Destructor
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on direction and checks for collisions
// This needs to be over-halled
void PacMan::move(const Maze& maze) {

    std::cout << "PacMan before move - X: " << x << " Y: " << y << std::endl;
    std::cout << "PacMan dx: " << dx << " dy: " << dy << std::endl;

    int newX = x + dx;  // Move Pac-Man by 1 tile (dx or dy will be 1, 0, or -1)
    int newY = y + dy;

    if (!maze.isWall(newX, newY)) {
        x = newX;  // Update tile position
        y = newY;
        std::cout << "PacMan moved to tile (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cout << "PacMan hit a wall at (" << newX << ", " << newY << ")" << std::endl;
    }

    // After moving, reset the direction so Pac-Man doesn't keep moving
    dx = 0;
    dy = 0;

    cout << "PacMan after move - X: " << x << " Y: " << y << endl;
}

// Draws Pac-Man on the screen
void PacMan::draw() const {
    int pixelX = x * 32;  // Convert tile coordinates to pixel coordinates
    int pixelY = y * 32;
    DrawCircle(pixelX + 16, pixelY + 16, 16, YELLOW);  // Draw Pac-Man centered in the tile    
}

// Sets the movement direction of Pac-Man
void PacMan::setDirection(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
}

// Checks for collisions with the maze
bool PacMan::checkCollision(const Maze& maze) const {
    return maze.isWall(x / 32, y / 32);
}

// Handles collisions with the maze
void PacMan::handleMazeCollision(const Maze& maze) {
    // Check if next position is a wall
    if (maze.isWall(x / 32 + dx, y / 32 + dy)) {
        dx = 0;
        dy = 0;  // Stop Pac-Man's movement
    }
}
