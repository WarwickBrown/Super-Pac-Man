/**
 * @file Draw.h
 * @brief Defines the Draw class used to handle all drawing-related functionality for the game.
 */

#include "Draw.h"
#include "PacMan.h"
#include "Game.h"
#include <raylib-cpp.hpp>

/**
 * @brief Default constructor for the Draw class.
 */
Draw::Draw() {}

/**
 * @brief Destructor for the Draw class.
 */
Draw::~Draw() {}

/**
 * @brief Draws Pac-Man at a specified location and frame based on his current direction.
 * 
 * @param pacman The Pac-Man object to be drawn.
 * @param frame The current animation frame of Pac-Man.
 * @param pacManDirection The direction Pac-Man is currently moving.
 */
void Draw::drawPacMan(const PacMan& pacman, int frame, Direction pacManDirection) {
    auto pixelX = pacman.getX() - 30;  // Adjust X position
    auto pixelY = pacman.getY() - 30;  // Adjust Y position

    Texture2D texture = pacManTextures[0];  // Default texture is for moving left
    switch(pacManDirection){
        case RIGHT: texture = pacManTextures[1]; break;
        case LEFT:  texture = pacManTextures[0]; break;
        case UP:    texture = pacManTextures[2]; break;
        case DOWN:  texture = pacManTextures[3]; break;
    }

    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

/**
 * @brief Draws Super Pac-Man at a specified location and frame based on his current direction.
 * 
 * @param pacman The Pac-Man object to be drawn.
 * @param frame The current animation frame of Pac-Man.
 * @param pacManDirection The direction Super Pac-Man is currently moving.
 */
void Draw::drawSuperPacMan(const PacMan& pacman, int frame, Direction pacManDirection) {
    auto pixelX = pacman.getX() - 50;  // Adjust X position
    auto pixelY = pacman.getY() - 50;  // Adjust Y position

    auto texture = pacManTexturesBig[0];  // Default texture is for moving left
    switch(pacManDirection){
        case RIGHT: texture = pacManTexturesBig[1]; break;
        case LEFT:  texture = pacManTexturesBig[0]; break;
        case UP:    texture = pacManTexturesBig[2]; break;
        case DOWN:  texture = pacManTexturesBig[3]; break;
    }

    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

/**
 * @brief Draws the maze by iterating through the walls in the maze.
 * 
 * @param maze The Maze object containing the walls to be drawn.
 */
void Draw::drawMaze(const Maze& maze) {
    const std::vector<Maze::Wall>& walls = maze.getWalls();
    for (const auto& wall : walls) {
        if (wall.active) {
            DrawRectangleRec(wall.rect, wall.color);
        }
    }
    for(const auto& wall : walls) {
        if (wall.color.r == PINK.r && wall.color.g == PINK.g && wall.color.b == PINK.b && wall.color.a == PINK.a) {
            Rectangle innerRect = {wall.rect.x + 2, wall.rect.y + 2, wall.rect.width - 4, wall.rect.height - 4};
            DrawRectangleRec(innerRect, BLACK);
        }
    }
}

/**
 * @brief Draws keys at their specified positions.
 * 
 * @param keys A vector of GameKey objects representing keys to be drawn.
 */
void Draw::drawKeys(const std::vector<GameKey>& keys) {
    for (const auto& key : keys) {
        if (key.isActive()) {
            DrawTexture(keyTexture, key.getX() - keyTexture.width / 2 + 7, key.getY() - keyTexture.height / 2 + 7, WHITE);
        }
    }
}

/**
 * @brief Draws power pellets at their specified positions.
 * 
 * @param powerPellets A vector of unique pointers to PowerPellet objects representing power pellets to be drawn.
 */
void Draw::drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets) {
    for (const auto& pellet : powerPellets) {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(powerPelletTexture.width), 0, (float)(powerPelletTexture.width), (float)(powerPelletTexture.height)};
            DrawTextureRec(powerPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

/**
 * @brief Draws a ghost at its specified position.
 * 
 * @param ghost The Ghost object to be drawn.
 * @param pacman The Pac-Man object used to determine if the ghost should be drawn in a frightened state.
 */
void Draw::drawGhost(const Ghost& ghost, const PacMan& pacman) {
    Texture2D currentTexture = ghostPicRight;
    if (ghost.isFrightened()) {
        currentTexture = ghostFrightenedRight;
    }
    else if (pacman.isSuper()) {
        currentTexture = ghostFlattenedTexture;
    }
    Rectangle sourceRec = {(float)(currentTexture.width), 0, (float)(currentTexture.width), (float)(currentTexture.height)};
    DrawTextureRec(currentTexture, sourceRec, Vector2{(float)ghost.getX()-35, (float)ghost.getY()-35}, RAYWHITE);
}
/**
 * @brief Draws fruit at their specified positions.
 * 
 * @param fruits A vector of unique pointers to Fruit objects representing fruits to be drawn.
 * @param num An integer representing the type of fruit texture to be used.
 */
void Draw::drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits, int num) {
    for (const auto& fruit : fruits) {
        Texture2D textures[3] = { getTexture(num) };
        if(fruit->isActive()) {
            for (int i = 0; i < 3; ++i) {
                Rectangle sourceRec = {(float)textures[i].width, 0, (float)textures[i].width, (float)textures[i].height};
                DrawTextureRec(textures[i], sourceRec, Vector2{(float)fruit->getX()-28, (float)fruit->getY()-28}, RAYWHITE);
            }
        }
    }
}

/**
 * @brief Draws symbols on the screen based on the provided texture numbers.
 * 
 * @param num1 The first symbol texture number.
 * @param num2 The second symbol texture number.
 */
void Draw::drawSymbols(int num1, int num2) {
    if (symbolActive) {
        Texture2D textures[3] = { getTexture(num1), getTexture(num2) };
        Vector2 positions[3] = { {650, 570}, {810, 570} };

        for (int i = 0; i < 3; ++i) {
            Rectangle sourceRec = {(float)textures[i].width, 0, (float)textures[i].width, (float)textures[i].height};
            DrawTextureRec(textures[i], sourceRec, positions[i], RAYWHITE);
        }
    }
}

/**
 * @brief Gets the texture based on the given number.
 * 
 * @param num The number representing the texture to be retrieved.
 * @return The Texture2D object corresponding to the given number.
 */
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

/**
 * @brief Sets the symbol's active status.
 * 
 * @param status A boolean value to set the symbol's active state.
 */
void Draw::setSymbolActive(bool status) {
    symbolActive = status;
}

/**
 * @brief Draws the current score and high score on the screen.
 * 
 * @param score The Score object containing the current and high scores.
 */
void Draw::drawScores(const Score& score) {
    auto currentScoreText = "Score: " + std::to_string(score.getCurrentScore());
    auto highScoreText = "High Score: " + std::to_string(score.getHighScore());
    auto combinedText = currentScoreText + "    " + highScoreText;
    auto fontSize = 40;
    auto textWidth = MeasureText(combinedText.c_str(), fontSize);
    auto DrawWidth = window.GetWidth();
    auto xPosition = (DrawWidth - textWidth) / 2;
    auto yPosition = 20;

    DrawText(combinedText.c_str(), xPosition, yPosition, fontSize, WHITE);
}

/**
 * @brief Draws the remaining lives on the screen.
 * 
 * @param lives The number of lives left to be drawn.
 */
void Draw::drawLives(int lives) {
    auto radius = 15;               
    auto spacing = 10;              
    auto totalLives = 3;            
    auto livesToDraw = std::min(lives, totalLives); 

    auto totalWidth = totalLives * (2 * radius) + (totalLives - 1) * spacing;
    auto xStart = window.GetWidth() - totalWidth - 20;
    auto yPosition = 20;

    for (auto i = 0; i < livesToDraw; ++i) {
        auto xPosition = xStart + i * ((2 * radius) + spacing);
        Rectangle sourceRec = {(float)symbolLives.width, 0, (float)symbolLives.width, (float)symbolLives.height};
        DrawTextureRec(symbolLives, sourceRec, Vector2{(float)(1365 + i*55), 20}, RAYWHITE);
    }
}

/**
 * @brief Draws the super pellets on the screen.
 * 
 * @param superPellets A vector of unique pointers to SuperPellet objects representing super pellets to be drawn.
 */
void Draw::drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets) {
    for(const auto& pellet : superPellets) {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(superPelletTexture.width), 0, (float)(superPelletTexture.width), (float)(superPelletTexture.height)};
            DrawTextureRec(superPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

/**
 * @brief Draws stars at their specified positions.
 * 
 * @param star A vector of unique pointers to Star objects representing stars to be drawn.
 */
void Draw::drawStars(std::vector<std::unique_ptr<Star>>& star) {
    for (const auto& eachStar : star) {
        if (eachStar->getChange()) {
            eachStar->setChange();
            picture = starTextures[num];
            num = (num + 1) % starTextures.size();
        }

        if (eachStar->isActive()) {
            Rectangle sourceRec = {(float)(picture.width), 0, (float)(picture.width), (float)(picture.height)};
            DrawTextureRec(picture, sourceRec, Vector2{(float)eachStar->getX() - 30, (float)eachStar->getY() - 32}, RAYWHITE);
        }
    }
}
