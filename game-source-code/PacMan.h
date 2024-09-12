#ifndef PACMAN_H
#define PACMAN_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacManScreen.h"
#include <tuple>

// Forward declaration of Screen

class PacMan {
public:
    PacMan(int startX, int startY);  // Constructor
    ~PacMan();  // Destructor

    void move(const Maze& maze, float deltaTime, int dir);  // Moves Pac-Man based on direction and checks for collisions
    int location(int frame, int dir) const;  // Draws Pac-Man on the screen
    void setDirection(int dir);  // Sets the movement direction of Pac-Man
    bool checkCollision(const Maze& maze) const;  // Checks for collisions with the maze
    int getX() const { return x; }
    int getY() const { return y; }

private:
    Maze* maze;  // Pointer to the maze
    PacManScreen* screen;
    float x, y;  // Current position of Pac-Man
    float dx, dy;  // Direction of Pac-Man's movement
    int radius;  // Radius for drawing Pac-Man
    float speed;  // Movement speed in pixels per second
    float timeSinceLastMove;  // Timer to track movement updates
    Texture2D manLeft = LoadTexture("../resources/pacman-images/pacmenLeft.png");
    Texture2D manRight = LoadTexture("../resources/pacman-images/pacmenRight.png");
    Texture2D manUp = LoadTexture("../resources/pacman-images/pacmenUp.png");
    Texture2D manDown = LoadTexture("../resources/pacman-images/pacmenDown.png");
};

#endif // PACMAN_H
