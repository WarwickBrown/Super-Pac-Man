#include "Draw.h"
#include "PacMan.h"
#include "Game.h"

#include <raylib-cpp.hpp>

// Constructor for Draw class
Draw::Draw() {}

// Destructor for Draw class
Draw::~Draw() {}

// Function to draw Pac-Man at a specific location and frame, based on the current direction
void Draw::drawPacMan(const PacMan& pacman, int frame, Direction pacManDirection) {
    // Convert Pac-Man's tile coordinates to pixel coordinates with a slight adjustment
    auto pixelX = pacman.getX() - 30;  // Adjust X position
    auto pixelY = pacman.getY() - 30;  // Adjust Y position

    // Select the appropriate texture based on the direction Pac-Man is moving
    Texture2D texture = pacManTextures[0];  // Default texture is for moving left
    switch(pacManDirection){
        case RIGHT:
            texture = pacManTextures[1];  // Texture for moving right
            break;
        case LEFT:
            texture = pacManTextures[0];  // Texture for moving right
            break;
        case UP:
            texture = pacManTextures[2];  // Texture for moving right
            break;
        case DOWN:
            texture = pacManTextures[3];  // Texture for moving right
            break;
    }

    // Determine which part of the texture to draw (based on animation frame)
    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};

    // Draw Pac-Man's texture at the specified location and frame
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

