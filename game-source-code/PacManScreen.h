#ifndef PACMANSCREEN_H
#define PACMANSCREEN_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include <tuple>

// Forward declaration of Screen

class PacManScreen {
public:
    PacManScreen();  // Constructor
    ~PacManScreen();  // Destructor

    void draw(int frame, int pixelX, int pixelY, int dir);  // Draws Pac-Man on the screen

private:
    Maze* maze;  // Pointer to the maze
    bool isRunning;  // Game running state
    int dir;
    raylib::Window window;  // Game window
    Texture2D manLeft = LoadTexture("../resources/pacman-images/pacmenLeft.png");
    Texture2D manRight = LoadTexture("../resources/pacman-images/pacmenRight.png");
    Texture2D manUp = LoadTexture("../resources/pacman-images/pacmenUp.png");
    Texture2D manDown = LoadTexture("../resources/pacman-images/pacmenDown.png");
};

#endif // PACMAN_H
