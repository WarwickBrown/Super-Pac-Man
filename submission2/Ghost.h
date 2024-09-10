#ifndef GHOST_H
#define GHOST_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"

// Forward declaration of the PacMan class
class PacMan;

// Enum to represent different ghost states
enum class GhostState {
    Normal,    // Ghost in normal chasing mode
    Frightened // Ghost in frightened mode
};

class Ghost {
public:
    Ghost(int startX, int startY);  // Constructor
    ~Ghost();  // Destructor

    void move(const Maze& maze, const PacMan& pacMan);  // Moves the ghost based on AI logic
    void draw() const;  // Draws the ghost on the screen
    bool checkCollision(const PacMan& pacMan) const;  // Checks for collisions with Pac-Man

    void becomeFrightened();  // Changes ghost state to frightened
    void resetState();  // Resets ghost state to normal
    bool isFrightened() const;  // Returns whether the ghost is in frightened mode

    int getX() const;  // Returns the ghost's current X position
    int getY() const;  // Returns the ghost's current Y position
    int getSize() const;  // Returns the size of the ghost for collision detection

    void setDirection(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
    }

private:
    int x, y;  // Current position of the ghost
    int dx, dy;  // Direction of the ghost's movement
    int size;  // Size of the ghost for drawing and collision purposes
    GhostState state;  // Current state of the ghost
    float frightenedDuration;  // Duration for which the ghost remains frightened

    void changeDirection(const Maze& maze);  // Changes the direction of the ghost randomly or based on AI
    void chasePacMan(const PacMan& pacMan);  // Logic to chase Pac-Man
    bool isWallAhead(const Maze& maze) const;  // Checks if there's a wall in the ghost's next position
};

#endif // GHOST_H
