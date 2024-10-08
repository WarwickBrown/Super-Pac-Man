/**
 * @file Screen.cpp
 * @brief Implements the Screen class, which handles rendering and displaying different screens in the game.
 * 
 * This file defines the methods for displaying the start screen, game over screen, and win screen.
 * It manages drawing various game elements on the screen and handles window-related operations.
 */

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

/**
 * @brief Constructs a Screen object and initialises the game window.
 * 
 * Initialises the window with specified dimensions and title. Sets up the initial state of the game.
 */
Screen::Screen() 
    : window(1530, 890, "Super Pac-Man"),  ///< initialise window dimensions and title.
      isRunning(true)                      ///< Set initial game state to running.
{ 
    maze = std::make_unique<Maze>();       ///< Allocate memory for Maze object.
}

/**
 * @brief Destructor for the Screen class.
 * 
 * Cleans up any dynamically allocated memory or resources (if applicable).
 */
Screen::~Screen() {}

/**
 * @brief Displays the start screen with game instructions and high score.
 * 
 * This method displays the game title, instructions for starting the game, and high score information.
 * It waits for the player to press ENTER to begin the game.
 * 
 * @param score Reference to the Score object to display the high score.
 */
void Screen::startScreen(const Score& score, int frameNumber) {
    window.BeginDrawing();   ///< Start drawing the screen.
    
    Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber].width), 0, (float)(backgroundAnimation[frameNumber].width), (float)(backgroundAnimation[frameNumber].height)};
    DrawTextureRec(backgroundAnimation[frameNumber], sourceRec, Vector2{0, 0}, RAYWHITE);

    // Draw the title "Super Pac-Man" at the top in yellow with a shadow effect.
    DrawText("Super Pac-Man", 
         window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2 + 2,  // Shadow effect offset
         window.GetHeight() / 4 + 2 + 20, 70, Color{153, 153, 0, 255});  // Darker Yellow color
    DrawText("Super Pac-Man", 
            window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2, 
            window.GetHeight() / 4 + 20, 70, YELLOW);  // Main color

    // Draw instructions and high score with shadows and colors.
    DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2 + 2, 
            window.GetHeight() / 2 - 38 + 2, 40, DARKGREEN);  // Shadow color
    DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2, 
            window.GetHeight() / 2 - 38, 40, GREEN);  // Main color

    DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2 + 2, 
            window.GetHeight() / 2 + 10 + 2, 30, Color{139, 0, 0, 255});  // Shadow color
    DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2, 
            window.GetHeight() / 2 + 10, 30, RED);  // Main color

    DrawText("Use the ARROW KEYS to change direction", 
            window.GetWidth() / 2 - MeasureText("Use the ARROW KEYS to change direction", 25) / 2, 
            window.GetHeight() - 80, 25, LIGHTGRAY);

    auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
    DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2 + 2,
            window.GetHeight() / 2 + 80 + 2, 35, DARKPURPLE);  // Shadow color
    DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2,
            window.GetHeight() / 2 + 80, 35, PURPLE);  // Main color

    drawGameImages();  ///< Draw additional images on the start screen.

    window.EndDrawing();  ///< Finish drawing the screen.
}

/**
 * @brief Clears the screen and prepares it for rendering.
 * 
 * This method is used to reset the screen and draw a new frame, setting a black background.
 */
void Screen::render() {
    window.BeginDrawing();
    window.ClearBackground(BLACK);  ///< Clear the screen with a black background.
    window.EndDrawing();
}

/**
 * @brief Draws additional game images (e.g., controls) on the start screen.
 * 
 * This method displays controls and other images on the start screen, such as input keys.
 */
void Screen::drawGameImages() {
    DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 408, WHITE);
}

/**
 * @brief Displays the game over screen and waits for user input to exit.
 * 
 * This method displays the game over message, the player's score, and the high score. It waits
 * for a few seconds before closing the window and exiting the game.
 * 
 * @param score Reference to the Score object to display the current score and high score.
 * @param skipDelay Boolean that allows the function to skip the 3 second delay.
 * @return false Always returns false to ensure the game loop stops.
 */
bool Screen::endGame(const Score& score, bool skipDelay) {
    int frameNumber = 0;
    for (int i = 0; i < 3000; i++) {
        window.BeginDrawing();
        Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber/100].width), 0, (float)(backgroundAnimation[frameNumber/100].width), (float)(backgroundAnimation[frameNumber/100].height)};
        DrawTextureRec(backgroundAnimation[frameNumber/100], sourceRec, Vector2{0, 0}, RAYWHITE);

        DrawText("Game Over!", 
                window.GetWidth() / 2 - MeasureText("Game Over!", 60) / 2, 
                window.GetHeight() / 3, 60, RED);

        auto scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

        window.EndDrawing();
        frameNumber++;
            if(frameNumber == 1000)
            {
                frameNumber = 0;
            }
        if(skipDelay) break;
    }

    return false;  ///< Ensure the game loop stops.
}

/**
 * @brief Displays the win screen and waits for user input to exit.
 * 
 * This method displays the win message, the player's score, and the high score. It waits
 * for a few seconds before restarting the game.
 * 
 * @param score Reference to the Score object to display the current score and high score.
 * @param skipDelay Boolean that allows the function to skip the 3 second delay.
 * @return false Always returns false to ensure the game loop stops.
 */
bool Screen::winGame(const Score& score, bool skipDelay) {
    int frameNumber = 0;
    for (int i = 0; i < 5000; i++) {
        window.BeginDrawing();
        Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber/100].width), 0, (float)(backgroundAnimation[frameNumber/100].width), (float)(backgroundAnimation[frameNumber/100].height)};
        DrawTextureRec(backgroundAnimation[frameNumber/100], sourceRec, Vector2{0, 0}, RAYWHITE);

        DrawText("You Win!", 
                window.GetWidth() / 2 - MeasureText("You Win!", 60) / 2, 
                window.GetHeight() / 3, 60, GREEN);

        auto scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

        window.EndDrawing();
        frameNumber++;
            if(frameNumber == 1000)
            {
                frameNumber = 0;
            }
        if(skipDelay) break;
    }

    window.Close();  ///< Close the window when the game is won.
    return false;  ///< Ensure the game loop stops.
}
