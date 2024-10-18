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


Star::Star(int x, int y)
    : Collectable(x, y, 20.0f),  ///< Call the base class constructor with the position and radius.
    change(false) {
    active = false;  ///< Set the star to be initially inactive.
}

Star::~Star() {
    // Base class destructor will handle unloading the texture.
}

void Star::show() {
    active = true;  ///< Set the star's active state to true.
}

void Star::determineChange() {
    auto updatedTime = GetTime() - startTime;  ///< Calculate the time elapsed since the start.
    if (updatedTime >= multiple * 0.2) {
        multiple++;      ///< Increment the multiple to increase time intervals.
        change = true;   ///< Set the `change` flag to true, indicating a texture change.
    }
}