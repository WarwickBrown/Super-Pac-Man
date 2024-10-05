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
#include <cstdlib>
#include <cmath>
#include <memory>

// Constructor - Initialises game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), pacManDirection(NONE), frame(0), gameWon(false) {}

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
    updater = std::make_unique<Update>(*this, draw.get());
    pacManManager = std::make_unique<PacManManager>(*this);
    maze->initialiseCustomWalls();
    pacMan->setDirection(PacMan::NONE);
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
    srand(time(0));
    num3 = rand()%6+1;
    // Continue the game loop until the window is closed or the game stops running
    while (isRunning && !window.ShouldClose()) {
        auto deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
        handleInput();   // Handle user input like key presses for movement
        update();
        screen->render(); // Render the current state of the game
        draw->drawMaze(*maze);  // Draw the maze
        draw->drawKeys(keys);
        frame = pacMan->location(frame);  // Update Pac-Man's frame for animation
        draw->drawFruits(fruits, num3);
        draw->drawStars(stars);
        draw->drawPowerPellets(powerPellets);
        draw->drawSuperPellets(superPellets);
        draw->drawScores(*score); // Draw the scores
        draw->drawLives(playerLives->getLives());

        for (const auto& star : stars) {
            star->determineChange();  // Use the star object directly
        }

        for (const auto& ghost : ghosts) {
            draw->drawGhost(*ghost, *pacMan);
        }

        if (pacMan->isSuper()) {
            draw->drawSuperPacMan(*pacMan, frame, static_cast<Draw::Direction>(pacManOldDirection));
        }
        else{
            draw->drawPacMan(*pacMan, frame, static_cast<Draw::Direction>(pacManOldDirection));  // Draw Pac-Man with its current frame and direction
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
        pacManDirection = RIGHT;
        break;
    case KEY_LEFT:
        pacManDirection = LEFT;
        break;
    case KEY_UP:
        pacManDirection = UP;
        break;
    case KEY_DOWN:
        pacManDirection = DOWN;
        break;
    default:
        // No direction change
        break;
    }
}

void Game::update() {
    auto deltaTime = GetFrameTime();  // Get the time elapsed since the last frame

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