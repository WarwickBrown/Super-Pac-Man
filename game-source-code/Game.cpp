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
#include <raylib-cpp.hpp>
#include <cstdlib>
#include <cmath>
#include <memory>

/**
 * @brief Constructs a Game object, initialising the game window, running state, and other game elements.
 */
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), pacManDirection(NONE), frame(0), gameWon(false) {}

/**
 * @brief Destructor for the Game class, releasing dynamically allocated resources for the maze, Pac-Man, and other objects.
 */
Game::~Game() = default;

/**
 * @brief Initialises the game objects such as maze, Pac-Man, and various collectables.
 * 
 * This function uses the `GameInitialiser` class to set up the game objects, displays the start screen,
 * and waits for the player to start the game by pressing ENTER.
 */
void Game::initialise(bool skipStartScreen) {
    GameInitialiser::initialiseGameObjects(*this);  // Initialises game objects (maze, Pac-Man, screen, etc)

    if (!skipStartScreen) {
        int frameNumber = 0;
        
        while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
            screen->startScreen(*score, frameNumber/100);
            
            frameNumber++;
            if(frameNumber == 1000)
            {
                frameNumber = 0;
            }
        }
    }

    // Check if the window is closed by the user
    if (window.ShouldClose()) {
        isRunning = false;  // Stop running the game if the window is closed
    }
}

/**
 * @brief Main game loop that handles input, updates game state, and renders game elements.
 * 
 * This function contains the primary game loop, which continues until the game is won or the window is closed.
 * It renders all game elements such as the maze, Pac-Man, ghosts, collectables, and updates their states accordingly.
 */
void Game::run() {
    int pixelX, pixelY;                          // Coordinates for rendering
    srand(time(0));
    num3 = rand() % 6 + 1;                       // Randomise a number for drawing fruits

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
        draw->drawFruits(fruits, num3);          // Draw the fruits
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
            draw->drawSuperPacMan(*pacMan, frame, static_cast<Draw::Direction>(pacManOldDirection));
        } else {
            draw->drawPacMan(*pacMan, frame, static_cast<Draw::Direction>(pacManOldDirection));
        }

        // If the game has been won, break the loop
        if (gameWon) {
            break;
        }
    }

    // Save high score when the game ends
    score->saveHighScore();

    // If the game is won, show the win screen, otherwise show the end game screen
    if (gameWon) {
        isRunning = screen->winGame(*score);
    } else {
        isRunning = screen->endGame(*score);
    }
}

/**
 * @brief Handles user input for controlling Pac-Man's direction and other game controls.
 * 
 * @param inputKey The key input for controlling movement (optional).
 * 
 * This function checks for arrow key presses to update Pac-Man's direction and ESCAPE to exit the game.
 */
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
        break;
    }
}

/**
 * @brief Updates the state of the game elements, such as Pac-Man, ghosts, and collectables.
 * 
 * This function delegates the update logic to the `PacManManager` and `Update` classes and checks if the game has been won.
 */
void Game::update() {
    auto deltaTime = GetFrameTime();             // Get the time elapsed since the last frame

    // Delegate Pac-Man update logic to PacManManager
    pacManManager->updatePacMan(deltaTime);

    // Delegate remaining update logic to the Update class
    updater->updateGame(deltaTime);

    // Check win condition
    checkWinCondition();
}

/**
 * @brief Checks if all the fruits have been collected to determine if the game has been won.
 * 
 * If all fruits are collected, the game is marked as won, and the game loop is stopped.
 */
void Game::checkWinCondition() {
    for (const auto& fruit : fruits) {
        if (fruit->isActive()) {
            return;  // If any fruit is still active, return early
        }
    }
    gameWon = true;                              // If all fruits are collected, set gameWon to true
    isRunning = false;                           // Stop the game loop
}

/**
 * @brief Retrieves a list of fruit pointers for accessing and modifying fruit objects.
 * 
 * @return A vector of raw pointers to Fruit objects.
 */
std::vector<Fruit*>& Game::getFruits() {
    static std::vector<Fruit*> fruitPtrs;
    fruitPtrs.clear();
    for (auto& fruit : fruits) {
        fruitPtrs.push_back(fruit.get());
    }
    return fruitPtrs;
}

/**
 * @brief Retrieves a reference to the original vector of Star objects.
 * 
 * @return A reference to the vector of std::unique_ptr<Star> objects.
 */
std::vector<std::unique_ptr<Star>>& Game::getStarObjects() {
    return stars;  // Assuming `stars` is the original vector of unique_ptr<Star>
}

/**
 * @brief Retrieves a reference to the original vector of Fruit objects.
 * 
 * @return A reference to the vector of std::unique_ptr<Fruit> objects.
 */
std::vector<std::unique_ptr<Fruit>>& Game::getFruitObjects() {
    return fruits;  // Assuming `fruits` is the original vector of unique_ptr<Fruit>
}
