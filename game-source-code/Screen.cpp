#include "Screen.h"
#include "Maze.h"
#include "PacMan.h"

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

// Function to draw Pac-Man at a specific location and frame
void Screen::drawPacMan(const PacMan& pacman, int frame, int dir) {
    const std::vector<Texture2D>& pacManImages = pacman.getPacmanImages();  // Get Pac-Man textures

    // Convert tile coordinates to pixel coordinates and apply some shift
    double pixelX = pacman.getX() - 39;  // Adjust this based on desired position
    double pixelY = pacman.getY() - 40;

    // Choose the appropriate texture based on the direction
    Texture2D texture = pacManImages[0];  // Default texture is manLeft
    if (dir == 1) { 
        texture = pacManImages[1];  // manRight
    } else if (dir == 3) {
        texture = pacManImages[2];  // manUp
    } else if (dir == 4) {
        texture = pacManImages[3];  // manDown
    }

    // Calculate which part of the texture to draw (based on frame)
    Rectangle sourceRec = {
        (float)(texture.width / 6) * frame,  // Frame width
        0, 
        (float)(texture.width / 6),          // Single frame width
        (float)(texture.height)              // Full height
    };

    // Draw the texture with the frame at the correct position
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

// Function to draw the maze walls on the screen
void Screen::drawMaze(const Maze& maze) {
    // Get the vector of wall rectangles from the maze
    const std::vector<Rectangle>& walls = maze.getWalls();

    // Iterate over each wall in the vector and draw it
    for (const auto& wall : walls) {
        DrawRectangleRec(wall, DARKBLUE);  // Draw each wall with a dark blue color
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
    for (int i = 0; i < 1800; i++) {  // Show "Game Over" for ~3 seconds at 60 FPS
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