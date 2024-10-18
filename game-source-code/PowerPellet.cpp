/**
 * @file PowerPellet.cpp
 * @brief Implements the PowerPellet class, which represents a power-up that Pac-Man can collect.
 * 
 * This file defines the methods for initialising the PowerPellet object and handling collisions
 * with Pac-Man.
 */

#include "PowerPellet.h"

PowerPellet::PowerPellet(float x, float y)
    : Collectable(x, y, 10.0f) {
}

PowerPellet::~PowerPellet() {
}

// Check if Pac-Man collides with the power pellet
bool PowerPellet::checkCollisionWithPacMan(const PacMan& pacman) {
    if (active && CheckCollisionCircles(
            { pacman.getX(), pacman.getY() }, pacman.getRadius(),
            { getX(), getY() }, getRadius())) {
        collect();  ///< Mark the pellet as collected if a collision occurs.
        return true;
    }
    return false;
}