#ifndef GHOST_H
#define GHOST_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"

class Ghost {
public:
    // Constructor: Initialises the ghost's starting position and speed
    Ghost(int startX, int startY, float speed);

    // Destructor
    ~Ghost();

    void respawn();  // New method to handle respawn logic
    void chooseRandomDirection(const Maze& maze);
    bool checkCollisionWithPacMan(const PacMan& pacman) const;
    void chooseNewDirection(const Maze& maze);     // Chooses a new direction when a collision occurs

    int move(const Maze& maze,const PacMan& pacman, float deltaTime);  // Moves the ghost based on direction

    // Getters for the ghost's position and radius
    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    int getDirection() const { return direction; }
    int getDX() const { return dx; }
    int getDY() const { return dy; }
    int getSpeed() const { return speed; }

    bool isEaten() const { return eaten; }
    void setEaten(bool state) { eaten = state; }


    // Method to set the ghost's direction
    void setDirection(int newDirection) { direction = newDirection; }

    // Ghost behavior methods
    bool isFrightened() const { return frightened; }
    void setFrightened(bool state) { frightened = state; }

    void setNormal() { frightened = false; }

private:
    float x, y;    // Current position of the ghost
    float dx, dy;  // Direction of the ghost's movement
    float speed;   // Movement speed in pixels per second
    int direction;
    int radius;
    bool frightened; // Whether the ghost is in a frightened state
    bool eaten;
    float startX, startY; // Starting position of the ghost (for respawn)
};

#endif // GHOST_H