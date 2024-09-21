#ifndef GAMEKEY_H
#define GAMEKEY_H

#include "Collectable.h"
#include <vector>

class GameKey : public Collectable {
public:
    // Constructor that accepts position (x, y), a texture reference, and a vector of walls to unlock
    GameKey(float x, float y, const std::vector<int>& wallsToUnlock);
    ~GameKey();

    const std::vector<int>& getWallsToUnlock() const; // Return the list of walls this key unlocks

private:
    std::vector<int> wallsToUnlock; // Walls that this key unlocks
};

#endif // GAMEKEY_H