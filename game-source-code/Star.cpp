/**
 * @file Star.cpp
 * @brief Implements the Star class, which represents a collectible star in the game.
 * 
 * This file defines the methods for managing the star's state, determining when to change its texture,
 * and handling its active state in the game.
 */

#include "Star.h"
#include <cstdlib>
#include <iostream> 

/**
 * @brief Constructs a Star object with a specified position and initialises it.
 * 
 * This constructor initialises the Star object using the base class Collectable's constructor
 * and sets its position, radius, and active state. The star is initially inactive.
 * 
 * @param x The x-coordinate of the star's position.
 * @param y The y-coordinate of the star's position.
 */
Star::Star(int x, int y)
    : Collectable(x, y, 20.0f),  ///< Call the base class constructor with the position and radius.
    change(false) {
    active = false;  ///< Set the star to be initially inactive.
}

/**
 * @brief Destructor for the Star class.
 * 
 * This destructor does not perform any specific actions as there is no dynamic memory
 * allocation, but it is defined for completeness.
 */
Star::~Star() {
    // Base class destructor will handle unloading the texture.
}

/**
 * @brief Activates the star, making it visible and collectible in the game.
 * 
 * This method sets the star's active state to true, making it visible in the game.
 */
void Star::show() {
    active = true;  ///< Set the star's active state to true.
}

/**
 * @brief Determines if the star's texture should change based on elapsed time.
 * 
 * This method uses the elapsed time since the star was created to determine if its texture
 * should change. If the time condition is met, the `change` flag is set to true.
 */
void Star::determineChange() {
    auto updatedTime = GetTime() - startTime;  ///< Calculate the time elapsed since the start.
    if (updatedTime >= multiple * 0.2) {
        multiple++;      ///< Increment the multiple to increase time intervals.
        change = true;   ///< Set the `change` flag to true, indicating a texture change.
    }
}
