#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"

// Forward declaration of PacMan

class Screen {
public:
    Screen();  // Constructor
    ~Screen(); // Destructor

    void startScreen();
    void render();
    void drawPacMan(int frame, int pixelX, int pixelY, int dir);
    void drawMaze() const;
    bool endGame();

private:
    Maze* maze;  // Pointer to the maze
    bool isRunning;  // Game running state
    int dir;
    raylib::Window window;  // Game window

    void initializeGameObjects(); // Initializes game objects
};

#endif // SCREEN_H


