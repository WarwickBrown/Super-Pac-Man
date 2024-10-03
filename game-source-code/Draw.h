#ifndef Draw_H
#define Draw_H

#include <vector>
#include <raylib-cpp.hpp>
#include <memory>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Ghost.h"
#include "Fruit.h"
#include "GameKey.h"
#include "Score.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"
// Forward declaration of the Game class
class Game;

class Draw {
public:
    Draw();  // Constructor: Initialises the Draw/window and other variables
    ~Draw(); // Destructor: Cleans up dynamically allocated memory (if any)

    // Draw functions
    void drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits, int num);
    void drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostDirection);
    void drawKeys(const std::vector<GameKey>& keys);
    void drawLives(int lives);
    void drawMaze(const Maze& maze);    // Draws the maze on the Draw
    void drawPacMan(const PacMan& pacman, int frame, int dir); // Draws Pac-Man at a specific location and frame
    void drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets);
    void drawScores(const Score& score);
    void drawStars(std::vector<std::unique_ptr<Star>>& star);
    void drawSuperPacMan(const PacMan& pacman, int frame, int direction);
    void drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets);
    void drawSymbols(int num1, int num2);

    Texture2D getTexture(int num);
    void setSymbolActive(bool status);

    void DrawPixelatedGradient(int DrawWidth, int DrawHeight);  // Draws a pixelated gradient background
    Color InterpolateColor(Color start, Color end, float t);  // Interpolates between two colors based on 't'

private:
    std::unique_ptr<Maze> maze;
    int direction;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    int num = 0;  
    bool eaten;
    bool symbolActive = false;
    Texture2D picture;

    // PacMan Textures
    std::vector<Texture2D> pacManTextures = {
        LoadTexture("../resources/pacman-images/pacmenLeft.png"),
        LoadTexture("../resources/pacman-images/pacmenRight.png"),
        LoadTexture("../resources/pacman-images/pacmenUp.png"),
        LoadTexture("../resources/pacman-images/pacmenDown.png")
    };

     std::vector<Texture2D> pacManTexturesBig = {
        LoadTexture("../resources/pacman-images/pacmenLeftBig.png"),
        LoadTexture("../resources/pacman-images/pacmenRightBig.png"),
        LoadTexture("../resources/pacman-images/pacmenUpBig.png"),
        LoadTexture("../resources/pacman-images/pacmenDownBig.png")
    };

    // Ghost Textures
    Texture2D ghostPicRight = LoadTexture("../resources/pacman-images/ghosty.png");
    Texture2D ghostPicLeft = LoadTexture("../resources/pacman-images/ghostyLeft.png");
    Texture2D ghostPicUp = LoadTexture("../resources/pacman-images/ghostyUp.png");
    Texture2D ghostPicDown = LoadTexture("../resources/pacman-images/ghostyDown.png");

     // Frightened Ghost Textures
    Texture2D ghostFrightenedRight = LoadTexture("../resources/pacman-images/ghostyScared.png");
    Texture2D ghostFrightenedLeft = LoadTexture("../resources/pacman-images/ghostyScared.png");
    Texture2D ghostFrightenedUp = LoadTexture("../resources/pacman-images/ghostyScared.png");
    Texture2D ghostFrightenedDown = LoadTexture("../resources/pacman-images/ghostyScared.png");

    // Flattened ghost textures
    Texture2D flattednedGhost = LoadTexture("../resources/pacman-images/ghostyStreched.png");

    // Enlarged Pacman Texture
    Texture2D pacManBig = LoadTexture("../resources/pacman-images/GhostHigh.png");

    // Symbol textures
    Texture2D symbol1 = LoadTexture("../resources/pacman-images/symbol1.png");
    Texture2D symbol2 = LoadTexture("../resources/pacman-images/symbol2.png");
    Texture2D symbol3 = LoadTexture("../resources/pacman-images/symbol3.png");
    Texture2D symbol4 = LoadTexture("../resources/pacman-images/symbol4.png");
    Texture2D symbol5 = LoadTexture("../resources/pacman-images/symbol5.png");
    Texture2D symbol6 = LoadTexture("../resources/pacman-images/symbol6.png");
    Texture2D symbolLives = LoadTexture("../resources/pacman-images/livesSymbol.png");

    // Key Textures
    Texture2D keyTexture = LoadTexture("../resources/pacman-images/key.png");

    // Fruit Texture
    Texture2D fruitPic = LoadTexture("../resources/pacman-images/strawberry.png");

    // Power Pellet Texture
    Texture2D powerPelletTexture = LoadTexture("../resources/pacman-images/PowerPellet.png");

    // Super Pellet Texture
    Texture2D superPelletTexture = LoadTexture("../resources/pacman-images/SuperPellet.png");

    // Star Textures
    std::vector<Texture2D> starTextures = {
        LoadTexture("../resources/pacman-images/star1.png"),
        LoadTexture("../resources/pacman-images/star2.png"),
        LoadTexture("../resources/pacman-images/star3.png")
    };
};

#endif // Draw_H