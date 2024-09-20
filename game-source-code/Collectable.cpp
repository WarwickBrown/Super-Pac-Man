// Collectable.cpp
#include "Collectable.h"

Collectable::Collectable(float x, float y, float radius, Texture2D texture)
    : x(x), y(y), radius(radius), active(true), texture(texture) {}

Collectable::~Collectable() {
    UnloadTexture(texture);
}

void Collectable::draw() const {
    if (active) {
        DrawTexture(texture, x - radius, y - radius, WHITE);
    }
}

void Collectable::collect() {
    active = false;
}

bool Collectable::isActive() const {
    return active;
}

float Collectable::getX() const {
    return x;
}

float Collectable::getY() const {
    return y;
}

float Collectable::getRadius() const {
    return radius;
}

bool Collectable::checkCollision(float otherX, float otherY, float otherRadius) const {
    return active && CheckCollisionCircles({ x, y }, radius, { otherX, otherY }, otherRadius);
}
