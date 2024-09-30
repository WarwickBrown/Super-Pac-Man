#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "Collectable.h"
#include "PacMan.h"
#include <raylib-cpp.hpp>

class PowerPellet : public Collectable {
public:
    // Constructor that accepts position (x, y) and initialises Collectable with the texture and radius
    PowerPellet(float x, float y);

    // Destructor
    ~PowerPellet();

    // Checks if Pac-Man collides with the Power Pellet
    bool checkCollisionWithPacMan(const PacMan& pacman);

};

#endif // POWERPELLET_H