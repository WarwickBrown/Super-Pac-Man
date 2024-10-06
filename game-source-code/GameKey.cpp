/**
 * @file GameKey.cpp
 * @brief Implements the GameKey class, which represents a key that can unlock specific walls in the game.
 */

#include "GameKey.h"

/**
 * @brief Constructs a GameKey object with a specified position and list of walls to unlock.
 * 
 * @param x The x-coordinate of the key's position.
 * @param y The y-coordinate of the key's position.
 * @param wallsToUnlock A vector of integers representing the indices of walls that this key can unlock.
 * 
 * The constructor uses the base class Collectable's constructor to initialise the position and radius of the key.
 * The radius of the key is set to a fixed value of 10.0f.
 */
GameKey::GameKey(float x, float y, const std::vector<int>& wallsToUnlock)
    : Collectable(x, y, 10.0f), wallsToUnlock(wallsToUnlock) {}

/**
 * @brief Destructor for the GameKey class.
 * 
 * This destructor doesn't perform any special operations, but is defined for completeness.
 */
GameKey::~GameKey() {}

/**
 * @brief Returns the list of walls that this key unlocks.
 * 
 * @return A constant reference to a vector of integers representing the indices of walls this key can unlock.
 */
const std::vector<int>& GameKey::getWallsToUnlock() const {
    return wallsToUnlock;
}
