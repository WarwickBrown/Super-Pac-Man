/**
 * @file Collectable.h
 * @brief Defines the Collectable class, a base for all collectable objects in the game.
 */

#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <raylib-cpp.hpp>

/**
 * @class Collectable
 * @brief A base class representing a collectable item in a game.
 */
class Collectable {
protected:
    float x;      ///< The x-coordinate of the collectable.
    float y;      ///< The y-coordinate of the collectable.
    float radius; ///< The radius of the collectable.
    bool active;  ///< Indicates if the collectable is active (not collected).

public:
    /**
     * @brief Constructs a Collectable object with a specified position and radius.
     * 
     * @param x The x-coordinate of the collectable.
     * @param y The y-coordinate of the collectable.
     * @param radius The radius of the collectable.
     */
    Collectable(float x, float y, float radius);

    /**
     * @brief Virtual destructor for the Collectable class.
     */
    virtual ~Collectable();

    /**
     * @brief Marks the collectable as collected by setting it to inactive.
     */
    virtual void collect() { active = false; }

    /**
     * @brief Checks if the collectable is still active (not collected).
     * 
     * @return true if the collectable is active, false otherwise.
     */
    bool isActive() const { return active; }

    /**
     * @brief Gets the x-coordinate of the collectable.
     * 
     * @return The x-coordinate of the collectable.
     */
    float getX() const { return x; }    

    /**
     * @brief Gets the y-coordinate of the collectable.
     * 
     * @return The y-coordinate of the collectable.
     */
    float getY() const { return y; }

    /**
     * @brief Gets the radius of the collectable.
     * 
     * @return The radius of the collectable.
     */
    float getRadius() const { return radius; }

    /**
     * @brief Checks if the collectable collides with another circle.
     * 
     * @param otherX The x-coordinate of the other circle.
     * @param otherY The y-coordinate of the other circle.
     * @param otherRadius The radius of the other circle.
     * @return true if there is a collision, false otherwise.
     */
    virtual bool checkCollision(float otherX, float otherY, float otherRadius) const;
};

#endif // COLLECTABLE_H