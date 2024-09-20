// PowerPellet.h
#pragma once
#include "Collectable.h"
#include "PacMan.h"

class PowerPellet : public Collectable {
public:
    PowerPellet(float x, float y, Texture2D texture);
    // If no additional behavior is needed, you might not need extra methods
    bool checkCollisionWithPacMan(const PacMan& pacman); // Check if Pac-Man collided with the pellet
};


