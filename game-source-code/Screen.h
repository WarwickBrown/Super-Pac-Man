#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"

// Forward declaration of PacMan

class Screen {
public:
    Screen();  // Constructor
    ~Screen(); // Destructor

    void startScreen();
    void render();
    void drawPacMan(const PacMan& pacman, int frame, int dir);
    void drawMaze(const Maze& maze);
    bool endGame();

private:
    Maze* maze;  // Pointer to the maze
    bool isRunning;  // Game running state
    int dir;
    raylib::Window window;  // Game window
    void initializeGameObjects(); // Initializes game objects
    
};

#endif // SCREEN_H


