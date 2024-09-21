#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
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
    void drawPacMan(const PacMan& pacman, int frame, int dir); // Draws Pac-Man at a specific location and frame
    void drawSuperPacMan(const PacMan& pacman, int frame, int dir);
    void drawFruits(const std::vector<Fruit>& fruits);
    void drawMaze(const Maze& maze);    // Draws the maze on the screen
    void drawGameImages(const Game& game); // Draws additional game images, like controls, on the screen
    bool endGame(const Score& score);
    bool winGame(const Score& score);
    void drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostDirection);
    void drawPowerPellets(const std::vector<PowerPellet>& powerPellet);
    void drawSuperPellets(const std::vector<SuperPellet>& superPellet);
    void drawStars(const std::vector<Star>& star);
    void drawKeys(const std::vector<GameKey>& keys);
    void drawScores(const Score& score);
    void symbols(int num1, int num2, int num3);
    Texture2D getTexture(int num);
    void drawLives(int lives);
    void setSymbolActive(bool status);

private:
    Maze* maze;            // Pointer to the maze
    Star* star;
    bool isRunning;        // State to check if the game is running
    int dir;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    void initializeGameObjects(); // Initializes game objects
    Texture2D ghostPicRight = LoadTexture("../resources/pacman-images/ghosty.png");
    Texture2D ghostPicLeft = LoadTexture("../resources/pacman-images/ghostyLeft.png");
    Texture2D ghostPicUp = LoadTexture("../resources/pacman-images/ghostyUp.png");
    Texture2D ghostPicDown = LoadTexture("../resources/pacman-images/ghostyDown.png");

     // Frightened ghost textures
    Texture2D ghostFrightenedRight = LoadTexture("../resources/pacman-images/GhostTA.png");
    Texture2D ghostFrightenedLeft = LoadTexture("../resources/pacman-images/GhostTA.png");
    Texture2D ghostFrightenedUp = LoadTexture("../resources/pacman-images/GhostTA.png");
    Texture2D ghostFrightenedDown = LoadTexture("../resources/pacman-images/GhostTA.png");

    // Flattened ghost textures
    Texture2D flattednedGhost = LoadTexture("../resources/pacman-images/GhostHigh.png");

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

    Texture2D picture;
    int num = 0;  

    bool eaten;
    bool symbolActive = false;
};

#endif // SCREEN_H


