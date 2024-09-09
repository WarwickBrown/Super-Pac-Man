#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Ghost.h"

class Game {
public:
    Game();  // Constructor
    ~Game(); // Destructor

    void initialize();   // Initializes the game
    void run();          // Main game loop
    void handleInput();  // Handles user input
    void update();       // Updates game state
    void render();       // Renders game objects
    void checkCollisions(); // Checks for collisions between objects
    void endGame();      // Ends the game

private:
    Maze* maze;  // Pointer to the maze
    PacMan* pacMan;  // Pointer to Pac-Man
    std::vector<Ghost*> ghosts; // Vector of ghosts
    bool isRunning;  // Game running state
    raylib::Window window;  // Game window

    void initializeGameObjects(); // Initializes game objects
};

#endif // GAME_H