// Function to draw Pac-Man at a specific location and frame, based on the current direction
void Draw::drawSuperPacMan(const PacMan& pacman, int frame, Direction pacManDirection) {
    auto renderRadius = 50;
    auto pixelX = pacman.getX() - 50;  // Adjust X position
    auto pixelY = pacman.getY() - 50;  // Adjust Y position

    // Select the appropriate texture based on the direction Pac-Man is moving
    auto texture = pacManTexturesBig[0];  // Default texture is for moving left
    switch(pacManDirection){
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
    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

// Function to draw the maze on the Draw
void Draw::drawMaze(const Maze& maze) {
    const std::vector<Maze::Wall>& walls = maze.getWalls();
    for (const auto& wall : walls) {
        if (wall.active) {
            DrawRectangleRec(wall.rect, wall.color);
        }
    }
    for(const auto& wall : walls) {
        if (wall.color.r == PINK.r && wall.color.g == PINK.g && wall.color.b == PINK.b && wall.color.a == PINK.a) {
                // Create the inner rectangle 2 pixels smaller in width and height
                Rectangle innerRect = {wall.rect.x + 2, wall.rect.y + 2, wall.rect.width - 4, wall.rect.height - 4};
                DrawRectangleRec(innerRect, BLACK);
            }
    }
}

void Draw::drawKeys(const std::vector<GameKey>& keys) {
    for (const auto& key : keys) {
        if (key.isActive()) {
            DrawTexture(keyTexture, key.getX() - keyTexture.width / 2 + 7, key.getY() - keyTexture.height / 2 + 7, WHITE);
        }
    }
}

void Draw::drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets) {
    for (const auto& pellet : powerPellets)
    {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(powerPelletTexture.width), 0, (float)(powerPelletTexture.width), (float)(powerPelletTexture.height)};
            DrawTextureRec(powerPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

void Draw::drawGhost(const Ghost& ghost, const PacMan& pacman) {
    Texture2D currentTexture;
    // Check if the ghost is frightened, use the appropriate frightened texture
    if(ghost.isFrightened()) {
        currentTexture = ghostFrightenedRight;
    } else if (pacman.isSuper()) {
        currentTexture = flattednedGhost;
    } else {
        currentTexture = ghostPicRight;
    }
    Rectangle sourceRec = {(float)(currentTexture.width), 0, (float)(currentTexture.width), (float)(currentTexture.height)};
    DrawTextureRec(currentTexture, sourceRec, Vector2{(float)ghost.getX()-35, (float)ghost.getY()-35}, RAYWHITE);
}

// Function to draw fruits on the Draw
void Draw::drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits, int num) {
    for (const auto& fruit : fruits) {
        Texture2D textures[3] = { getTexture(num) };
        if(fruit->isActive())
        {
            for (int i = 0; i < 3; ++i) {
            Rectangle sourceRec = {(float)textures[i].width, 0, (float)textures[i].width, (float)textures[i].height};
            DrawTextureRec(textures[i], sourceRec, Vector2{(float)fruit->getX()-28, (float)fruit->getY()-28}, RAYWHITE);
        }
        }
    }
}

void Draw::drawSymbols(int num1, int num2) {
    if (symbolActive) {
        Texture2D textures[3] = { getTexture(num1), getTexture(num2) };
        Vector2 positions[3] = { {650, 570}, {810, 570} };

        // Loop through each texture to draw it
        for (int i = 0; i < 3; ++i) {
            Rectangle sourceRec = {(float)textures[i].width, 0, (float)textures[i].width, (float)textures[i].height};
            DrawTextureRec(textures[i], sourceRec, positions[i], RAYWHITE);
        }
    }
}

auto Draw::getTexture(int num) -> Texture2D {
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

void Draw::setSymbolActive(bool status){
    symbolActive = status;
}

void Draw::drawScores(const Score& score) {
    // Convert scores to strings
    auto currentScoreText = "Score: " + std::to_string(score.getCurrentScore());
    auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
    auto combinedText = currentScoreText + "    " + highScoreText;

    // Set the new, larger font size
    auto fontSize = 40;

    // Measure the width of the combined text
    auto textWidth = MeasureText(combinedText.c_str(), fontSize);

    // Calculate x position to center the text
    auto DrawWidth = window.GetWidth();
    auto xPosition = (DrawWidth - textWidth) / 2;

    // Set y position at the top with some padding
    auto yPosition = 20; // Adjust as needed

    // Draw the combined text
    DrawText(combinedText.c_str(), xPosition, yPosition, fontSize, WHITE);
}

void Draw::drawLives(int lives) {
    // Parameters for drawing the lives
    auto radius = 15;                  // Radius of the life circles
    auto spacing = 10;                 // Space between circles
    auto totalLives = 3;               // Total number of lives
    auto livesToDraw = std::min(lives, totalLives); // Ensure we don't draw more than total lives

    // Calculate the total width of the lives display
    auto totalWidth = totalLives * (2 * radius) + (totalLives - 1) * spacing;

    // Starting position (top right of the Draw)
    auto xStart = window.GetWidth() - totalWidth - 20; // 20 pixels padding from the right edge
    auto yPosition = 20;                               // 20 pixels padding from the top edge

    // Draw the lives
    for (auto i = 0; i < livesToDraw; ++i) {
        auto xPosition = xStart + i * ((2 * radius) + spacing);
        Rectangle sourceRec = {(float)symbolLives.width, 0, (float)symbolLives.width, (float)symbolLives.height};
        DrawTextureRec(symbolLives, sourceRec, Vector2{(float)(1365 + i*55), 20}, RAYWHITE);
    }
}

void Draw::drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets) {
    for(const auto& pellet : superPellets)
    {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(superPelletTexture.width), 0, (float)(superPelletTexture.width), (float)(superPelletTexture.height)};
            DrawTextureRec(superPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

void Draw::drawStars(std::vector<std::unique_ptr<Star>>& star)
{
    for (const auto& eachStar : star) {
        if (eachStar->getChange()) {
            eachStar->setChange();  // Reset the change flag

            // Cycle through textures
            picture = starTextures[num];
            num = (num + 1) % starTextures.size();  // Loop through the textures
        }

        if (eachStar->isActive()) {
            Rectangle sourceRec = {(float)(picture.width), 0, (float)(picture.width), (float)(picture.height)};
            DrawTextureRec(picture, sourceRec, Vector2{(float)eachStar->getX() - 30, (float)eachStar->getY() - 32}, RAYWHITE);
        }
    }
}