#ifndef PACMANMANAGER_H
#define PACMANMANAGER_H

#include "Game.h"
#include <memory>

class PacManManager {
public:
    explicit PacManManager(Game& game);

    // Update Pac-Man's direction and movement
    void updatePacMan(float deltaTime);

private:
    Game& game;  // Reference to the game object to access maze, Pac-Man, etc.

    // Helper function to update direction and movement
    void updateDirection();
};

#endif // PACMANMANAGER_H