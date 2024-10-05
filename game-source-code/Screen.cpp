#include "Screen.h"
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Fruit.h"
#include "Score.h"
#include "Ghost.h"
#include "SuperPellet.h"
#include "Star.h"

#include <raylib-cpp.hpp>
#include <iostream>
#include <memory>

// Constructor for Screen class
Screen::Screen() 
    : window(1530, 890, "Super Pac-Man"),  // Initialise window dimensions and title
      isRunning(true)                      // Set initial game state to running
{ maze = std::make_unique<Maze>(); }

// Destructor for Screen class
Screen::~Screen() {
}

// Function to display the start screen with game instructions
void Screen::startScreen(const Game* game, const Screen* screen, const Score& score) {
    window.BeginDrawing();   // Start drawing the screen
    window.ClearBackground(BLACK);  // Set background color to black
    // Draw the title "Super Pac-Man" at the top in yellow with a shadow effect
    DrawText("Super Pac-Man", 
            window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2 + 2,  // Shadow effect offset
            window.GetHeight() / 4 + 2, 70, GRAY);  // Shadow color
    DrawText("Super Pac-Man", 
            window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2, 
            window.GetHeight() / 4, 70, YELLOW);  // Main color

    // Draw "Press ENTER to Start" below the title in green with an outline effect
    DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2 + 2, 
            window.GetHeight() / 2 - 18 + 2, 40, DARKGREEN);  // Shadow color
    DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2, 
            window.GetHeight() / 2 - 18, 40, GREEN);  // Main color

    // Draw "Press ESC to Exit" instruction in red with an outline effect
    DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2 + 2, 
            window.GetHeight() / 2 + 40 + 2, 30, RED);  // Shadow color
    DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2, 
            window.GetHeight() / 2 + 40, 30, RED);  // Main color

    // Display arrow key instructions in light gray at the bottom of the screen
    DrawText("Use the ARROW KEYS to change direction", 
            window.GetWidth() / 2 - MeasureText("Use the ARROW KEYS to change direction", 25) / 2, 
            window.GetHeight() - 60, 25, LIGHTGRAY);

    // Display high score in a more prominent way
    auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
    DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2 + 2,
            window.GetHeight() / 2 + 100 + 2, 35, DARKPURPLE);  // Shadow color
    DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2,
            window.GetHeight() / 2 + 100, 35, PURPLE);  // Main color


    drawGameImages(*game);


    window.EndDrawing();  // Finish drawing the screen
}

// Function to render the screen with a black background
void Screen::render() {
    window.BeginDrawing();
    window.ClearBackground(BLACK);  // Clear the screen with black background
    window.EndDrawing();
}

// Function to draw additional images on the start screen (e.g., controls)
void Screen::drawGameImages(const Game& game) {
    DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 450, WHITE);
}

bool Screen::endGame(const Score& score) {
    // Display the Game Over screen for a few seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("Game Over!", 
                window.GetWidth() / 2 - MeasureText("Game Over!", 60) / 2, 
                window.GetHeight() / 3, 60, RED);
        // Display player's score
        auto scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        // Display high score
        auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

        window.EndDrawing();
    }

    // Close the window and exit the game properly
    return false;  // Ensure the game loop stops
}

bool Screen::winGame(const Score& score) {

    // Display the "You Win!" screen for a few seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("You Win!", 
                window.GetWidth() / 2 - MeasureText("You Win!", 60) / 2, 
                window.GetHeight() / 3, 60, GREEN);

        // Display player's score
        auto scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        // Display high score
        auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

        window.EndDrawing();
    }

    window.Close();
    Game game;
    game.initialise();
    return false;  // Ensure the game loop stops
}

