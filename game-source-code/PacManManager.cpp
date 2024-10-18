/**
 * @file PacManManager.cpp
 * @brief Implements the PacManManager class, which manages Pac-Man's state and movement.
 * 
 * The PacManManager class handles Pac-Man's interactions with the game environment,
 * including movement, state updates, and collision detection with maze walls.
 */

#include "PacManManager.h"
#include "PacMan.h"

PacManManager::PacManManager(Game& game) : game(game) {}

void PacManManager::updatePacMan(float deltaTime) {
    // initialise movement deltas (dx, dy) to zero.
    auto dx = 0, dy = 0;

    // Determine movement direction based on the game's current direction state.
    switch (static_cast<PacMan::Direction>(game.getDirection())) {
    case PacMan::RIGHT:
        dx = 1; dy = 0;
        break;
    case PacMan::LEFT:
        dx = -1; dy = 0;
        break;
    case PacMan::UP:
        dx = 0; dy = -1;
        break;
    case PacMan::DOWN:
        dx = 0; dy = 1;
        break;
    default:
        dx = 0; dy = 0;  // No movement if direction is NONE.
        break;
    }

    // Check if Pac-Man is attempting to move in a valid direction.
    if (dx != 0 || dy != 0) {
        // Calculate Pac-Man's potential new position.
        auto newX = game.pacMan->getX() + dx;
        auto newY = game.pacMan->getY() + dy;

        // Check if Pac-Man can move to the new position without colliding with a wall.
        if (!game.getMaze().isWallRec(newX, newY, 34)) {
            game.pacManOldDirection = game.getDirection();  ///< Update old direction if no wall collision.
        }

        // Update Pac-Man's state and move.
        game.pacMan->updateSuperMode(deltaTime);            ///< Update super mode state.
        game.pacMan->updateInvincibility(deltaTime);        ///< Update invincibility state.
        game.pacMan->move(game.getMaze(), deltaTime, static_cast<PacMan::Direction>(game.pacManOldDirection));  ///< Move Pac-Man.
    }
}