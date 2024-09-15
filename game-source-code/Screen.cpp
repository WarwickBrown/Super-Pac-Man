#include "Screen.h"
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Fruit.h"

#include <raylib-cpp.hpp>
#include <iostream>

// Constructor for Screen class
Screen::Screen() 
    : window(1530, 890, "Super Pac-Man"),  // Initialize window dimensions and title
      isRunning(true),                     // Set initial game state to running
      maze(nullptr),                       // Initialize maze pointer to nullptr
      dir(0)                               // Initialize direction to 0 (no direction)
{}

// Destructor for Screen class
Screen::~Screen() {
    // Clean up dynamically allocated memory for the maze
    delete maze;
}

// Function to display the start screen with game instructions
void Screen::startScreen(const Game* game) {
    window.BeginDrawing();   // Start drawing the screen
    window.ClearBackground(BLACK);  // Set background color to black

    // Draw the title "Super Pac-Man" at the top in yellow
    DrawText("Super Pac-Man", 
             window.GetWidth() / 2 - MeasureText("Super Pac-Man", 60) / 2,  // Center the text horizontally
             window.GetHeight() / 4, 60, YELLOW);  // Position text at 1/4th the window height

    // Draw "Press ENTER to Start" below the title in green
    DrawText("Press ENTER to Start", 
            window.GetWidth() / 2 - MeasureText("Press ENTER to Start", 30) / 2, 
            window.GetHeight() / 2 - 20, 30, GREEN);  

    // Draw "Press ESC to Exit" instruction in red
    DrawText("Press ESC to Exit", 
            window.GetWidth() / 2 - MeasureText("Press ESC to Exit", 20) / 2, 
            window.GetHeight() / 2 + 30, 20, RED);

    // Display arrow key instructions in light gray at the bottom of the screen
    DrawText("Use the ARROW KEYS to change direction", 
            window.GetWidth() / 2 - MeasureText("Use the ARROW KEYS to change direction", 20) / 2, 
            window.GetHeight() - 50, 20, LIGHTGRAY);

    // Draw any game images (e.g., controls) on the start screen
    drawGameImages(*game);

    window.EndDrawing();  // Finish drawing the screen
}

// Function to render the screen with a black background
void Screen::render() {
    window.BeginDrawing();
    window.ClearBackground(BLACK);  // Clear the screen with black background
    window.EndDrawing();
}

// Function to draw Pac-Man at a specific location and frame, based on the current direction
void Screen::drawPacMan(const PacMan& pacman, int frame, int dir) {
    const std::vector<Texture2D>& pacManImages = pacman.getPacmanImages();  // Get textures for Pac-Man

    // Convert Pac-Man's tile coordinates to pixel coordinates with a slight adjustment
    double pixelX = pacman.getX() - 30;  // Adjust X position
    double pixelY = pacman.getY() - 30;  // Adjust Y position

    // Select the appropriate texture based on the direction Pac-Man is moving
    Texture2D texture = pacManImages[0];  // Default texture is for moving left
    if (dir == 1) { 
        texture = pacManImages[1];  // Texture for moving right
    } else if (dir == 3) {
        texture = pacManImages[2];  // Texture for moving up
    } else if (dir == 4) {
        texture = pacManImages[3];  // Texture for moving down
    }

    // Determine which part of the texture to draw (based on animation frame)
    Rectangle sourceRec = {
        (float)(texture.width / 6) * frame,  // Calculate width of a single frame
        0, 
        (float)(texture.width / 6),          // Width of a single frame
        (float)(texture.height)              // Full height of the texture
    };

    // Draw Pac-Man's texture at the specified location and frame
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

// Function to draw additional images on the start screen (e.g., controls)
void Screen::drawGameImages(const Game& game) {
    const std::vector<Texture2D>& gameImages = game.getGameImages();  // Get game images
    // Draw the image in the center of the screen with some vertical adjustment
    DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 450, WHITE);
}

// Function to draw the maze on the screen
void Screen::drawMaze(const Maze& maze) {
    // Get the vector of rectangles representing maze walls
    const std::vector<Rectangle>& walls = maze.getWalls();

    // Draw each wall as a rectangle with a pink color
    for (const auto& wall : walls) {
        DrawRectangleRec(wall, PINK);  
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

void Screen::drawGhost(const Ghost& ghost) {
    Rectangle sourceRec = {
        (float)(ghostPic.width) ,  // Calculate width of a single frame
        0, 
        (float)(ghostPic.width),          // Width of a single frame
        (float)(ghostPic.height)              // Full height of the texture
    };

    // Draw Ghosts texture at the specified location and frame
    DrawTextureRec(ghostPic, sourceRec, Vector2{(float)ghost.getX()-31, (float)ghost.getY()-31}, RAYWHITE);
}

// Implement the "You Win!" screen
bool Screen::winGame() {
    // Display the "You Win!" screen
    window.BeginDrawing();
    window.ClearBackground(BLACK);

    // Center "You Win!" text
    DrawText("You Win!", 
             window.GetWidth() / 2 - MeasureText("You Win!", 60) / 2, 
             window.GetHeight() / 3, 60, GREEN);  // Use green color for the win message

    window.EndDrawing();

    // Display the "You Win!" screen for ~3 seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {  // Show for ~3 seconds at 60 FPS
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("You Win!", 
                 window.GetWidth() / 2 - MeasureText("You Win!", 60) / 2, 
                 window.GetHeight() / 3, 60, GREEN);

        window.EndDrawing();
    }

    // Close the window and exit the game properly
    CloseWindow();
    return false;  // Ensure the game loop stops
}

// Function to draw fruits on the screen
void Screen::drawFruits(const std::vector<Fruit>& fruits) {
    for (const auto& fruit : fruits) {
        if(!fruit.isEaten())
        {
            // Draw each fruit as a green circle
          //  DrawCircle(fruit.getX(), fruit.getY(), fruit.getRadius(), GREEN);
        }

    }
}