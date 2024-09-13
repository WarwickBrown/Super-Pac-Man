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
    window.ClearBackground(BLACK);  // Set background to black for a Pac-Man-like feel

    // Draw the title (Super Pac-Man) in yellow at the top
    DrawText("Super Pac-Man", 
             window.GetWidth() / 2 - MeasureText("Super Pac-Man", 60) / 2, 
             window.GetHeight() / 4, 60, YELLOW);  // Title in Pac-Man yellow

    // Draw "Press ENTER to Start" below the title in white
    DrawText("Press ENTER to Start", 
             window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 30) / 2, 
             window.GetHeight() / 2 - 20, 30, GREEN);  // Main action prompt in white

    // Draw "Press ESC to Exit" below the start prompt in gray
    DrawText("Press ESC to Exit", 
             window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 20) / 2, 
             window.GetHeight() / 2 + 30, 20, RED);  // Exit instruction in gray

    // Draw the arrow key instructions at the bottom
    DrawText("Use the ARROW KEYS to change direction", 
             window.GetWidth() / 2 - MeasureText("Use the ARROW KEYS to change direction", 20) / 2, 
             window.GetHeight() - 50, 20, LIGHTGRAY);  // Arrow keys instruction

    // Background Animation: You could add subtle animations like moving dots or Pac-Man-style graphics to give the screen more energy.
    // Sound Effects or Music: Adding a looping retro game soundtrack or sound effect could enhance the arcade atmosphere.
    // Flashing Text: The "Press ENTER to Start" could flash or pulse to draw attention.
    // Game Logo or Visuals: If you want to add an extra visual element, you could include an image or graphic representing Pac-Man (like a simple circle with a mouth) near the title.
    // High Score Display: You could display high scores from previous sessions if that's a feature you plan to implement.

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
        DrawRectangleRec(wall, PINK);  // Draw each wall with a dark blue color
    }
}

bool Screen::endGame() {  // Accept score as a parameter to display
    // Display the Game Over screen
    window.BeginDrawing();
    window.ClearBackground(BLACK);

    // Center "Game Over!" text
    DrawText("Game Over!", 
             window.GetWidth() / 2 - MeasureText("Game Over!", 60) / 2, 
             window.GetHeight() / 3, 60, RED);  // Larger size for impact

    // Display player's score
    // std::string scoreText = "Your Score: " + std::to_string(score);
    // DrawText(scoreText.c_str(), 
    //          window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2, 
    //          window.GetHeight() / 2, 30, WHITE);  // Score below the "Game Over!" text

    // Instruction to exit the game
    // DrawText("Press ENTER to Exit", 
    //          window.GetWidth() / 2 - MeasureText("Press ENTER to Exit", 20) / 2, 
    //          window.GetHeight() - 100, 20, LIGHTGRAY);  // Instruction at the bottom

    window.EndDrawing();

    // Display the Game Over screen for ~3 seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {  // Show for ~3 seconds at 60 FPS
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("Game Over!", 
                 window.GetWidth() / 2 - MeasureText("Game Over!", 60) / 2, 
                 window.GetHeight() / 3, 60, RED);

        // DrawText(scoreText.c_str(), 
        //          window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2, 
        //          window.GetHeight() / 2, 30, WHITE);

        // DrawText("Press ENTER to Exit", 
        //          window.GetWidth() / 2 - MeasureText("Press ENTER to Exit", 20) / 2, 
        //          window.GetHeight() - 100, 20, LIGHTGRAY);

        window.EndDrawing();

        // Allow the player to exit early by pressing ENTER or closing the window
        // if (IsKeyPressed(KEY_ENTER) || window.ShouldClose()) {
        //     break;
        // }
    }

    // Close the window and exit the game properly
    CloseWindow();
    return false;  // Ensure the game loop stops
}
