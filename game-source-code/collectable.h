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

    bool isActive() const { return active; }

    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return radius; }

    // Optionally, if collision logic is common
    virtual bool checkCollision(float otherX, float otherY, float otherRadius) const;
};
