// Collectable.h
#pragma once
#include <raylib-cpp.hpp>

class Collectable {
protected:
    float x;
    float y;
    float radius;
    bool active;
    Texture2D texture;

public:
    Collectable(float x, float y, float radius, Texture2D texture);
    virtual ~Collectable();

    virtual void draw() const;
    virtual void collect();
    bool isActive() const;

    float getX() const;
    float getY() const;
    float getRadius() const;

    // Optionally, if collision logic is common
    virtual bool checkCollision(float otherX, float otherY, float otherRadius) const;
};
