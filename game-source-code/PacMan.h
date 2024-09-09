#ifndef PACMAN_H
#define PACMAN_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "Ghost.h"

// Forward declaration of the Ghost class
class Ghost;

class PacMan {
public:
    PacMan(int startX, int startY);  // Constructor
    ~PacMan();  // Destructor

    void move(const Maze& maze);  // Moves Pac-Man based on direction and checks for collisions
    void draw() const;  // Draws Pac-Man on the screen
    void setDirection(int dx, int dy);  // Sets the movement direction of Pac-Man
    bool checkCollision(const Maze& maze) const;  // Checks for collisions with the maze
    bool checkCollision(const Ghost& ghost) const;  // Checks for collisions with ghosts

    void becomeSuper();  // Changes Pac-Man's state to "Super"
    void resetSuper();  // Resets Pac-Man's state from "Super"
    bool isSuper() const;  // Returns whether Pac-Man is in "Super" mode

    int getX() const { return x; }
    int getY() const { return y; }


private:
    int x, y;  // Current position of Pac-Man
    int dx, dy;  // Direction of Pac-Man's movement
    int radius;  // Radius for drawing Pac-Man
    bool superState;  // Boolean flag to indicate if Pac-Man is in "Super" mode
    float superDuration;  // Duration for which Pac-Man remains in "Super" mode

    void handleMazeCollision(const Maze& maze);  // Handles collisions with the maze
};

#endif // PACMAN_H
