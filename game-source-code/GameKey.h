/**
 * @file GameKey.h
 * @brief Defines the GameKey class, a type of collectable that can unlock specific walls in the game.
 */

#ifndef GAMEKEY_H
#define GAMEKEY_H

#include "Collectable.h"
#include <vector>

/**
 * @class GameKey
 * @brief A collectable key that unlocks specific walls within the maze.
 * 
 * The GameKey class is derived from the Collectable class and is used to represent keys in the game.
 * Each key has a list of wall indices that it can unlock, providing new pathways or access to different areas.
 */
class GameKey : public Collectable {
public:
    /**
     * @brief Constructs a GameKey object with a specified position and list of walls to unlock.
     * 
     * @param x The x-coordinate of the key's position.
     * @param y The y-coordinate of the key's position.
     * @param wallsToUnlock A vector of integers representing the indices of walls that this key can unlock.
     */
    GameKey(float x, float y, const std::vector<int>& wallsToUnlock);

    /**
     * @brief Destructor for the GameKey class.
     */
    ~GameKey();

    /**
     * @brief Returns the list of walls that this key unlocks.
     * 
     * @return A constant reference to a vector of integers representing the indices of walls this key can unlock.
     */
    const std::vector<int>& getWallsToUnlock() const;

private:
    std::vector<int> wallsToUnlock; ///< Vector of wall indices that this key unlocks.
};

#endif // GAMEKEY_H