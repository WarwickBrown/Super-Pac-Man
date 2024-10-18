/**
 * @file Collectable.cpp
 * @brief Header and implementation for the Collectable class.
 */

#include "Collectable.h"

Collectable::Collectable(float x, float y, float radius)
    : x(x), y(y), radius(radius), active(true) {}

Collectable::~Collectable() {}

bool Collectable::checkCollision(float otherX, float otherY, float otherRadius) const {
    return active && CheckCollisionCircles({ x, y }, radius, { otherX, otherY }, otherRadius);
}