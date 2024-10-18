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

Screen::Screen() 
        : window(1530, 890, "Super Pac-Man"),  ///< initialise window dimensions and title.
        isRunning(true)                      ///< Set initial game state to running.
{ 
        maze = std::make_unique<Maze>();       ///< Allocate memory for Maze object.
}

Screen::~Screen() {}

void Screen::startScreen(const Score& score, int frameNumber) {
        window.BeginDrawing();   ///< Start drawing the screen.
    
        Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber].width), 0, (float)(backgroundAnimation[frameNumber].width), (float)(backgroundAnimation[frameNumber].height)};
        DrawTextureRec(backgroundAnimation[frameNumber], sourceRec, Vector2{0, 0}, RAYWHITE);

        // Draw the title "Super Pac-Man" at the top in yellow with a shadow effect.
        DrawText("Super Pac-Man", 
         window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2 + 2,  // Shadow effect offset
         window.GetHeight() / 4 + 2 + 20, 70, Color{153, 153, 0, 255});  // Darker Yellow colour
        DrawText("Super Pac-Man", 
            window.GetWidth() / 2 - MeasureText("Super Pac-Man", 70) / 2, 
            window.GetHeight() / 4 + 20, 70, YELLOW);  // Main colour

        // Draw instructions and high score with shadows and colours.
        DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2 + 2, 
            window.GetHeight() / 2 - 38 + 2, 40, DARKGREEN);  // Shadow colour
        DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 40) / 2, 
            window.GetHeight() / 2 - 38, 40, GREEN);  // Main colour

        DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2 + 2, 
            window.GetHeight() / 2 + 10 + 2, 30, Color{139, 0, 0, 255});  // Shadow colour
        DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 30) / 2, 
            window.GetHeight() / 2 + 10, 30, RED);  // Main colour

        DrawText("Use the ARROW KEYS to change direction", 
            window.GetWidth() / 2 - MeasureText("Use the ARROW KEYS to change direction", 25) / 2, 
            window.GetHeight() - 80, 25, WHITE);

        auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2 + 2,
            window.GetHeight() / 2 + 80 + 2, 35, DARKPURPLE);  // Shadow colour
        DrawText(highScoreText.c_str(),
            window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 35) / 2,
            window.GetHeight() / 2 + 80, 35, PURPLE);  // Main colour

        DrawText("Turn on Audio For Best Experience",
            window.GetWidth() / 2 - MeasureText("Turn on Audio For Best Experience", 20) / 2 - 560,
            window.GetHeight() / 2 + 410, 18, WHITE);  // Main colour

        drawGameImages();  ///< Draw additional images on the start screen.

        window.EndDrawing();  ///< Finish drawing the screen.
}

void Screen::render() {
        window.BeginDrawing();      
        window.ClearBackground(BLACK);  ///< Clear the screen with a black background.
        window.EndDrawing();
}

void Screen::drawGameImages() {
        DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 408, WHITE);
        DrawTexture(gameImages[2], 100, 700, WHITE);
}

bool Screen::endGame(const Score& score, bool skipDelay) {
        int frameNumber = 0;
        for (int i = 0; i < 1200; i++) {
        window.BeginDrawing();
        Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber/20].width), 0, (float)(backgroundAnimation[frameNumber/20].width), (float)(backgroundAnimation[frameNumber/20].height)};
        DrawTextureRec(backgroundAnimation[frameNumber/20], sourceRec, Vector2{0, 0}, RAYWHITE);

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
        if(frameNumber == 200)
        {
                frameNumber = 0;
        }
        if(skipDelay) break;
        }
        return false;  ///< Ensure the game loop stops.
}

bool Screen::winGame(const Score& score, bool skipDelay) {
        int frameNumber = 0;

        for (int i = 0; i < 1600; i++) {
        window.BeginDrawing();
        Rectangle sourceRec = {(float)(backgroundAnimation[frameNumber/20].width), 0, (float)(backgroundAnimation[frameNumber/20].width), (float)(backgroundAnimation[frameNumber/20].height)};
        DrawTextureRec(backgroundAnimation[frameNumber/20], sourceRec, Vector2{0, 0}, RAYWHITE);

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
        if(frameNumber == 200)
        {
                frameNumber = 0;
        }
        if(skipDelay) break;
        }
        window.Close();  ///< Close the window when the game is won.
        return false;  ///< Ensure the game loop stops.
}