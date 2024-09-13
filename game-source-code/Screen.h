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
    Screen();  // Constructor
    ~Screen(); // Destructor

    void startScreen(const Game* game);
    void render();
    void drawPacMan(const PacMan& pacman, int frame, int dir);
    void drawMaze(const Maze& maze);
    void drawGameImages(const Game& game);
    bool endGame();

private:
    Maze* maze;  // Pointer to the maze
    bool isRunning;  // Game running state
    int dir;
    raylib::Window window;  // Game window
    void initializeGameObjects(); // Initializes game objects
    
};

#endif // SCREEN_H


