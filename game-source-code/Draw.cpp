/**
 * @file Draw.cpp
 * @brief Defines the Draw class used to handle all drawing-related functionality for the game.
 */

#include "Draw.h"
#include "PacMan.h"
#include "Game.h"
#include <raylib-cpp.hpp>

Draw::Draw() {}

Draw::~Draw() {}

void Draw::drawPacMan(const PacMan& pacman, int frame, PacMan::Direction pacManDirection) {
    auto pixelX = pacman.getX() - 30;  // Adjust X position
    auto pixelY = pacman.getY() - 30;  // Adjust Y position

    Texture2D texture = pacManTextures[0];  // Default texture is for moving left
    switch(pacManDirection){
        case PacMan::RIGHT: texture = pacManTextures[1]; break;
        case PacMan::LEFT:  texture = pacManTextures[0]; break;
        case PacMan::UP:    texture = pacManTextures[2]; break;
        case PacMan::DOWN:  texture = pacManTextures[3]; break;
    }

    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

void Draw::drawSuperPacMan(const PacMan& pacman, int frame, PacMan::Direction pacManDirection) {
    auto pixelX = pacman.getX() - 50;  // Adjust X position
    auto pixelY = pacman.getY() - 50;  // Adjust Y position

    auto texture = pacManTexturesBig[0];  // Default texture is for moving left
    switch(pacManDirection){
        case PacMan::RIGHT: texture = pacManTexturesBig[1]; break;
        case PacMan::LEFT:  texture = pacManTexturesBig[0]; break;
        case PacMan::UP:    texture = pacManTexturesBig[2]; break;
        case PacMan::DOWN:  texture = pacManTexturesBig[3]; break;
    }

    Rectangle sourceRec = {(float)(texture.width / 6) * frame, 0, (float)(texture.width / 6), (float)(texture.height)};
    DrawTextureRec(texture, sourceRec, Vector2{(float)pixelX, (float)pixelY}, RAYWHITE);
}

void Draw::drawMaze(const Maze& maze) {
    const std::vector<Maze::Wall>& walls = maze.getWalls();
    for (const auto& wall : walls) {
        if (wall.active) {
            DrawRectangleRec(wall.rect, wall.colour);
        }
    }
    for(const auto& wall : walls) {
        if (wall.colour.r == PINK.r && wall.colour.g == PINK.g && wall.colour.b == PINK.b && wall.colour.a == PINK.a) {
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
    for (const auto& pellet : powerPellets) {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(powerPelletTexture.width), 0, (float)(powerPelletTexture.width), (float)(powerPelletTexture.height)};
            DrawTextureRec(powerPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

void Draw::drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostNumber) {
    Texture2D currentTexture;
    switch(ghostNumber){
        case 1: 
            currentTexture = ghostPicRed;
            break;
        case 2: 
            currentTexture = ghostPicGreen;
            break;
        case 3: 
            currentTexture = ghostPicOrange;
            break;
    }
    if (ghost.isFrightened()) {
        currentTexture = ghostFrightenedRight;
    }
    else if (pacman.isSuper()) {
        switch(ghostNumber){
        case 1: 
            currentTexture = ghostFlattenedRed;
            break;
        case 2: 
            currentTexture = ghostFlattenedGreen;
            break;
        case 3: 
            currentTexture = ghostFlattenedOrange;
            break;
        }
    }
    Rectangle sourceRec = {(float)(currentTexture.width), 0, (float)(currentTexture.width), (float)(currentTexture.height)};
    DrawTextureRec(currentTexture, sourceRec, Vector2{(float)ghost.getX()-35, (float)ghost.getY()-35}, RAYWHITE);
}

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

void Draw::setSymbolActive(bool status) {
    symbolActive = status;
}

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

void Draw::drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets) {
    for(const auto& pellet : superPellets) {
        if (pellet->isActive()) {
            Rectangle sourceRec = {(float)(superPelletTexture.width), 0, (float)(superPelletTexture.width), (float)(superPelletTexture.height)};
            DrawTextureRec(superPelletTexture, sourceRec, Vector2{(float)pellet->getX()-25, (float)pellet->getY()-25}, RAYWHITE);
        }
    }
}

void Draw::drawStars(std::vector<std::unique_ptr<Star>>& star) {
    for (const auto& eachStar : star) {
        if (eachStar->getChange()) {
            eachStar->setChange();
            starTexture = starTextures[textureNumber];
            textureNumber = (textureNumber + 1) % starTextures.size();
        }

        if (eachStar->isActive()) {
            Rectangle sourceRec = {(float)(starTexture.width), 0, (float)(starTexture.width), (float)(starTexture.height)};
            DrawTextureRec(starTexture, sourceRec, Vector2{(float)eachStar->getX() - 30, (float)eachStar->getY() - 32}, RAYWHITE);
        }
    }
}