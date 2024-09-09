#include "PacMan.h"
#include "Ghost.h"
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

    int newX = x + dx;
    int newY = y + dy;

    if (!maze.isWall(newX / 32, newY / 32)) {
        x = newX;
        y = newY;
    } else {
        std::cout << "PacMan hit a wall at (" << newX / 32 << ", " << newY / 32 << ")" << std::endl;
    }

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
        DrawCircle(x, y, radius, YELLOW);  // Draw normal Pac-Man in yellow
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

// Checks for collisions with ghosts
bool PacMan::checkCollision(const Ghost& ghost) const {
    // Simple bounding box collision detection for now
    int ghostX = ghost.getX();
    int ghostY = ghost.getY();
    int ghostSize = ghost.getSize();  // Assume ghosts are drawn as squares for simplicity

    if (x < ghostX + ghostSize && x + radius * 2 > ghostX &&
        y < ghostY + ghostSize && y + radius * 2 > ghostY) {
        return true;  // Collision detected
    }

    return false;
}

// Changes Pac-Man's state to "Super"
void PacMan::becomeSuper() {
    superState = true;
    superDuration = 10.0f;  // Super state lasts for 10 seconds
}

// Resets Pac-Man's state from "Super"
void PacMan::resetSuper() {
    superState = false;
}

// Returns whether Pac-Man is in "Super" mode
bool PacMan::isSuper() const {
    return superState;
}

// Handles collisions with the maze
void PacMan::handleMazeCollision(const Maze& maze) {
    // Check if next position is a wall
    if (maze.isWall(x / 32 + dx, y / 32 + dy)) {
        dx = 0;
        dy = 0;  // Stop Pac-Man's movement
    }
}
