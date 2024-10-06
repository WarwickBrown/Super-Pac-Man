/**
 * @file SuperPellet.cpp
 * @brief Implements the SuperPellet class, a special type of collectible in the game.
 * 
 * This file defines the methods for the SuperPellet class, including the constructor,
 * destructor, and collision detection functionality with Pac-Man.
 */

#include "SuperPellet.h"

/**
 * @brief Constructs a SuperPellet object with a specified position.
 * 
 * Initializes the SuperPellet object using the base class Collectable's constructor,
 * setting its position and radius. The super pellet is initially active.
 * 
 * @param x The x-coordinate of the super pellet's position.
 * @param y The y-coordinate of the super pellet's position.
 */
SuperPellet::SuperPellet(float x, float y)
    : Collectable(x, y, 15.0f) {  ///< Initialize using the Collectable base class with position and radius.
}

/**
 * @brief Destructor for the SuperPellet class.
 * 
 * Cleans up resources if necessary. Since no dynamic memory allocation is used,
 * this destructor does not perform any specific actions but is defined for completeness.
 */
SuperPellet::~SuperPellet() {
    // No specific actions required for the destructor.
}

/**
 * @brief Checks if Pac-Man collides with the super pellet.
 * 
 * This method checks if the bounding circle of Pac-Man intersects with the bounding
 * circle of the super pellet. If a collision is detected and the super pellet is active,
 * it returns true; otherwise, it returns false.
 * 
 * @param pacManX The x-coordinate of Pac-Man's position.
 * @param pacManY The y-coordinate of Pac-Man's position.
 * @param pacManRadius The radius of Pac-Man (for collision detection).
 * @return true if Pac-Man collides with the super pellet and it is active, false otherwise.
 */
bool SuperPellet::checkCollision(float pacManX, float pacManY, float pacManRadius) const {
    return active && CheckCollisionCircles({ pacManX, pacManY }, pacManRadius, { getX(), getY() }, getRadius());
}
