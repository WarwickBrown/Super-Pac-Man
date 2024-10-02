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
      isRunning(true),                     // Set initial game state to running
      direction(0)                         // Initialise direction to 0 (no direction)
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
    std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());
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

// Function to draw Pac-Man at a specific location and frame, based on the current direction
void Screen::drawPacMan(const PacMan& pacman, int frame, int direction) {
    // Convert Pac-Man's tile coordinates to pixel coordinates with a slight adjustment
    double pixelX = pacman.getX() - 30;  // Adjust X position
    double pixelY = pacman.getY() - 30;  // Adjust Y position

    // Select the appropriate texture based on the direction Pac-Man is moving
    Texture2D texture = pacManTextures[0];  // Default texture is for moving left
    switch(direction){
        case 1:
            texture = pacManTextures[1];  // Texture for moving right
            break;
        case 2:
            texture = pacManTextures[0];  // Texture for moving right
            break;
        case 3:
            texture = pacManTextures[2];  // Texture for moving right
            break;
        case 4:
            texture = pacManTextures[3];  // Texture for moving right
            break;
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
void Screen::drawSuperPacMan(const PacMan& pacman, int frame, int direction) {
    float renderRadius = 50;
    double pixelX = pacman.getX() - 50;  // Adjust X position
    double pixelY = pacman.getY() - 50;  // Adjust Y position

    // Select the appropriate texture based on the direction Pac-Man is moving
    Texture2D texture = pacManTexturesBig[0];  // Default texture is for moving left
    switch(direction){
        case 1:
            texture = pacManTexturesBig[1];  // Texture for moving right
            break;
        case 2:
            texture = pacManTexturesBig[0];  // Texture for moving right
            break;
        case 3:
            texture = pacManTexturesBig[2];  // Texture for moving right
            break;
        case 4:
            texture = pacManTexturesBig[3];  // Texture for moving right
            break;
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
    DrawTexture(gameImages[0], window.GetWidth() / 2 - gameImages[0].width / 2, 
                window.GetHeight() / 2 - gameImages[0].height + 450, WHITE);
}

// Function to draw the maze on the screen
void Screen::drawMaze(const Maze& maze) {
    const std::vector<Maze::Wall>& walls = maze.getWalls();
    for (const auto& wall : walls) {
        if (wall.active) {
            DrawRectangleRec(wall.rect, wall.color);
        }
    }
    for(const auto& wall : walls) {
        if (wall.color.r == PINK.r && wall.color.g == PINK.g && wall.color.b == PINK.b && wall.color.a == PINK.a) {
                // Create the inner rectangle 2 pixels smaller in width and height
                Rectangle innerRect = {
                    wall.rect.x + 2,       // Move 1 pixel right
                    wall.rect.y + 2,       // Move 1 pixel down
                    wall.rect.width - 4,   // Reduce width by 2 pixels
                    wall.rect.height - 4   // Reduce height by 2 pixels
                };
                // Draw the inner black rectangle
                DrawRectangleRec(innerRect, BLACK);
            }
    }
}

void Screen::drawKeys(const std::vector<GameKey>& keys) {
    for (const auto& key : keys) {
        if (key.isActive()) {
            DrawTexture(keyTexture, key.getX() - keyTexture.width / 2 + 7, key.getY() - keyTexture.height / 2 + 7, WHITE);
        }
    }
}

void Screen::drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets) {
    for (const auto& pellet : powerPellets)
    {
        if (pellet->isActive()) {
            Rectangle sourceRec = {
            (float)(powerPelletTexture.width) ,  // Calculate width of a single frame
            0, 
            (float)(powerPelletTexture.width),   // Width of a single frame
            (float)(powerPelletTexture.height)   // Full height of the texture
        };

        DrawTextureRec(powerPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
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
    return false;  // Ensure the game loop stops
}

void Screen::drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostDirection) {
    Texture2D currentTexture;
    
    // Check if the ghost is frightened, use the appropriate frightened texture
    if(ghost.isFrightened()) {
        switch (ghostDirection) {
            case 1: currentTexture = ghostFrightenedRight; break;  // Right
            case 2: currentTexture = ghostFrightenedLeft; break;   // Left
            case 3: currentTexture = ghostFrightenedUp; break;     // Up
            case 4: currentTexture = ghostFrightenedDown; break;   // Down
            default: currentTexture = ghostFrightenedRight; break; // Fallback texture
        }
    } else if (pacman.isSuper()) {
        switch (ghostDirection) {
            case 1: currentTexture = flattednedGhost; break;  // Right
            case 2: currentTexture = flattednedGhost; break;   // Left
            case 3: currentTexture = flattednedGhost; break;     // Up
            case 4: currentTexture = flattednedGhost; break;   // Down
            default: currentTexture = flattednedGhost; break; // Fallback texture
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
        (float)(currentTexture.width),   // Width of a single frame
        (float)(currentTexture.height)   // Full height of the texture
    };

    // Draw Ghosts texture at the specified location and frame
    DrawTextureRec(currentTexture, sourceRec, Vector2{(float)ghost.getX()-35, (float)ghost.getY()-35}, RAYWHITE);
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

    window.Close();
    Game game;
    game.initialise();
    return false;  // Ensure the game loop stops
}

// Function to draw fruits on the screen
void Screen::drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits, int num) {
    for (const auto& fruit : fruits) {
        Texture2D textures[3] = { getTexture(num) };
        if(fruit->isActive())
        {
            for (int i = 0; i < 3; ++i) {
            Rectangle sourceRec = {
                (float)textures[i].width,  // Calculate width of a single frame
                0,
                (float)textures[i].width,   // Width of a single frame
                (float)textures[i].height
            };

            // Draw Fruit texture at the specified location and frame
            DrawTextureRec(textures[i], sourceRec, Vector2{(float)fruit->getX()-28, (float)fruit->getY()-28}, RAYWHITE);
        }
        }
    }
}

void Screen::drawSymbols(int num1, int num2) {
    if (symbolActive) {
        Texture2D textures[3] = { getTexture(num1), getTexture(num2) };
        Vector2 positions[3] = { {650, 570}, {810, 570} };

        // Loop through each texture to draw it
        for (int i = 0; i < 3; ++i) {
            Rectangle sourceRec = {
                (float)textures[i].width,  // Calculate width of a single frame
                0,
                (float)textures[i].width,   // Width of a single frame
                (float)textures[i].height
            };

            // Draw the texture at the specified location
            DrawTextureRec(textures[i], sourceRec, positions[i], RAYWHITE);
        }
    }
}

Texture2D Screen::getTexture(int num) {
    switch(num) {
        case 1: return symbol1;
        case 2: return symbol2;
        case 3: return symbol3;
        case 4: return symbol4;
        case 5: return symbol5;
        case 6: return symbol6;
        default: return symbol1; 
    }
}

void Screen::setSymbolActive(bool status){
    symbolActive = status;
}

void Screen::drawScores(const Score& score) {
    // Convert scores to strings
    std::string currentScoreText = "Score: " + std::to_string(score.getCurrentScore());
    std::string highScoreText = "High Score: " + std::to_string(score.getHighScore());
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
            (float)symbolLives.width,  // Width of a single frame
            (float)symbolLives.height
        };
        // Draw Pac-Man's texture at the specified location and frame
        DrawTextureRec(symbolLives, sourceRec, Vector2{(float)(1365 + i*55), 20}, RAYWHITE);
    }
}

void Screen::drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets) {
    for(const auto& pellet : superPellets)
    {
        if (pellet->isActive()) {
            Rectangle sourceRec = {
            (float)(superPelletTexture.width) ,  // Calculate width of a single frame
            0, 
            (float)(superPelletTexture.width),   // Width of a single frame
            (float)(superPelletTexture.height)   // Full height of the texture
            };

            DrawTextureRec(superPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

void Screen::drawStars(std::vector<std::unique_ptr<Star>>& star)
{
    
    for (const auto& eachStar : star) {
        if (eachStar->getChange()) {
            eachStar->setChange();  // Reset the change flag

            // Cycle through textures
            picture = starTextures[num];
            num = (num + 1) % starTextures.size();  // Loop through the textures
        }

        if (eachStar->isActive()) {
            Rectangle sourceRec = {
                (float)(picture.width),  // Full width of the texture
                0, 
                (float)(picture.width),  // Width of a single frame
                (float)(picture.height)  // Full height of the texture
            };

            // Draw Star texture at the specified location
            DrawTextureRec(picture, sourceRec, Vector2{(float)eachStar->getX() - 30, (float)eachStar->getY() - 32}, RAYWHITE);
        }
    }
}