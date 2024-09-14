#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"

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
    void drawMaze(const Maze& maze);    // Draws the maze on the screen
    void drawGameImages(const Game& game); // Draws additional game images, like controls, on the screen
    bool endGame();                     // Displays the end game screen and handles the end of the game

private:
    Maze* maze;            // Pointer to the maze
    bool isRunning;        // State to check if the game is running
    int dir;               // Current direction for Pac-Man's movement
    raylib::Window window; // Game window object for rendering
    
};

#endif // SCREEN_H


