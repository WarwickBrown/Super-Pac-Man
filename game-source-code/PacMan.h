#ifndef PACMAN_H
#define PACMAN_H

#include <raylib-cpp.hpp>
#include "Maze.h"
class PacMan {
public:
    enum Direction {
        RIGHT = 1,
        LEFT,
        UP,
        DOWN
    };
    PacMan(int startX, int startY);  // Constructor: Initialises Pac-Man's starting position
    ~PacMan();  // Destructor: Cleans up resources if necessary (not much needed here)

    // Sets Pac-Man's movement direction based on the input direction (e.g., left, right, etc.)
    void setDirection(Direction direction);

    // Determines and returns the current animation frame based on direction and frame time
    int location(int frame) const;

    // Moves Pac-Man based on the direction and delta time, and checks for collisions with the maze
    void move(const Maze& maze, float deltaTime, Direction direction);

    // Getters for Pac-Man's position, movement, radius, and speed
    float getX() const { return x; }
    float getY() const { return y; }
    float getVisualRadius() const { return visualRadius; }
    void setX(const float newX) {};  // Placeholder function for setting X (not used)
    void setY(const float newY) {};  // Placeholder function for setting Y (not used)
    int getDX() const { return dx; } // Returns Pac-Man's movement in the x direction
    int getDY() const { return dy; } // Returns Pac-Man's movement in the y direction
    int getFrames() const { return GetFrameTime(); }  // Returns frame time for Pac-Man animations
    int getRadius() const { return radius; }  // Returns Pac-Man's radius (for collision detection)
    int getSpeed() { return normalSpeed; }  // Returns Pac-Man's speed value
    bool isInvincible() const { return invincible; }
    bool isSuper() const { return superModeActive; }
    void setPosition(int newX, int newY);

    void setInvincible(bool invincible);
    void updateInvincibility(float deltaTime);

    void updateSuperMode(float deltaTime);
    void activateSuperMode();
    void deactivateSuperMode();

private:
    float x, y;  // Pac-Man's current position on the screen (x, y)
    float dx, dy;  // Direction of movement (change in x, change in y)
    int newDirection;
    int radius;  // Radius of Pac-Man (used for collision detection)
    float visualRadius;
    float normalSpeed;  // Movement speed of Pac-Man (pixels per second)
    float superSpeed;
    bool superModeActive;
    float superModeDuration;
    float superModeTimer;
    bool invincible;
    float invincibilityTime;
    float invincibilityDuration;
};

#endif // PACMAN_H