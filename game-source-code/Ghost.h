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

    void move(const Maze& maze, float deltaTime);  // Moves the ghost based on direction
    void chooseNewDirection(const Maze& maze);     // Chooses a new direction when a collision occurs


    // Method to set the ghost's direction
    void setDirection(int direction);

    // Getters for the ghost's position and radius
    int getX() const;
    int getY() const;
    int getRadius() const;
    int getDX() const;
    int getDY() const;

    // Ghost behavior methods
    void setFrightened(bool state);
    void chase(const PacMan& pacman); // Simple chase behavior towards Pac-Man
    void scatter(); // Move to a random corner of the maze

private:
    float x, y;    // Current position of the ghost
    float dx, dy;  // Direction of the ghost's movement
    float speed;   // Movement speed in pixels per second
    int direction;
    int radius;
    bool frightened; // Whether the ghost is in a frightened state
};

#endif // GHOST_H
