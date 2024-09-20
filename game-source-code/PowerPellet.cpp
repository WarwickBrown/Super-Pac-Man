#include "PowerPellet.h"

// Constructor to initialize the power pellet with position and texture
PowerPellet::PowerPellet(float x, float y)
    : x(x), y(y), active(true), radius(10.0f) {}

// Destructor
PowerPellet::~PowerPellet() {
    // Unload the texture when the power pellet is destroyed
}

void PowerPellet::draw() const {
    if (active) {
        Rectangle sourceRec = {
        (float)(powerPelletTexture.width) ,  // Calculate width of a single frame
        0, 
        (float)(powerPelletTexture.width),          // Width of a single frame
        (float)(powerPelletTexture.height)              // Full height of the texture
    };

    DrawTextureRec(powerPelletTexture, sourceRec, Vector2{(float)getX()-28, (float)getY()-28}, RAYWHITE);
    }
}

// Check if the power pellet is active (not yet collected)
bool PowerPellet::isActive() const {
    return active;
}

// Mark the power pellet as collected
void PowerPellet::collect() {
    active = false;
}

// Get the X position of the power pellet
float PowerPellet::getX() const {
    return x;
}

// Get the Y position of the power pellet
float PowerPellet::getY() const {
    return y;
}

// Get the radius of the power pellet
float PowerPellet::getRadius() const {
    return radius;
}

// Check if Pac-Man collides with the power pellet
bool PowerPellet::checkCollisionWithPacMan(const PacMan& pacman) {
    if (active && CheckCollisionCircles(
            { pacman.getX(), pacman.getY() }, pacman.getRadius(),
            { x, y }, radius)) {
        collect();  // If collision occurs, mark the pellet as collected
        return true;
    }
    return false;
}