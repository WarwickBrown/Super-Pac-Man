#pragma once
#include <raylib-cpp.hpp>

class Collectable {
protected:
    float x;
    float y;
    float radius;
    bool active;

public:
    Collectable(float x, float y, float radius);
    virtual ~Collectable();

    virtual void collect() { active = false; }

    bool isActive() const { return active; }    // Used to check if the item has been collected

    // Getters for coordinates and radius (mostly for tests)
    float getX() const { return x; }    
    float getY() const { return y; }
    float getRadius() const { return radius; }

    virtual bool checkCollision(float otherX, float otherY, float otherRadius) const;
};