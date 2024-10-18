/**
 * @file GameKey.cpp
 * @brief Implements the GameKey class, which represents a key that can unlock specific walls in the game.
 */

#include "GameKey.h"

GameKey::GameKey(float x, float y, const std::vector<int>& wallsToUnlock)
    : Collectable(x, y, 10.0f), wallsToUnlock(wallsToUnlock) {}

GameKey::~GameKey() {}

const std::vector<int>& GameKey::getWallsToUnlock() const {
    return wallsToUnlock;
}