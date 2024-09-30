#include "GameKey.h"

// Constructor using Collectable's constructor to initialise position, radius, and texture
GameKey::GameKey(float x, float y, const std::vector<int>& wallsToUnlock)
    : Collectable(x, y, 10.0f), wallsToUnlock(wallsToUnlock) {} // Assuming a fixed radius of 20 for GameKey

// Destructor
GameKey::~GameKey() {}

// Return the list of walls that this key unlocks
const std::vector<int>& GameKey::getWallsToUnlock() const {
    return wallsToUnlock;
}