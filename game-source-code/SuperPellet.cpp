/**
 * @file SuperPellet.cpp
 * @brief Implements the SuperPellet class, a special type of collectible in the game.
 * 
 * This file defines the methods for the SuperPellet class, including the constructor,
 * destructor, and collision detection functionality with Pac-Man.
 */

#include "SuperPellet.h"

SuperPellet::SuperPellet(float x, float y)
    : Collectable(x, y, 15.0f) {  ///< initialise using the Collectable base class with position and radius.
}

SuperPellet::~SuperPellet() {
    // No specific actions required for the destructor.
}

bool SuperPellet::checkCollision(float pacManX, float pacManY, float pacManRadius) const {
    return active && CheckCollisionCircles({ pacManX, pacManY }, pacManRadius, { getX(), getY() }, getRadius());
}