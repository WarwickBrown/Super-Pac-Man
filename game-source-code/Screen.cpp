#include "Screen.h"
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Fruit.h"
#include "Score.h"
#include "Ghost.h"

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
void Screen::startScreen(const Game* game, const Screen* screen, const Score& score) {
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

    // Display high score
    std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());
    DrawText(highScoreText.c_str(),
             window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
             window.GetHeight() / 2 + 80, 30, WHITE);

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

// Function to draw Pac-Man at a specific location and frame, based on the current direction
void Screen::drawSuperPacMan(const PacMan& pacman, int frame, int dir) {
    // const std::vector<Texture2D>& pacManImages = pacman.getPacmanImages();  // Get textures for Pac-Man

    // // Convert Pac-Man's tile coordinates to pixel coordinates with a slight adjustment
    // double pixelX = pacman.getX() - 30;  // Adjust X position
    // double pixelY = pacman.getY() - 30;  // Adjust Y position

    // // Select the appropriate texture based on the direction Pac-Man is moving
    // Texture2D texture = pacManImages[0];  // Default texture is for moving left
    // if (dir == 1) { 
    //     texture = pacManImages[1];  // Texture for moving right
    // } else if (dir == 3) {
    //     texture = pacManImages[2];  // Texture for moving up
    // } else if (dir == 4) {
    //     texture = pacManImages[3];  // Texture for moving down
    // }

    // // Determine which part of the texture to draw (based on animation frame)
    // Rectangle sourceRec = {
    //     (float)(texture.width / 6) * frame,  // Calculate width of a single frame
    //     0, 
    //     (float)(texture.width / 6),          // Width of a single frame
    //     (float)(texture.height)              // Full height of the texture
    // };

    // // Draw Pac-Man's texture at the specified location and frame
    // DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
    float renderRadius = 50;
    DrawCircle(pacman.getX(), pacman.getY(), renderRadius, YELLOW);
}

// Function to draw additional images on the start screen (e.g., controls)
void Screen::drawGameImages(const Game& game) {
    const std::vector<Texture2D>& gameImages = game.getGameImages();  // Get game images
    // Draw the image in the center of the screen with some vertical adjustment
    DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 450, WHITE);
}

void Screen::drawMaze(const Maze& maze) {
    const std::vector<Wall>& walls = maze.getWalls();
    for (const auto& wall : walls) {
        if (wall.active) {
            DrawRectangleRec(wall.rect, wall.color);
        }
    }
}

void Screen::drawKeys(const std::vector<GameKey>& keys) {
    for (const auto& key : keys) {
        if (key.isActive()) {
            key.draw();
        }
    }
}


bool Screen::endGame(const Score& score) {  // Accept score as a parameter to display

    // Display the Game Over screen for ~3 seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {  // Show for ~3 seconds at 60 FPS
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("Game Over!", 
                 window.GetWidth() / 2 - MeasureText("Game Over!", 60) / 2, 
                 window.GetHeight() / 3, 60, RED);
        // Display player's score
        std::string scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        // Display high score
        std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

        window.EndDrawing();
    }

    // Close the window and exit the game properly
    CloseWindow();
    return false;  // Ensure the game loop stops
}

void Screen::drawGhost(const Ghost& ghost, int ghostDirection) {
    Texture2D currentTexture;
    
    // Check if the ghost is frightened, use the appropriate frightened texture
    if (ghost.isFrightened()) {
        switch (ghostDirection) {
            case 1: currentTexture = ghostFrightenedRight; break;  // Right
            case 2: currentTexture = ghostFrightenedLeft; break;   // Left
            case 3: currentTexture = ghostFrightenedUp; break;     // Up
            case 4: currentTexture = ghostFrightenedDown; break;   // Down
            default: currentTexture = ghostFrightenedRight; break; // Fallback texture
        }
    } else {
        // Normal state: use the normal ghost texture based on direction
        switch (ghostDirection) {
            case 1: currentTexture = ghostPicRight; break;  // Right
            case 2: currentTexture = ghostPicLeft; break;   // Left
            case 3: currentTexture = ghostPicUp; break;     // Up
            case 4: currentTexture = ghostPicDown; break;   // Down
            default: currentTexture = ghostPicRight; break; // Fallback texture
        }
    }
    Rectangle sourceRec = {
        (float)(currentTexture.width) ,  // Calculate width of a single frame
        0, 
        (float)(currentTexture.width),          // Width of a single frame
        (float)(currentTexture.height)              // Full height of the texture
    };

    // Draw Ghosts texture at the specified location and frame
    DrawTextureRec(currentTexture, sourceRec, Vector2{(float)ghost.getX()-35, (float)ghost.getY()-35}, RAYWHITE);
}

