/**
 * @file PacMan.cpp
 * @brief Implements the PacMan class, which represents the player character and its behavior.
 * 
 * The PacMan class manages Pac-Man's movement, state changes, and interactions within the game,
 * such as collision detection with the maze walls and activation of special modes.
 */

#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>


using namespace std;

PacMan::PacMan(int startX, int startY) 
    : x(765), y(525), dx(0), dy(0), normalSpeed(250), radius(34), superSpeed(400),
      superModeActive(false), superModeDuration(10), superModeTimer(0), invincible(false),
      invincibilityTime(0.0f), invincibilityDuration(2.0f) {}

PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

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
            dx = 0; dy = 0;  // No movement
    }
}

int PacMan::location(int frame) const {
    static auto timer = 0.0f;  ///< Timer to control the speed of the frame change.
    timer += GetFrameTime();   ///< Add time since the last frame.

    // If the timer exceeds 0.2 seconds, advance to the next frame.
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;  ///< Cycle through 6 frames (0 to 5).
    }

    return frame;  ///< Return the updated frame number.
}

void PacMan::move(const Maze& maze, float deltaTime, Direction direction) {
    auto speed = superModeActive ? superSpeed : normalSpeed;  ///< Use super speed if in super mode.

    setDirection(direction);  ///< Set the movement direction based on input direction.

    // Calculate the new position.
    auto newX = x + dx;
    auto newY = y + dy;

    // Check if the new position is not colliding with a wall.
    if ((dx != 0 || dy != 0) && !maze.isWall(newX, newY, radius)) {
        x += dx * speed * deltaTime;  ///< Update x position if no collision.
        y += dy * speed * deltaTime;  ///< Update y position if no collision.
    }
}

void PacMan::setInvincible(bool invincible) {
    this->invincible = invincible;
    setPosition(765, 525);  ///< Reset Pac-Man's position.
    if (invincible) {
        invincibilityTime = 0.0f;  ///< Reset the invincibility timer.
    }
}

void PacMan::updateInvincibility(float deltaTime) {
    if (invincible) {
        invincibilityTime += deltaTime;  ///< Increment the invincibility timer.
        if (invincibilityTime >= invincibilityDuration) {
            invincible = false;          ///< Deactivate invincibility.
            invincibilityTime = 0.0f;
        }
    }
}

void PacMan::activateSuperMode() {
    superModeActive = true;
    superModeTimer = 4.0f;      ///< Set the super mode timer duration.
    visualRadius = radius * 1.5f;  ///< Increase visual radius.
}

void PacMan::deactivateSuperMode() {
    superModeActive = false;
    visualRadius = radius;  ///< Reset visual radius to normal.
}

void PacMan::updateSuperMode(float deltaTime) {
    if (superModeActive) {
        superModeTimer -= deltaTime;  ///< Decrease timer based on elapsed time.
        if (superModeTimer <= 0.0f) {
            deactivateSuperMode();  ///< Deactivate super mode when timer ends.
        }
    }
}

void PacMan::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}