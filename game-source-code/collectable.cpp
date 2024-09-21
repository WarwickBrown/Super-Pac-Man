#include "Collectable.h"

Collectable::Collectable(float x, float y, float radius)
    : x(x), y(y), radius(radius), active(true) {}

Collectable::~Collectable() {
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
