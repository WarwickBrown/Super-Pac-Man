#ifndef SUPERPELLET_H
#define SUPERPELLET_H

#include "Collectable.h"
#include <raylib-cpp.hpp>

class SuperPellet : public Collectable {
public:
    SuperPellet(float x, float y); // Constructor
    ~SuperPellet();                // Destructor

    // Check for collision with Pac-Man
    bool checkCollision(float pacManX, float pacManY, float pacManRadius) const;

    // Mark the Super Pellet as collected
    void collect() { active = false; }
};

#endif // SUPERPELLET_H