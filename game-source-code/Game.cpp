#include "Game.h"
#include "Screen.h"
#include "Draw.h"
#include "Ghost.h"
#include "Star.h"
#include "Fruit.h"
#include "Lives.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"
#include "GameInitialiser.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <cmath>
#include <memory>

// Constructor - Initialises game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), direction(0), frame(0), gameWon(false) {}

// Destructor - Frees dynamically allocated memory for maze, pacMan, and screen
Game::~Game() = default;

// Function to initialise the game
void Game::initialise() {
    GameInitialiser::initialiseGameObjects(*this);  // Initialises game objects (maze, Pac-Man, screen)
    GameInitialiser::initialiseFruits(*this);
    GameInitialiser::initialiseKeys(*this);
    GameInitialiser::initialiseStars(*this);
    GameInitialiser::initialisePowerPellets(*this);
    GameInitialiser::initialiseSuperPellets(*this);
    maze->initialiseCustomWalls();

    score = std::make_unique<Score>("highscore.txt"); // Initialise the score object
    playerLives = std::make_unique<Lives>(3);

    // Display the start screen until the player presses ENTER or closes the window
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        screen->startScreen(this, screen.get(), *score); // Shows the start screen and passes the current game instance
    }

    // Check if the window is closed by the user
    if (window.ShouldClose()) {
        isRunning = false;  // Stop running the game if the window is closed
    }
}

// Main game loop
void Game::run() {
    int pixelX; // Coordinates for rendering
    int pixelY;

    // Continue the game loop until the window is closed or the game stops running
    while (isRunning && !window.ShouldClose()) {
        float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
        
        handleInput();   // Handle user input like key presses for movement
        update();        // Update game state (Pac-Man's position, etc.)
        screen->render(); // Render the current state of the game
        draw->drawMaze(*maze);  // Draw the maze
        draw->drawKeys(keys);
        frame = pacMan->location(frame);  // Update Pac-Man's frame for animation
        draw->drawFruits(fruits, num3);
        
        draw->drawStars(stars);

        for (const auto& star : stars) {
            star->determineChange();  // Use the star object directly
        }

        draw->drawPowerPellets(powerPellets);
        draw->drawSuperPellets(superPellets);
        
        // Draw the fruits on the screen
        draw->drawScores(*score); // Draw the scores
        draw->drawLives(playerLives->getLives());

        for (const auto& ghost : ghosts) {
            draw->drawGhost(*ghost, *pacMan, ghostDirection);
        }

        if (pacMan->isSuper()) {
            draw->drawSuperPacMan(*pacMan, frame, oldDirection);
        }
        else{
            draw->drawPacMan(*pacMan, frame, oldDirection);  // Draw Pac-Man with its current frame and direction
        }
        // If the game has been won, break the loop
        if (gameWon) {
            break;
        }
    }

    // Save high score when the game ends
    score->saveHighScore();

    // If the game is won, show the win screen
    if (gameWon) {
        isRunning = screen->winGame(*score);
    } else {
        isRunning = screen->endGame(*score);
    }
}


// Handles user input for controlling Pac-Man's direction
void Game::handleInput() {
    auto key = GetKeyPressed();
    // Check if the ESCAPE key is pressed to exit the game
    if (key == KEY_ESCAPE) {
        isRunning = false;  // Stop the game loop
        return;
    }

    // Detect arrow key presses to update Pac-Man's direction
    switch (key) {
    case KEY_RIGHT:
        direction = 1;  // Move right
        break;
    case KEY_LEFT:
        direction = 2;  // Move left
        break;
    case KEY_UP:
        direction = 3;  // Move up
        break;
    case KEY_DOWN:
        direction = 4;  // Move down
        break;
    default:
        // No direction change
        break;
    }
}

