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
    Screen();  // Constructor: Initialises the screen/window and other variables
    ~Screen(); // Destructor: Cleans up dynamically allocated memory (if any)

    // Functions for handling various Draw-related tasks
    void startScreen(const Game* game, const Score& score); // Displays the start Draw with game instructions
    void render(); // Clears the Draw and prepares it for rendering
    void drawGameImages(const Game& game); // Draws additional game images, like controls, on the screen

    bool endGame(const Score& score);
    bool winGame(const Score& score);


private:
    std::unique_ptr<Maze> maze;
    bool isRunning;        // State to check if the game is running
    int direction;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    int num = 0;  
    bool eaten;
    Texture2D picture;

    std::vector<Texture2D> gameImages = {
        LoadTexture("../resources/pacman-images/inputkeys.png"),
    };
};

#endif // Draw_H
