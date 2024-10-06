/**
 * @file PowerPellet.cpp
 * @brief Implements the PowerPellet class, which represents a power-up that Pac-Man can collect.
 * 
 * This file defines the methods for initializing the PowerPellet object and handling collisions
 * with Pac-Man.
 */

#include "PowerPellet.h"

/**
 * @brief Constructs a PowerPellet object with a specified position.
 * 
 * This constructor initializes the PowerPellet using the Collectable class's constructor
 * and sets its position and radius.
 * 
 * @param x The x-coordinate of the power pellet.
 * @param y The y-coordinate of the power pellet.
 */
PowerPellet::PowerPellet(float x, float y)
    : Collectable(x, y, 10.0f) {
}

/**
 * @brief Destructor for the PowerPellet class.
 * 
 * This destructor does not perform any specific actions but is defined for completeness.
 */
PowerPellet::~PowerPellet() {
}

/**
 * @brief Checks if Pac-Man collides with the power pellet.
 * 
 * This method checks if Pac-Man collides with the power pellet using circle collision detection.
 * If a collision is detected, the pellet is marked as collected, and the method returns true.
 * Otherwise, it returns false.
 * 
 * @param pacman The Pac-Man object to check for collisions.
 * @return true if Pac-Man collides with the pellet, false otherwise.
 */
bool PowerPellet::checkCollisionWithPacMan(const PacMan& pacman) {
    if (active && CheckCollisionCircles(
            { pacman.getX(), pacman.getY() }, pacman.getRadius(),
            { getX(), getY() }, getRadius())) {
        collect();  ///< Mark the pellet as collected if a collision occurs.
        return true;
    }
    return false;
}
