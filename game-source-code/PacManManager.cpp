#include "PacManManager.h"

PacManManager::PacManManager(Game& game) : game(game) {}

void PacManManager::updatePacMan(float deltaTime) {
    // Update Pac-Man's movement based on the direction
    int dx = 0, dy = 0;

    switch (game.getDirection()) {
    case 1: dx = 1; dy = 0; break;    // Right movement
    case 2: dx = -1; dy = 0; break;   // Left movement
    case 3: dx = 0; dy = -1; break;   // Up movement
    case 4: dx = 0; dy = 1; break;    // Down movement
    default: dx = 0; dy = 0; break;
    }

    float newX = game.pacMan->getX() + dx;
    float newY = game.pacMan->getY() + dy;

    // Check if Pac-Man can move in the new direction (no collision with walls)
    if (!game.getMaze().isWallRec(newX, newY, 34)) {
        game.oldDirection = game.getDirection();  // Update old direction if no wall collision
    }

    // Update Pac-Man's state and move
    game.pacMan->updateSuperMode(deltaTime);
    game.pacMan->updateInvincibility(deltaTime);
    game.pacMan->move(game.getMaze(), deltaTime, game.oldDirection);
}