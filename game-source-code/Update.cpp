/**
 * @file Update.cpp
 * @brief Implements the Update class, responsible for updating the state of various game components.
 * 
 * This file defines the methods for the Update class, including updating power pellets, super pellets,
 * fruits, stars, keys, and Pac-Man's invincibility state. It interacts with the Game and Draw classes
 * to update the game world during each frame.
 */

#include "Update.h"

/**
 * @brief Constructs an Update object using a reference to the Game instance and a pointer to the Draw instance.
 * 
 * Initialises the Update class with references to the main Game and Draw instances, allowing
 * it to access and modify game components during each frame update.
 * 
 * @param game Reference to the Game instance.
 * @param drawInstance Pointer to the Draw instance.
 */
Update::Update(Game& game, Draw* drawInstance) : game(game), draw(drawInstance) {}

/**
 * @brief Updates the state of the entire game, including all collectibles and player status.
 * 
 * This method calls individual update functions for each collectible type and player state,
 * ensuring that the game elements are properly updated during each frame.
 * 
 * @param deltaTime The time elapsed since the last frame, used for smooth updates.
 */
void Update::updateGame(float deltaTime) {
    updateFruits();
    updatePowerPellets();
    updateSuperPellets();
    updateStars();
    updateKeys();
    updateInvincibility(deltaTime);
}

/**
 * @brief Updates the state of power pellets and handles collision detection with Pac-Man.
 * 
 * Checks if Pac-Man collides with any active power pellet, and if so, activates frightened mode
 * for all ghosts and awards points to Pac-Man.
 */
void Update::updatePowerPellets() {
    for (auto& pellet : game.powerPellets) {
        if (pellet->checkCollisionWithPacMan(*game.pacMan)) {
            game.getScore().addPoints(100);  ///< Add 100 points for eating a power pellet.

            // Make all ghosts frightened.
            for (auto& ghost : game.ghosts) {
                ghost->setFrightened(true);
            }

            // Start a timer to end frightened mode after a certain time.
            game.powerPelletTimer = GetTime();  ///< Set the time when the pellet is eaten.
        }
    }

    // Revert ghosts to normal if the frightened mode time has expired.
    if (GetTime() - game.powerPelletTimer > 5.0f) {  ///< Frightened mode lasts for 5 seconds.
        for (auto& ghost : game.ghosts) {
            ghost->setFrightened(false);  ///< Switch ghosts back to normal mode.
        }
    }
}

/**
 * @brief Updates the state of super pellets and handles collision detection with Pac-Man.
 * 
 * Checks if Pac-Man collides with any active super pellet, and if so, activates super mode for
 * Pac-Man, deactivates the pellet, and awards points to Pac-Man.
 */
void Update::updateSuperPellets() {
    for (auto& superPellet : game.superPellets) {
        if (superPellet->isActive() && superPellet->checkCollision(game.pacMan->getX(), game.pacMan->getY(), game.pacMan->getRadius())) {
            superPellet->collect();  ///< Pac-Man collects the super pellet.
            game.pacMan->activateSuperMode();
            game.getScore().addPoints(500);  ///< Add 500 points for collecting a super pellet.
        }
    }

    // If Pac-Man is in super mode, check if he's moving through any locked walls.
    if (game.pacMan->isSuper()) {
        for (auto& key : game.keys) {
            for (int wallIndex : key.getWallsToUnlock()) {
                auto& wall = game.maze->getWalls()[wallIndex];  ///< Get the wall reference.

                if (wall.active) {  ///< Only proceed if the wall is still active (locked).
                    Vector2 pacManCenter = { game.pacMan->getX(), game.pacMan->getY() };
                    auto pacManRadius = game.pacMan->getRadius() * 1.1;

                    // Check for a collision between Pac-Man's circle and the wall's rectangle.
                    if (CheckCollisionCircleRec(pacManCenter, pacManRadius, wall.rect)) {
                        wall.active = false;  ///< Unlock the wall (deactivate it).
                    }
                }
            }
        }
    }
}

/**
 * @brief Updates the state of fruits and handles collision detection with Pac-Man.
 * 
 * Checks if Pac-Man collides with any active fruit, and if so, collects the fruit and awards
 * points to Pac-Man.
 */
