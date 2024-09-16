#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Ghost.h"
#include "Fruit.h"

// Forward declaration of the Game class
class Game;

class Screen {
public:
    Screen();  // Constructor: Initializes the screen/window and other variables
    ~Screen(); // Destructor: Cleans up dynamically allocated memory (if any)

    // Functions for handling various screen-related tasks
    void startScreen(const Game* game); // Displays the start screen with game instructions
    void render();                      // Clears the screen and prepares it for rendering
    void drawPacMan(const PacMan& pacman, int frame, int dir); // Draws Pac-Man at a specific location and frame
    void drawFruits(const std::vector<Fruit>& fruits);
    void drawMaze(const Maze& maze);    // Draws the maze on the screen
    void drawGameImages(const Game& game); // Draws additional game images, like controls, on the screen
    bool endGame();                     // Displays the end game screen and handles the end of the game
    void drawGhost(const Ghost& ghost, int ghostDirection);
    bool winGame(); // Add a method to display the "You Win!" screen
    void drawEdges();
    void drawInner();

private:
    Maze* maze;            // Pointer to the maze
    bool isRunning;        // State to check if the game is running
    int dir;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    void initializeGameObjects(); // Initializes game objects
    Texture2D ghostPicRight = LoadTexture("../resources/pacman-images/ghosty.png");
    Texture2D ghostPicLeft = LoadTexture("../resources/pacman-images/ghostyLeft.png");
    Texture2D ghostPicUp = LoadTexture("../resources/pacman-images/ghostyUp.png");
    Texture2D ghostPicDown = LoadTexture("../resources/pacman-images/ghostyDown.png");
    bool eaten;
};

#endif // SCREEN_H


