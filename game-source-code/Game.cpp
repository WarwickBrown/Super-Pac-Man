/**
 * @file Game.cpp
 * @brief Implementation of the Game class, which manages the entire game flow and logic.
 */

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
#include "SoundManager.h"
#include <raylib-cpp.hpp>
#include <cstdlib>
#include <cmath>
#include <memory>

// Constructor - Initialises game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), pacManDirection(PacMan::NONE), frame(0), gameWon(false) {}

// Destructor - Frees dynamically allocated memory for maze, pacMan, and screen
Game::~Game() = default;

// Function to initialise the game
void Game::initialise(bool skipStartScreen) {
    GameInitialiser::initialiseGameObjects(*this);  // Initialises game objects (maze, Pac-Man, screen, etc)
    
    soundManager->playSound("start_screen_music");

    if (!skipStartScreen) {
        int frameNumber = 0;
        
        while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
            screen->startScreen(*score, frameNumber/20);
            
            frameNumber++;
            if(frameNumber == 200)
            {
                frameNumber = 0;
            }
        }
    }

    // Check if the window is closed by the user
    if (window.ShouldClose()) {
        isRunning = false;  // Stop running the game if the window is closed
    }
    soundManager->stopSound("start_screen_music");
}

// Main game loop
void Game::run() {
    int pixelX, pixelY;                          // Coordinates for rendering
    srand(time(0));
    fruitSymbolInMaze = rand() % 6 + 1;                       // Randomise a number for drawing fruits
    soundManager->playSound("gameplay_music");

    // Continue the game loop until the window is closed or the game stops running
    while (isRunning && !window.ShouldClose()) {
        int ghostNumber = 0;
        auto deltaTime = GetFrameTime();         // Get the time elapsed since the last frame
        handleInput(0);                          // Handle user input like key presses for movement
        update();                                // Update the game state
        screen->render();                        // Render the current state of the game

        draw->drawMaze(*maze);                   // Draw the maze
        draw->drawKeys(keys);                    // Draw the keys
        frame = pacMan->location(frame);         // Update Pac-Man's frame for animation
        draw->drawFruits(fruits, fruitSymbolInMaze);          // Draw the fruits
        draw->drawStars(stars);                  // Draw the stars
        draw->drawPowerPellets(powerPellets);    // Draw the power pellets
        draw->drawSuperPellets(superPellets);    // Draw the super pellets
        draw->drawScores(*score);                // Draw the scores
        draw->drawLives(playerLives->getLives());// Draw the player lives

        for (const auto& star : stars) {
            star->determineChange();             // Determine star state changes
        }

        for (const auto& ghost : ghosts) {
            ghostNumber++;
            draw->drawGhost(*ghost, *pacMan, ghostNumber);    // Draw each ghost
        }

        // Draw Pac-Man based on his current state (regular or super)
        if (pacMan->isSuper()) {
            draw->drawSuperPacMan(*pacMan, frame, static_cast<PacMan::Direction>(pacManOldDirection));
        } else {
            draw->drawPacMan(*pacMan, frame, static_cast<PacMan::Direction>(pacManOldDirection));
        }

        // If the game has been won, break the loop
        if (gameWon) {
            break;
        }
    }

    // Save high score when the game ends
    score->saveHighScore();
    soundManager->stopSound("gameplay_music");
    soundManager->stopSound("super_pellet");
    // If the game is won, show the win screen, otherwise show the end game screen
    if (gameWon) {
        soundManager->playSound("win_game");
        isRunning = screen->winGame(*score);
    } else {
        soundManager->playSound("lose_game");
        isRunning = screen->endGame(*score);
    }
}


// Handles user input for controlling Pac-Man's direction
void Game::handleInput(int inputKey) {
    if (inputKey == 0) {
        inputKey = GetKeyPressed();              // Get the key that was pressed
    }

    // Check if the ESCAPE key is pressed to exit the game
    if (inputKey == KEY_ESCAPE) {
        isRunning = false;                       // Stop the game loop
        return;
    }

    // Detect arrow key presses to update Pac-Man's direction
    switch (inputKey) {
    case KEY_RIGHT:
        pacManDirection = PacMan::RIGHT;
        break;
    case KEY_LEFT:
        pacManDirection = PacMan::LEFT;
        break;
    case KEY_UP:
        pacManDirection = PacMan::UP;
        break;
    case KEY_DOWN:
        pacManDirection = PacMan::DOWN;
        break;
    default:
        break;
    }
}

// Updates the game state (e.g., Pac-Man's position)
void Game::update() {
    auto deltaTime = GetFrameTime();             // Get the time elapsed since the last frame
    
    // Delegate Pac-Man update logic to PacManManager
    pacManManager->updatePacMan(deltaTime);

    // Delegate remaining update logic to the Update class
    updater->updateGame(deltaTime);

    // Check win condition
    checkWinCondition();
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

std::vector<Fruit*>& Game::getFruits() {
    static std::vector<Fruit*> fruitPtrs;
    fruitPtrs.clear();
    for (auto& fruit : fruits) {
        fruitPtrs.push_back(fruit.get());
    }
    return fruitPtrs;
}

std::vector<std::unique_ptr<Star>>& Game::getStarObjects() {
    return stars;  // Assuming `stars` is the original vector of unique_ptr<Star>
}

std::vector<std::unique_ptr<Fruit>>& Game::getFruitObjects() {
    return fruits;  // Assuming `fruits` is the original vector of unique_ptr<Fruit>
}