void Update::updateFruits() {
    for (auto& fruit : game.fruits) {
        if (fruit->isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius() - 35,
                { static_cast<float>(fruit->getX()), static_cast<float>(fruit->getY()) }, fruit->getRadius())) {
            fruit->collect();  ///< Collect the fruit.
            game.getScore().addPoints(10);  ///< Add 10 points for collecting a fruit.
        }
    }
}

/**
 * @brief Updates the state of stars and handles collision detection with Pac-Man.
 * 
 * Manages the appearance of stars, checks for collisions with Pac-Man, and awards points based
 * on the current star conditions.
 */
void Update::updateStars() {
    auto updatedTimer = GetTime() - game.timerStart;
    for (auto& stars : game.stars) {
        if (updatedTimer >= 2 * game.multi) {
            game.fruitSymbolOne = rand() % 6 + 1;
            game.fruitSymbolTwo = rand() % 6 + 1;
            game.multi++;
        }
        draw->drawSymbols(game.fruitSymbolOne, game.fruitSymbolTwo);
        if (updatedTimer >= 30 * game.multi2) {
            stars->show();
            draw->setSymbolActive(true);
            game.multi2++;
        }

        if (stars->isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius() - 30,
                { static_cast<float>(stars->getX()), static_cast<float>(stars->getY()) }, stars->getRadius())) {
            if (game.fruitSymbolOne == game.fruitSymbolTwo && game.fruitSymbolTwo == game.fruitSymbolInMaze) {
                game.getScore().addPoints(5000);
            } else if (game.fruitSymbolOne == game.fruitSymbolTwo) {
                game.getScore().addPoints(2000);
            } else {
                game.getScore().addPoints(500);
            }
            stars->collect();  ///< Collect the star.
            draw->setSymbolActive(false);
        }
    }
}

/**
 * @brief Updates the state of keys and handles collision detection with Pac-Man.
 * 
 * Checks if Pac-Man collides with any active key, and if so, deactivates the key, unlocks the
 * corresponding walls, and awards points to Pac-Man.
 */
void Update::updateKeys() {
    for (auto& key : game.keys) {
        if (key.isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            key.collect();
            game.getScore().addPoints(50);  ///< Add 50 points for collecting a key.
            for (int wallIndex : key.getWallsToUnlock()) {
                game.getMaze().getWalls()[wallIndex].active = false;  ///< Deactivate the walls.
            }
        }
    }
}

/**
 * @brief Updates Pac-Man's invincibility state and handles collision detection with ghosts.
 * 
 * Manages Pac-Man's invincibility state and handles collision detection between Pac-Man and
 * ghosts. If Pac-Man collides with a ghost, determines the outcome based on Pac-Man's state.
 * 
 * @param deltaTime The time elapsed since the last frame, used for smooth updates.
 */
void Update::updateInvincibility(float deltaTime) {
    if (!game.pacMan->isInvincible()) {
        for (const auto& ghost : game.ghosts) {
            int ghostDirection = ghost->move(game.getMaze(), *game.pacMan, deltaTime);
            if (ghost->checkCollisionWithPacMan(*game.pacMan)) {
                if (ghost->isFrightened()) {
                    ghost->setEaten(true);
                    ghost->respawn();
                    game.getScore().addPoints(200);  ///< Add 200 points for eating a frightened ghost.
                } else if (game.pacMan->isSuper()) {
                    continue;
                } else {
                    game.playerLives->loseLife();
                    for (const auto& ghost : game.ghosts) {
                        ghost->respawn();  ///< Respawn all ghosts.
                    }
                    if (!game.playerLives->isAlive()) {
                        game.isRunning = false;
                        return;  ///< Stop the game if no lives remain.
                    }
                    game.pacMan->setInvincible(true);  ///< Activate Pac-Man's invincibility.
                    break;
                }
            }
        }
    }
    else {
        for (const auto& ghost : game.ghosts) {
            int ghostDirection = ghost->move(*game.maze, *game.pacMan, deltaTime);
        }
    }
}
