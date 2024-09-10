#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

// Constructor
PacMan::PacMan(int startX, int startY) 
    : x(startX), y(startY), dx(0), dy(0), speed(50) {}

// Destructor
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on direction and checks for collisions
// This needs to be over-halled
void PacMan::move(const Maze& maze, float deltaTime, int dir) {
    setDirection(dir);
    float newX = x + dx;
    float newY = y + dy;

    //int gridX = static_cast<int>(newX) / 16;
    //int gridY = static_cast<int>(newY) / 16;

    std::cout << "New Position: (" << newX << ", " << newY << ")\n";  // Debug output
    //std::cout << "Grid Position: (" << gridX << ", " << gridY << ")\n";  // Debug output

    if (!maze.isWall(newX, newY)) {
        x += dx*0.01;
        y += dy*0.01;
    }
}

// Draws Pac-Man on the screen
void PacMan::draw() const {
    double pixelX = x * 32;  // Convert tile coordinates to pixel coordinates
    double pixelY = y * 32;
    DrawCircle(pixelX + 16, pixelY + 16, 16, YELLOW);  // Draw Pac-Man centered in the tile    
}

// Sets the movement direction of Pac-Man
void PacMan::setDirection(int dir) {
    if(dir == 0){
        dx = 0;
        dy = 0;
    }
    else if(dir == 1){
        dx = 1;
        dy = 0;
    }
    else if(dir == 2){
        dx = -1;
        dy = 0;
    }
    else if(dir == 3){
        dx = 0;
        dy = -1;
    }
    else if(dir == 4){
        dx = 0;
        dy = 1;
    }
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

