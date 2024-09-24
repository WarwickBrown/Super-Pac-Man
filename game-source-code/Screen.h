#ifndef SCREEN_H
#define SCREEN_H

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

class Screen {
public:
    Screen();  // Constructor: Initializes the screen/window and other variables
    ~Screen(); // Destructor: Cleans up dynamically allocated memory (if any)

    // Functions for handling various screen-related tasks
    void startScreen(const Game* game, const Screen* screen, const Score& score); // Displays the start screen with game instructions
    void render();                      // Clears the screen and prepares it for rendering
    
    bool endGame(const Score& score);
    bool winGame(const Score& score);

    void drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits);
    void drawGameImages(const Game& game); // Draws additional game images, like controls, on the screen
    void drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostDirection);
    void drawKeys(const std::vector<GameKey>& keys);
    void drawLives(int lives);
    void drawMaze(const Maze& maze);    // Draws the maze on the screen
    void drawPacMan(const PacMan& pacman, int frame, int dir); // Draws Pac-Man at a specific location and frame
    void drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets);
    void drawScores(const Score& score);
    void drawStars(std::vector<std::unique_ptr<Star>>& star);
    void drawSuperPacMan(const PacMan& pacman, int frame, int direction);
    void drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets);
    void drawSymbols(int num1, int num2, int num3);
    
    Texture2D getTexture(int num);
    void setSymbolActive(bool status);

private:
    std::unique_ptr<Maze> maze;
    bool isRunning;        // State to check if the game is running
    int direction;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    void initializeGameObjects(); // Initializes game objects

    std::vector<Texture2D> gameImages = {
        LoadTexture("../resources/pacman-images/inputkeys.png"),
    };

    // PacMan Textures
    std::vector<Texture2D> pacManTextures = {
        LoadTexture("../resources/pacman-images/pacmenLeftCopy.png"),
        LoadTexture("../resources/pacman-images/pacmenRightCopy.png"),
        LoadTexture("../resources/pacman-images/pacmenUpCopy.png"),
        LoadTexture("../resources/pacman-images/pacmenDownCopy.png")
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

    int num = 0;  
    bool eaten;
    bool symbolActive = false;
    Texture2D picture;
};

#endif // SCREEN_H


