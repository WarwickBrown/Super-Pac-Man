#include "Screen.h"

#include <raylib-cpp.hpp>
#include <iostream>


Screen::Screen() : window(1600, 900, "Super Pac-Man"), isRunning(true), maze(nullptr), dir(0){}

Screen::~Screen() {
    // Clean up dynamically allocated memory
    delete maze;
}

void Screen::startScreen()
{
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);
    DrawText("Press ENTER to Start", 200, 200, 20, BLACK);
    DrawText("Use the ARROW KEYS to change direction", 200, 230, 20, BLACK);
    DrawText("Press ESC to Exit", 200, 260, 20, BLACK);
    window.EndDrawing();
}

void Screen::render() {
    window.BeginDrawing();
    window.ClearBackground(BLACK);
    window.EndDrawing();
}

void Screen::drawPacMan(int frame, int pixelX, int pixelY, int dir){

}

void Screen::drawMaze() const {
    for (const auto& wall : maze->getWalls()) {
        DrawRectangleRec(wall, raylib::Color::DarkBlue());
    }
}

bool Screen::endGame() {
    // Display the Game Over screen
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);
    DrawText("Game Over!", window.GetWidth() / 2 - 100, window.GetHeight() / 2, 20, RED);
    window.EndDrawing();

    // Give some time for the player to see the Game Over screen
    // Use a timed delay or wait for a key press to exit
    for (int i = 0; i < 180; i++) {  // Show "Game Over" for ~3 seconds at 60 FPS
        window.BeginDrawing();
        window.ClearBackground(RAYWHITE);
        DrawText("Game Over!", window.GetWidth() / 2 - 100, window.GetHeight() / 2, 20, RED);
        window.EndDrawing();
        
        // Allow the player to exit early by pressing ESC or closing the window
        if (IsKeyPressed(KEY_ENTER) || window.ShouldClose()) {
            break;
        }
    }

    // Now close the window and exit the game properly
    CloseWindow();
    return false;  // Ensure the game loop stops
}