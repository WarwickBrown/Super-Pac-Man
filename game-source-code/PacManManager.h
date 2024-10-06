#ifndef PACMANMANAGER_H
#define PACMANMANAGER_H

#include "Game.h"
#include <memory>

class PacManManager {
public:
    enum Direction {
        RIGHT = 1,
        LEFT,
        UP,
        DOWN
    };

    explicit PacManManager(Game& game);

    // Update Pac-Man's direction and movement
    void updatePacMan(float deltaTime);

private:
    Game& game;  // Reference to the game object to access maze, Pac-Man, etc.
};

#endif // PACMANMANAGER_H