// Updates the game state (e.g., Pac-Man's position)
void Game::update() {
    int dx, dy;
    switch (direction) {
    case 1: 
            dx = 1; 
            dy = 0; 
            break;  // Right movement
        case 2: 
            dx = -1; 
            dy = 0; 
            break; // Left movement
        case 3: 
            dx = 0; 
            dy = -1; 
            break; // Down movement
        case 4: 
            dx = 0; 
            dy = 1; 
            break;  // Up movement
        default: 
            dx = 0; 
            dy = 0; 
            break;
    }

    float newX = pacMan->getX()+dx;
    float newY = pacMan->getY()+dy;
    if (!maze->isWallRec(newX, newY, 34)) {
        oldDirection = direction;
    }
    
    float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
    // Update Pac-Man's invincibility timer
    pacMan->updateSuperMode(deltaTime);
    pacMan->updateInvincibility(deltaTime);
    pacMan->move(*maze, deltaTime, oldDirection);  // Move Pac-Man based on the direction and elapsed time
    
    updateFruits();
    // Check if all fruits have been collected
    checkWinCondition();
    updatePowerPellets();
    updateKeys();
    updateSuperPellets();
    updateInvincibility(deltaTime);
    updateStars();
}

void Game::updateStars(){
    float updatedTimer = GetTime() - timerStart;
    for (auto& stars : stars) {
            if((updatedTimer) >= 3*multi){
                num1 = rand()%6+1;
                num2 = rand()%6+1;
                multi++;
            }
            
            draw->drawSymbols(num1, num2, symbolActive); 
            if((updatedTimer) >= 30*multi2)
            {
                stars->show();
                //draw->setSymbolActive(true);
                symbolActive = true;
                totalFrames = 1;
                multi2++;
            }
            else
            {
                totalFrames++;
            }
        if (stars->isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-30,
                { (float)stars->getX(), (float)stars->getY() }, stars->getRadius())) {
                    if(num1 == num2 && num2 == num3)
                    {
                        score->addPoints(5000); // Add points for collecting a key
                    }
                    else if(num1 == num2)
                    {
                        score->addPoints(2000); // Add points for collecting a key
                    }
                    else{
                        score->addPoints(500); // Add points for collecting a key
                    }
            stars->collect();
            //draw->setSymbolActive(false);
            symbolActive = false;
        }
    }
}

