/**
 * @file Update.cpp
 * @brief Implements the Update class, responsible for updating the state of various game components.
 * 
 * This file defines the methods for the Update class, including updating power pellets, super pellets,
 * fruits, stars, keys, and Pac-Man's invincibility state. It interacts with the Game and Draw classes
 * to update the game world during each frame.
 */

#include "Update.h"

Update::Update(Game& game, Draw* drawInstance) : game(game), draw(drawInstance) {}

void Update::updateGame(float deltaTime) {
    updateFruits();
    updatePowerPellets();
    updateSuperPellets();
    updateStars();
    updateKeys();
    updateInvincibility(deltaTime);
}

void Update::updatePowerPellets() {
    for (auto& pellet : game.powerPellets) {
        if (pellet->checkCollisionWithPacMan(*game.pacMan)) {
            game.getScore().addPoints(100);  ///< Add 100 points for eating a power pellet.
            game.soundManager->playSound("power_pellet");
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

void Update::updateSuperPellets() {
    for (auto& superPellet : game.superPellets) {
        if (superPellet->isActive() && superPellet->checkCollision(game.pacMan->getX(), game.pacMan->getY(), game.pacMan->getRadius())) {
            game.soundManager->stopSound("super_pellet");
            game.soundManager->playSound("super_pellet");
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

void Update::updateFruits() {
    for (auto& fruit : game.fruits) {
        if (fruit->isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius() - 35,
                { static_cast<float>(fruit->getX()), static_cast<float>(fruit->getY()) }, fruit->getRadius())) {
                game.soundManager->playSound("fruit_collect");
            fruit->collect();  ///< Collect the fruit.
            game.getScore().addPoints(10);  ///< Add 10 points for collecting a fruit.
        }
    }
}

void Update::updateStars() {
    auto updatedTimer = GetTime() - game.timerStart;
    for (auto& stars : game.stars) {
        if (updatedTimer >= 2 * game.multi) {
            game.fruitSymbolOne = rand() % 6 + 1;   ///< Generates a random number for the symbol in the left box.
            game.fruitSymbolTwo = rand() % 6 + 1;   ///< Generates a random number for the symbol in the left box.
            game.multi++;
        }
        draw->drawSymbols(game.fruitSymbolOne, game.fruitSymbolTwo);
        if (updatedTimer >= 30 * game.multi2) {
            stars->show();  ///< Show the stars after 30 seconds.
            draw->setSymbolActive(true);    ///< Show the symbols in the boxes.
            game.multi2++;
        }

        if (stars->isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius() - 30,
                { static_cast<float>(stars->getX()), static_cast<float>(stars->getY()) }, stars->getRadius())) {
                game.soundManager->playSound("star_collect");
            if (game.fruitSymbolOne == game.fruitSymbolTwo && game.fruitSymbolTwo == game.fruitSymbolInMaze) {  ///< If the symbols in the boxes both match and are the same as the fruits.
                game.getScore().addPoints(5000);    
            } else if (game.fruitSymbolOne == game.fruitSymbolTwo) {    ///< If both symbols in the boxes match.
                game.getScore().addPoints(2000);
            } else {    ///< If neither of the symbols in the boxes match.
                game.getScore().addPoints(500);
            }
            stars->collect();  ///< Collect the star.
            draw->setSymbolActive(false);   ///< Hides the symbols.
        }
    }
}

void Update::updateKeys() {
    for (auto& key : game.keys) {
        if (key.isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            game.soundManager->playSound("key_collect");
            key.collect();  ///< Collect the key.
            game.getScore().addPoints(50);  ///< Add 50 points for collecting a key.
            for (int wallIndex : key.getWallsToUnlock()) {
                game.getMaze().getWalls()[wallIndex].active = false;  ///< Deactivate the walls.
            }
        }
    }
}

void Update::updateInvincibility(float deltaTime) {
    if (!game.pacMan->isInvincible()) {
        for (const auto& ghost : game.ghosts) {
            int ghostDirection = ghost->move(game.getMaze(), *game.pacMan, deltaTime);
            if (ghost->checkCollisionWithPacMan(*game.pacMan)) {
                if (ghost->isFrightened()) {
                    game.soundManager->playSound("ghost_eaten");
                    ghost->setEaten(true);
                    ghost->respawn();
                    game.getScore().addPoints(200);  ///< Add 200 points for eating a frightened ghost.
                } else if (game.pacMan->isSuper()) {
                    continue;
                } else {
                    game.soundManager->playSound("lose_life");
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