// Implement the "You Win!" screen
bool Screen::winGame(const Score& score) {

    // Display the "You Win!" screen for ~3 seconds or until player presses ENTER
    for (int i = 0; i < 1800; i++) {  // Show for ~3 seconds at 60 FPS
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        DrawText("You Win!", 
                 window.GetWidth() / 2 - MeasureText("You Win!", 60) / 2, 
                 window.GetHeight() / 3, 60, GREEN);

        // Display player's score
        std::string scoreText = "Your Score: " + std::to_string(score.getCurrentScore());
        DrawText(scoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(scoreText.c_str(), 30) / 2,
                window.GetHeight() / 2, 30, WHITE);

        // Display high score
        std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());
        DrawText(highScoreText.c_str(),
                window.GetWidth() / 2 - MeasureText(highScoreText.c_str(), 30) / 2,
                window.GetHeight() / 2 + 40, 30, WHITE);

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

void Screen::drawEdges()
{
   // DrawCircleSector({(float)180,(float)80}, 5, 270, 360, 50, PINK);
}

void Screen::symbols(int num1, int num2, int num3)
{
    if(symbolActive){
        Texture2D texture1;
        Texture2D texture2;
        Texture2D texture3;
        if(num1 == 1)
    {
        texture1 = symbol1;
    }
    else if(num1 == 2)
    {
        texture1 = symbol2;
    }
    else if(num1 == 3)
    {
        texture1 = symbol3;
    }
    else if(num1 == 4)
    {
        texture1 = symbol4;
    }
    else if(num1 == 5)
    {
        texture1 = symbol5;
    }
    else if(num1 == 6)
    {
        texture1 = symbol6;
    }
        if(num2 == 1)
    {
        texture2 = symbol1;
    }
    else if(num2 == 2)
    {
        texture2 = symbol2;
    }
    else if(num2 == 3)
    {
        texture2 = symbol3;
    }
    else if(num2 == 4)
    {
        texture2 = symbol4;
    }
    else if(num2 == 5)
    {
        texture2 = symbol5;
    }
    else if(num2 == 6)
    {
        texture2 = symbol6;
    }
    if(num3 == 1)
    {
        texture3 = symbol1;
    }
    else if(num3 == 2)
    {
        texture3 = symbol2;
    }
    else if(num3 == 3)
    {
        texture3 = symbol3;
    }
    else if(num3 == 4)
    {
        texture3 = symbol4;
    }
    else if(num3 == 5)
    {
        texture3 = symbol5;
    }
    else if(num3 == 6)
    {
        texture3 = symbol6;
    }
        Rectangle sourceRec1 = {
            (float)(texture1.width),  // Calculate width of a single frame
            0, 
            (float)(texture1.width),          // Width of a single frame
            (float)(texture1.height) 
        };
        Rectangle sourceRec2 = {
            (float)texture2.width,  // Calculate width of a single frame
            0, 
            (float)texture2.width,         // Width of a single frame
            (float)texture2.height
        };
        Rectangle sourceRec3 = {
            (float)texture3.width,  // Calculate width of a single frame
            0, 
            (float)texture3.width,         // Width of a single frame
            (float)texture3.height
        };
        // Draw Pac-Man's texture at the specified location and frame
        DrawTextureRec(texture1, sourceRec1, Vector2{650, 570}, RAYWHITE);
        DrawTextureRec(texture2, sourceRec2, Vector2{810, 570}, RAYWHITE);
        DrawTextureRec(texture3, sourceRec3, Vector2{730, 90}, RAYWHITE);
    }
}

void Screen::setSymbolActive(bool status){
    symbolActive = status;
}

void Screen::drawInner(){

    DrawRectangleRec(Rectangle{2, 82, 6, 806}, BLACK);     // Left wall
    DrawRectangleRec(Rectangle{2, 82, 1522, 6}, BLACK);    // Top wall
    DrawRectangleRec(Rectangle{1522, 82, 6, 806}, BLACK);  // Right wall
    DrawRectangleRec(Rectangle{2, 882, 1520, 6}, BLACK);  // Bottom wall

    //DrawRectangleRec(Rectangle{82, 802, 82, 6}, BLACK);   // Horizontal wall

    DrawRectangleRec({2, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({242, 802, 86, 6}, BLACK);   // Horizontal wall

    DrawRectangleRec({82, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({162, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({242, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({242, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({162, 162, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({162, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({322, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({322, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({322, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({482, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({402, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({482, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({562, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({402, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({482, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({402, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({322, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({82, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({802, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 802, 244, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 482, 242, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({802, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({802, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({882, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({962, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1042, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1122, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1202, 802, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1202, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1442, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1362, 802, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1362, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({962, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1042, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1122, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1122, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1202, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1282, 562, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1282, 402, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1202, 322, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1042, 482, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1122, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({82, 802, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1362, 242, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({1282, 162, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({962, 242, 86, 6}, BLACK);   // Horizontal wall

    // Vertical walls for more complexity
    DrawRectangleRec({162, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({242, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({82, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({82, 322, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({82, 82, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({162, 242, 6, 246}, BLACK);  // Vertical wall
    DrawRectangleRec({242, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({242, 82, 6, 244}, BLACK);  // Vertical wall
    DrawRectangleRec({322, 82, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({402, 82, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({402, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({562, 82, 6, 244}, BLACK);  // Vertical wall
    DrawRectangleRec({322, 482, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({562, 802, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({482, 642, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({562, 82, 6, 244}, BLACK);  // Vertical wall
    DrawRectangleRec({482, 402, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({562, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({402, 322, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({962, 802, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({562, 402, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({642, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({882, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({642, 402, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({882, 402, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({722, 242, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({802, 242, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({962, 402, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({962, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1122, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1042, 402, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({1442, 82, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({962, 82, 6, 244}, BLACK);  // Vertical wall
    DrawRectangleRec({1282, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1362, 722, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1282, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1042, 642, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({1122, 322, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1202, 482, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({1442, 562, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({1442, 322, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({1362, 242, 6, 246}, BLACK);  // Vertical wall
    DrawRectangleRec({1282, 82, 6, 244}, BLACK);  // Vertical wall
    DrawRectangleRec({1202, 82, 6, 166}, BLACK);  // Vertical wall
    DrawRectangleRec({1122, 82, 6, 86}, BLACK);  // Vertical wall
    DrawRectangleRec({722, 82, 86, 86}, BLACK);   // Block
    DrawRectangleRec({642, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({802, 722, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({722, 562, 6, 86}, BLACK);   // Vertical wall
    DrawRectangleRec({802, 562, 6, 86}, BLACK);   // Vertical wall
    DrawRectangleRec({642, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({802, 642, 86, 6}, BLACK);   // Horizontal wall
    DrawRectangleRec({642, 162, 6, 86}, BLACK);   // Vertical wall
    DrawRectangleRec({882, 162, 6, 86}, BLACK);   // Vertical wall
}
void Screen::drawScores(const Score& score) {
    // Convert scores to strings
    std::string currentScoreText = "Score: " + std::to_string(score.getCurrentScore());
    std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());

    // Option 1: Combine both texts into one line
    std::string combinedText = currentScoreText + "    " + highScoreText;

    // Set the new, larger font size
    int fontSize = 40;

    // Measure the width of the combined text
    int textWidth = MeasureText(combinedText.c_str(), fontSize);

    // Calculate x position to center the text
    int screenWidth = window.GetWidth();
    int xPosition = (screenWidth - textWidth) / 2;

    // Set y position at the top with some padding
    int yPosition = 20; // Adjust as needed

    // Draw the combined text
    DrawText(combinedText.c_str(), xPosition, yPosition, fontSize, WHITE);
}

void Screen::drawLives(int lives) {
    // Parameters for drawing the lives
    int radius = 15;                  // Radius of the life circles
    int spacing = 10;                 // Space between circles
    int totalLives = 3;               // Total number of lives
    int livesToDraw = std::min(lives, totalLives); // Ensure we don't draw more than total lives

    // Calculate the total width of the lives display
    int totalWidth = totalLives * (2 * radius) + (totalLives - 1) * spacing;

    // Starting position (top right of the screen)
    int xStart = window.GetWidth() - totalWidth - 20; // 20 pixels padding from the right edge
    int yPosition = 20;                               // 20 pixels padding from the top edge

    // Draw the lives
    for (int i = 0; i < livesToDraw; ++i) {
        int xPosition = xStart + i * ((2 * radius) + spacing);
        //DrawCircle(xPosition + radius, yPosition + radius, radius, RED);
        Rectangle sourceRec = {
            (float)symbolLives.width,  // Calculate width of a single frame
            0, 
            (float)symbolLives.width,         // Width of a single frame
            (float)symbolLives.height
        };
        // Draw Pac-Man's texture at the specified location and frame
        DrawTextureRec(symbolLives, sourceRec, Vector2{(float)(1365 + i*55), 20}, RAYWHITE);
    }
}