void Game::updateSuperPellets(){
    for (auto& superPellet : superPellets) {
        if (superPellet->isActive() && superPellet->checkCollision(pacMan->getX(), pacMan->getY(), pacMan->getRadius())) {
            superPellet->collect(); // Pac-Man collects the super pellet
            // Trigger super mode for Pac-Man (e.g., enlarge Pac-Man, increase speed, etc.)
            pacMan->activateSuperMode();
            score->addPoints(500); // Add points for collecting a super pellet
        }
    }

    // If Pac-Man is in super mode, check if he's moving through any locked walls
    if (pacMan->isSuper()) {
        for (auto& key : keys) {
            // Iterate through the walls that the key can unlock
            for (int wallIndex : key.getWallsToUnlock()) {
                Maze::Wall& wall = maze->getWalls()[wallIndex];  // Get the wall

                // Only proceed if the wall is still active (locked)
                if (wall.active) {
                    // Output Pac-Man and wall positions for debugging

                    // Define Pac-Man's bounding circle
                    Vector2 pacManCenter = { pacMan->getX(), pacMan->getY() };
                    float pacManRadius = pacMan->getRadius() * 1.1;

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

void Game::updateFruits(){
    // Check if Pac-Man collects any fruits
    for (auto& fruit : fruits) {
        if (fruit->isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-35,
                { (float)fruit->getX(), (float)fruit->getY() }, fruit->getRadius())) {
            fruit->collect();
            score->addPoints(10); // Add points for collecting a fruit
        }
    }
}

void Game::updateKeys(){
    // Check if Pac-Man collects any keys
    for (auto& key : keys) {
        if (key.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            key.collect();
            score->addPoints(50); // Add points for collecting a key
            // Unlock associated walls
            for (int wallIndex : key.getWallsToUnlock()) {
                maze->getWalls()[wallIndex].active = false;
            }
        }
    }
}

void Game::updatePowerPellets(){
    // Check if Pac-Man collects any power pellets
    for (auto& pellet : powerPellets) {
        if (pellet->checkCollisionWithPacMan(*pacMan)) {
            score->addPoints(100);  // Add 100 points for eating a power pellet

            // Make ghosts frightened
            for (auto& ghost : ghosts) {
                ghost->setFrightened(true);
            }

            // Start a timer to end frightened mode after a certain time
            // You can manage this with a timer or frame counting
            powerPelletTimer = GetTime();  // Set the time when pellet is eaten
        }
    }

    // Revert ghosts to normal if the frightened mode time has expired
    if (GetTime() - powerPelletTimer > 5.0f) {  // For example, frightened lasts 5 seconds
        for (auto& ghost : ghosts) {
            ghost->setFrightened(false);  // Switch back to normal texture and mode
        }
    }
}

void Game::updateInvincibility(float deltaTime){
    if (!pacMan->isInvincible()) {
        for (const auto& ghost : ghosts) {
            int ghostDirection = ghost->move(*maze,*pacMan, deltaTime);
            // Check for collision with Pac-Man
            if (ghost->checkCollisionWithPacMan(*pacMan)) {
                if (ghost->isFrightened()) {
                    // Pac-Man eats the ghost
                    ghost->setEaten(true);  // Mark the ghost as eaten
                    ghost->respawn();       // Respawn the ghost at the center of the maze
                    score->addPoints(200); // Increase score for eating a ghost
                } 
                else if (pacMan->isSuper()) {
                    continue;
                }
                else {
                    // Pac-Man is hit by a non-frightened ghost
                    playerLives->loseLife(); // Deduct a life
                    for (const auto& ghost : ghosts) {
                        ghost->respawn();
                    }
                    if (!playerLives->isAlive()) {
                        // Game over
                        isRunning = false;
                        return;
                    }

                    // Make Pac-Man invincible for a short time to avoid losing multiple lives instantly
                    pacMan->setInvincible(true);
                    break; // Exit the loop if Pac-Man is hit, as we don't need to check other ghosts
                }
            }
        }
    }
    else {
        for (const auto& ghost : ghosts) {
            int ghostDirection = ghost->move(*maze,*pacMan, deltaTime);
        }
    }
}

// Implement the method to check if all fruits are collected
void Game::checkWinCondition() {
    for (const auto& fruit : fruits) {
        if (fruit->isActive()) {
            return;  // If any fruit is still active, return early
        }
    }
    // If all fruits are collected, set gameWon to true
    gameWon = true;
    isRunning = false;  // Stop the game loop
}

// Getter for fruits, returns a vector of raw pointers
std::vector<Fruit*>& Game::getFruits() {
    static std::vector<Fruit*> fruitPtrs;
    fruitPtrs.clear();
    for (auto& fruit : fruits) {
        fruitPtrs.push_back(fruit.get());
    }
    return fruitPtrs;
}

// Similar implementations for power pellets, super pellets, and ghosts
std::vector<PowerPellet*>& Game::getPowerPellets() {
    static std::vector<PowerPellet*> pelletPtrs;
    pelletPtrs.clear();
    for (auto& pellet : powerPellets) {
        pelletPtrs.push_back(pellet.get());
    }
    return pelletPtrs;
}

std::vector<SuperPellet*>& Game::getSuperPellets() {
    static std::vector<SuperPellet*> superPelletPtrs;
    superPelletPtrs.clear();
    for (auto& superPellet : superPellets) {
        superPelletPtrs.push_back(superPellet.get());
    }
    return superPelletPtrs;
}

std::vector<Ghost*>& Game::getGhosts() {
    static std::vector<Ghost*> ghostPtrs;
    ghostPtrs.clear();
    for (auto& ghost : ghosts) {
        ghostPtrs.push_back(ghost.get());
    }
    return ghostPtrs;
}

// Getter for individual game objects
Maze* Game::getMaze() const {
    return maze.get();
}

PacMan* Game::getPacMan() const {
    return pacMan.get();
}

Screen* Game::getScreen() const {
    return screen.get();
}

Score* Game::getScore() const {
    return score.get();
}

Lives* Game::getPlayerLives() const {
    return playerLives.get();
}