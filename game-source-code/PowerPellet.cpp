// PowerPellet.cpp
#include "PowerPellet.h"

PowerPellet::PowerPellet(float x, float y, Texture2D texture)
    : Collectable(x, y, 10.0f, texture) {}


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