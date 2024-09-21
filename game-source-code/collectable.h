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

    virtual void collect();
    bool isActive() const;

    float getX() const;
    float getY() const;
    float getRadius() const;

    // Optionally, if collision logic is common
    virtual bool checkCollision(float otherX, float otherY, float otherRadius) const;
};
