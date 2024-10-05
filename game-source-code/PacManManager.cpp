#include "PacManManager.h"

PacManManager::PacManManager(Game& game) : game(game) {}

void PacManManager::updatePacMan(float deltaTime) {
    // Update Pac-Man's movement based on the direction
    auto dx = 0, dy = 0;

    switch (game.getDirection()) {
    case RIGHT:
        dx = 1; dy = 0;
        break;
    case LEFT:
        dx = -1; dy = 0;
        break;
    case UP:
        dx = 0; dy = -1;
        break;
    case DOWN:
        dx = 0; dy = 1;
        break;
    default:
        dx = 0; dy = 0;
        break;
}

    if (dx!= 0 || dy != 0) {
        auto newX = game.pacMan->getX() + dx;
        auto newY = game.pacMan->getY() + dy;

        // Check if Pac-Man can move in the new direction (no collision with walls)
        if (!game.getMaze().isWallRec(newX, newY, 34)) {
            game.pacManOldDirection = game.getDirection();  // Update old direction if no wall collision
        }

        // Update Pac-Man's state and move
        game.pacMan->updateSuperMode(deltaTime);
        game.pacMan->updateInvincibility(deltaTime);
        game.pacMan->move(game.getMaze(), deltaTime, static_cast<PacMan::Direction>(game.pacManOldDirection));
    }
}