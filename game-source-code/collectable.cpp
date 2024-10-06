/**
 * @file Collectable.h
 * @brief Header and implementation for the Collectable class.
 */

#include "Collectable.h"

/**
 * @brief Constructs a Collectable object with a specified position and radius.
 * 
 * @param x The x-coordinate of the collectable.
 * @param y The y-coordinate of the collectable.
 * @param radius The radius of the collectable.
 */
Collectable::Collectable(float x, float y, float radius)
    : x(x), y(y), radius(radius), active(true) {}

/**
 * @brief Destructor for the Collectable class.
 */
Collectable::~Collectable() {}

/**
 * @brief Checks if the collectable collides with another circle.
 * 
 * @param otherX The x-coordinate of the other circle.
 * @param otherY The y-coordinate of the other circle.
 * @param otherRadius The radius of the other circle.
 * @return true if there is a collision, false otherwise.
 */
bool Collectable::checkCollision(float otherX, float otherY, float otherRadius) const {
    return active && CheckCollisionCircles({ x, y }, radius, { otherX, otherY }, otherRadius);
}