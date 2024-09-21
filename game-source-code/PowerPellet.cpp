#include "PowerPellet.h"

// Constructor to initialize the power pellet using the Collectable constructor
PowerPellet::PowerPellet(float x, float y)
    : Collectable(x, y, 10.0f) { // Set radius to 10.0f
}

// Destructor
PowerPellet::~PowerPellet() {
}

// Check if Pac-Man collides with the power pellet
bool PowerPellet::checkCollisionWithPacMan(const PacMan& pacman) {
    if (active && CheckCollisionCircles(
            { pacman.getX(), pacman.getY() }, pacman.getRadius(),
            { getX(), getY() }, getRadius())) {
        collect();  // If collision occurs, mark the pellet as collected
        return true;
    }
    return false;
}