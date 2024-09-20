#include "SuperPellet.h"

SuperPellet::SuperPellet(float x, float y) 
    : x(x), y(y), radius(15.0f), active(true) {
    texture = LoadTexture("../resources/pacman-images/Star3.png"); // Load super pellet texture
}

SuperPellet::~SuperPellet() {
    UnloadTexture(texture); // Unload texture when done
}

void SuperPellet::draw() const {
    if (active) {
        DrawTexture(texture, x - radius, y - radius, WHITE); // Draw the super pellet texture
    }
}

bool SuperPellet::checkCollision(float pacManX, float pacManY, float pacManRadius) const {
    // Check if Pac-Man's circle intersects with the super pellet's circle
    return active && CheckCollisionCircles({ pacManX, pacManY }, pacManRadius, { x, y }, radius);
}

void SuperPellet::collect() {
    active = false; // Mark as collected
}

bool SuperPellet::isActive() const {
    return active;
}