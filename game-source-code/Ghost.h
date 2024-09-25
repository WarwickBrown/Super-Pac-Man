#ifndef GHOST_H
#define GHOST_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"

class Ghost {
public:
    // Constructor: Initializes the ghost's starting position and speed
    Ghost(int startX, int startY, float speed);

    // Destructor
    ~Ghost();

    int move(const Maze& maze,const PacMan& pacman, float deltaTime);  // Moves the ghost based on direction
    void chooseNewDirection(const Maze& maze);     // Chooses a new direction when a collision occurs
    void respawn();  // New method to handle respawn logic
    bool isEaten() const;
    void setEaten(bool eaten);

    bool checkCollisionWithPacMan(const PacMan& pacman) const;
    void chooseRandomDirection(const Maze& maze);


    // Method to set the ghost's direction
    void setDirection(int newDirection) { direction = newDirection; }

    // Getters for the ghost's position and radius
    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    int getDirection() const { return direction; }
    int getDX() const { return dx; }
    int getDY() const { return dy; }
    int getSpeed() const { return speed; }

    // Ghost behavior methods
    void setFrightened(bool state);  // Set the ghost to frightened mode
    void setNormal();  // Revert to normal mode
    void chase(const PacMan& pacman); // Simple chase behavior towards Pac-Man
    void scatter(); // Move to a random corner of the maze
    bool isFrightened() const;

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
