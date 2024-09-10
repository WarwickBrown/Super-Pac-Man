#include "Ghost.h"
#include <cstdlib>  // For random number generation
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

// Constructor
Ghost::Ghost(int startX, int startY)
    : x(startX), y(startY), dx(1), dy(0), size(16), state(GhostState::Normal), frightenedDuration(0.0f) {}

// Destructor
Ghost::~Ghost() {
    // No dynamic memory to clean up in this class
}

// Moves the ghost based on AI logic
void Ghost::move(const Maze& maze, const PacMan& pacMan) {

    if (state == GhostState::Frightened) {
        frightenedDuration -= GetFrameTime();
        if (frightenedDuration <= 0) {
            resetState();
        }
    }

    if (isWallAhead(maze)) {
        changeDirection(maze);  // Change direction if there's a wall
    }

    // Simple chasing logic: move towards Pac-Man if not frightened
    if (state == GhostState::Normal) {
        chasePacMan(pacMan);
    }

    if (isWallAhead(maze)) {
        changeDirection(maze);  // Change direction if there's a wall ahead
    }

    int newX = x + dx;  // Move by tile, not pixel
    int newY = y + dy;

    if (!maze.isWall(newX, newY)) {
        x = newX;
        y = newY;
    }

    std::cout << "Ghost moved to tile (" << x << ", " << y << ")" << std::endl;
}



// Draws the ghost on the screen
void Ghost::draw() const {
    if (state == GhostState::Frightened) {
        DrawRectangle(x, y, size, size, BLUE);  // Draw frightened ghost in blue
    } else {
        int pixelX = x * 32;
        int pixelY = y * 32;
        DrawRectangle(pixelX, pixelY, 32, 32, RED);  // Draw ghost in the tile
    }
}

// Checks for collisions with Pac-Man
bool Ghost::checkCollision(const PacMan& pacMan) const {
    int pacManX = pacMan.getX();
    int pacManY = pacMan.getY();
    int pacManSize = 32;  // Assuming Pac-Man's size is 32x32 for simplicity

    if (x < pacManX + pacManSize && x + size > pacManX &&
        y < pacManY + pacManSize && y + size > pacManY) {
        return true;  // Collision detected
    }

    return false;
}

// Changes ghost state to frightened
void Ghost::becomeFrightened() {
    state = GhostState::Frightened;
    frightenedDuration = 5.0f;  // Frightened state lasts for 5 seconds
}

// Resets ghost state to normal
void Ghost::resetState() {
    state = GhostState::Normal;
}

// Returns whether the ghost is in frightened mode
bool Ghost::isFrightened() const {
    return state == GhostState::Frightened;
}

// Returns the ghost's current X position
int Ghost::getX() const {
    return x;
}

// Returns the ghost's current Y position
int Ghost::getY() const {
    return y;
}

// Returns the size of the ghost for collision detection
int Ghost::getSize() const {
    return size;
}

// Changes the direction of the ghost randomly or based on AI
void Ghost::changeDirection(const Maze& maze) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int newDirectionIndex = rand() % 4;
    dx = directions[newDirectionIndex][0];
    dy = directions[newDirectionIndex][1];

    // Ensure the new direction is not leading into a wall
    while (isWallAhead(maze)) {
        newDirectionIndex = rand() % 4;
        dx = directions[newDirectionIndex][0];
        dy = directions[newDirectionIndex][1];
    }
}

// Logic to chase Pac-Man
void Ghost::chasePacMan(const PacMan& pacMan) {
    int pacManX = pacMan.getX();
    int pacManY = pacMan.getY();

    // Simple chasing logic: move towards Pac-Man's position
    if (x < pacManX) dx = 1;
    else if (x > pacManX) dx = -1;

    if (y < pacManY) dy = 1;
    else if (y > pacManY) dy = -1;
}

// Checks if there's a wall in the ghost's next position
bool Ghost::isWallAhead(const Maze& maze) const {
    int nextX = x + dx;
    int nextY = y + dy;
    return maze.isWall(nextX / 32, nextY / 32);
}
