#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>


using namespace std;

// Constructor: Initialises Pac-Man's starting position (x, y), movement direction (dx, dy), speed, and size (radius).
PacMan::PacMan(int startX, int startY) : x(765), y(525), dx(0), dy(0), normalSpeed(250), radius(34), superSpeed(400), superModeActive(false), superModeDuration(10), superModeTimer(0), invincible(false), invincibilityTime(0.0f), invincibilityDuration(2.0f) {}

// Destructor: Since there is no dynamic memory allocation, the destructor does not need to clean up any resources.
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Sets the movement direction of Pac-Man based on the given direction integer.
// This updates dx and dy, which represent movement in the x and y directions.
void PacMan::setDirection(Direction direction) {
    switch (direction) {
        case RIGHT: 
            dx = 1; dy = 0;
            break;
        case LEFT: 
            dx = -1; dy = 0;
            break;
        case UP: 
            dx = 0; dy = -1;
            break;
        case DOWN: 
            dx = 0; dy = 1;
            break;
        default: 
            dx = 0; dy = 0;
    }
}


// Manages Pac-Man's animation frame timing and returns the appropriate frame index for rendering.
// This method controls how quickly Pac-Man's sprite animation changes as he moves.
int PacMan::location(int frame) const {
    // Timer to control the speed of the frame change.
    static auto timer = 0.0f;
    timer += GetFrameTime();  // Add time since the last frame.

    // If the timer exceeds 0.2 seconds, advance to the next frame.
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;  // Cycle through 6 frames (0 to 5).
    }

    // Return the updated frame number.
    return frame;
}

// Moves Pac-Man based on the direction and checks for wall collisions.
// If Pac-Man does not collide with a wall, his position is updated.
void PacMan::move(const Maze& maze, float deltaTime, Direction direction) {
    auto speed = superModeActive ? superSpeed : normalSpeed;
   // Set the movement direction (based on input direction).
    setDirection(direction);

    // Calculate the new position.
    auto newX = x + dx;
    auto newY = y + dy;

    // Check if the new position is not colliding with a wall.
    if (!maze.isWall(newX, newY, radius)) {
        // If no collision, update Pac-Man's position.
        x += dx * speed * deltaTime;
        y += dy * speed * deltaTime;
    }
}

void PacMan::setInvincible(bool invincible) {
    this->invincible = invincible;
    setPosition(765, 525);
    if (invincible) {
        invincibilityTime = 0.0f;
    }
}

void PacMan::updateInvincibility(float deltaTime) {
    if (invincible) {
        invincibilityTime += deltaTime;
        if (invincibilityTime >= invincibilityDuration) {
            invincible = false;
            invincibilityTime = 0.0f;
        }
    }
}

void PacMan::activateSuperMode() {
    superModeActive = true;
    superModeTimer = 4.0f;
    visualRadius = radius * 1.5f;
}

void PacMan::deactivateSuperMode() {
    superModeActive = false;
    visualRadius = radius;
}

void PacMan::updateSuperMode(float deltaTime) {
    if (superModeActive) {
        superModeTimer -= deltaTime;    // Decrease timer based on elapsed time
        if (superModeTimer <= 0.0f) {
            deactivateSuperMode();      // Deactivate super mode when timer ends
        }
    }
}

void PacMan::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}