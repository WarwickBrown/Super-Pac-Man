#include "SuperPellet.h"

// Constructor that initializes using the Collectable base class
SuperPellet::SuperPellet(float x, float y)
    : Collectable(x, y, 15.0f) { // Set radius to 15.0f
}

// Destructor
SuperPellet::~SuperPellet() {
}

// Check if Pac-Man collides with the super pellet
bool SuperPellet::checkCollision(float pacManX, float pacManY, float pacManRadius) const {
    return active && CheckCollisionCircles({ pacManX, pacManY }, pacManRadius, { getX(), getY() }, getRadius());
}
