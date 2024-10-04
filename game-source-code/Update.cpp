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
            game.getScore().addPoints(100);  // Add 100 points for eating a power pellet

            // Make ghosts frightened
            for (auto& ghost : game.ghosts) {
                ghost->setFrightened(true);
            }

            // Start a timer to end frightened mode after a certain time
            game.powerPelletTimer = GetTime();  // Set the time when pellet is eaten
        }
    }

    // Revert ghosts to normal if the frightened mode time has expired
    if (GetTime() - game.powerPelletTimer > 5.0f) {  // For example, frightened lasts 5 seconds
        for (auto& ghost : game.ghosts) {
            ghost->setFrightened(false);  // Switch back to normal texture and mode
        }
    }
}

void Update::updateSuperPellets() {
    for (auto& superPellet : game.superPellets) {
        if (superPellet->isActive() && superPellet->checkCollision(game.pacMan->getX(), game.pacMan->getY(), game.pacMan->getRadius())) {
            superPellet->collect(); // Pac-Man collects the super pellet
            game.pacMan->activateSuperMode();
            game.getScore().addPoints(500); // Add points for collecting a super pellet
        }
    }
    // If Pac-Man is in super mode, check if he's moving through any locked walls
    if (game.pacMan->isSuper()) {
        for (auto& key : game.keys) {
            // Iterate through the walls that the key can unlock
            for (int wallIndex : key.getWallsToUnlock()) {
                Maze::Wall& wall = game.maze->getWalls()[wallIndex];  // Get the wall

                // Only proceed if the wall is still active (locked)
                if (wall.active) {
                    // Output Pac-Man and wall positions for debugging

                    // Define Pac-Man's bounding circle
                    Vector2 pacManCenter = { game.pacMan->getX(), game.pacMan->getY() };
                    float pacManRadius = game.pacMan->getRadius() * 1.1;

                    // Define the wall's rectangle
                    Rectangle wallRec = wall.rect;

                    // Check for a collision between Pac-Man's circle and the wall's rectangle
                    if (CheckCollisionCircleRec(pacManCenter, pacManRadius, wallRec)) {
                        wall.active = false;  // Unlock the wall (deactivate it)
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
                { (float)fruit->getX(), (float)fruit->getY() }, fruit->getRadius())) {
            fruit->collect();
            game.getScore().addPoints(10); // Add points for collecting a fruit
        }
    }
}

void Update::updateStars() {
    float updatedTimer = GetTime() - game.timerStart;
    for (auto& stars : game.stars) {
        if ((updatedTimer) >= 2 * game.multi) {
            game.num1 = rand() % 6 + 1;
            game.num2 = rand() % 6 + 1;
            game.multi++;
        }
        draw->drawSymbols(game.num1, game.num2);
        if ((updatedTimer) >= 30 * game.multi2) {
            stars->show();
            draw->setSymbolActive(true);
            game.multi2++;
        }

        if (stars->isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius() - 30,
                { (float)stars->getX(), (float)stars->getY() }, stars->getRadius())) {
            if (game.num1 == game.num2 && game.num2 == game.num3) {
                game.getScore().addPoints(5000);
            } else if (game.num1 == game.num2) {
                game.getScore().addPoints(2000);
            } else {
                game.getScore().addPoints(500);
            }
            stars->collect();
            draw->setSymbolActive(false);
        }
    }
}

void Update::updateKeys() {
    for (auto& key : game.keys) {
        if (key.isActive() && CheckCollisionCircles(
                { game.pacMan->getX(), game.pacMan->getY() }, game.pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            key.collect();
            game.getScore().addPoints(50);
            for (int wallIndex : key.getWallsToUnlock()) {
                game.getMaze().getWalls()[wallIndex].active = false;
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
                    ghost->setEaten(true);
                    ghost->respawn();
                    game.getScore().addPoints(200);
                } else if (game.pacMan->isSuper()) {
                    continue;
                } else {
                    game.playerLives->loseLife();
                    for (const auto& ghost : game.ghosts) {
                        ghost->respawn();
                    }
                    if (!game.playerLives->isAlive()) {
                        game.isRunning = false;
                        return;
                    }
                    game.pacMan->setInvincible(true);
                    break;
                }
            }
        }
    }
    else {
        for (const auto& ghost : game.ghosts) {
            int ghostDirection = ghost->move(*game.maze,*game.pacMan, deltaTime);
        }
    }
}





