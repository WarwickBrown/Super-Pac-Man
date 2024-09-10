#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

// Constructor
PacMan::PacMan(int startX, int startY) 
    : x(startX), y(startY), dx(0), dy(0), radius(16), superState(false), superDuration(0.0f) {}

// Destructor
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on direction and checks for collisions
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

    // Handle Super state or any other game logic here...


    // Handle special cases (like eating fruits or keys) here if needed

    // Reduce the duration of Super state
    if (superState) {
        superDuration -= GetFrameTime();  // Reduce time by the frame duration
        if (superDuration <= 0) {
            resetSuper();
        }
    }

    cout << "PacMan after move - X: " << x << " Y: " << y << endl;
}

// Draws Pac-Man on the screen
void PacMan::draw() const {
    if (superState) {
        DrawCircle(x, y, radius, BLUE);  // Draw "Super" Pac-Man in blue
    } else {
        int pixelX = x * 32;  // Convert tile coordinates to pixel coordinates
        int pixelY = y * 32;
        DrawCircle(pixelX + 16, pixelY + 16, 16, YELLOW);  // Draw Pac-Man centered in the tile    
    }
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

// bool PacMan::checkCollision(const Ghost& ghost) const {
//     // Assuming Pac-Man and Ghost are both aligned to 32x32 tiles
//     int pacManTileX = x / 32;
//     int pacManTileY = y / 32;
//     // int ghostTileX = ghost.getX() / 32;
//     // int ghostTileY = ghost.getY() / 32;

//     std::cout << "PacMan Tile: (" << pacManTileX << ", " << pacManTileY << ")"
//               << " Ghost Tile: (" << ghostTileX << ", " << ghostTileY << ")" << std::endl;

//     return (pacManTileX == ghostTileX && pacManTileY == ghostTileY);
// }


// Changes Pac-Man's state to "Super"
// void PacMan::becomeSuper() {
//     superState = true;
//     superDuration = 10.0f;  // Super state lasts for 10 seconds
// }

// Resets Pac-Man's state from "Super"
// void PacMan::resetSuper() {
//     superState = false;
// }

// Returns whether Pac-Man is in "Super" mode
// bool PacMan::isSuper() const {
//     return superState;
// }

// Handles collisions with the maze
void PacMan::handleMazeCollision(const Maze& maze) {
    // Check if next position is a wall
    if (maze.isWall(x / 32 + dx, y / 32 + dy)) {
        dx = 0;
        dy = 0;  // Stop Pac-Man's movement
    }
}
