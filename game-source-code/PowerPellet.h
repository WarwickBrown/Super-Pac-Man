#ifndef POWER_PELLET_H
#define POWER_PELLET_H

#include <raylib-cpp.hpp>
#include "PacMan.h"

class PowerPellet {
public:
    PowerPellet(float x, float y); // Constructor
    ~PowerPellet(); // Destructor

    void draw() const;           // Render the power pellet
    bool isActive() const;       // Check if the power pellet is still active
    void collect();              // Mark the power pellet as collected
    float getX() const;          // Get X position of the power pellet
    float getY() const;          // Get Y position of the power pellet
    float getRadius() const;     // Get the radius of the power pellet
    bool checkCollisionWithPacMan(const PacMan& pacman); // Check if Pac-Man collided with the pellet

private:
    float x, y;                  // Position of the power pellet
    bool active;                 // Is the power pellet still active (not eaten)?
    float radius;                // Radius of the power pellet
    Texture2D powerPelletTexture = LoadTexture("../resources/pacman-images/PowerPellet.png");  // Load power pellet texture
};

#endif
