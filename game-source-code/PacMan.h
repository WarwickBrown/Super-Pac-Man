#ifndef PACMAN_H
#define PACMAN_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include <tuple>

// Forward declaration of Screen

class PacMan {
public:
    PacMan(int startX, int startY);  // Constructor: Initializes Pac-Man's starting position
    ~PacMan();  // Destructor: Cleans up resources if necessary (not much needed here)

    // Moves Pac-Man based on the direction and delta time, and checks for collisions with the maze
    void move(const Maze& maze, float deltaTime, int dir);  

    // Determines and returns the current animation frame based on direction and frame time
    int location(int frame, int dir) const;

    // Sets Pac-Man's movement direction based on the input direction (e.g., left, right, etc.)
    void setDirection(int dir);
    
    // bool checkCollision(const Maze& maze) const;  // Checks for collisions with the maze

    // Getters for Pac-Man's position, movement, radius, and speed
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(const float newX) {};  // Placeholder function for setting X (not used)
    void setY(const float newY) {};  // Placeholder function for setting Y (not used)
    int getDX() const { return dx; } // Returns Pac-Man's movement in the x direction
    int getDY() const { return dy; } // Returns Pac-Man's movement in the y direction
    int getFrames() const { return GetFrameTime(); }  // Returns frame time for Pac-Man animations
    int getRadius() const { return radius; }  // Returns Pac-Man's radius (for collision detection)
    const std::vector<Texture2D>& getPacmanImages() const;  // Returns the vector of Pac-Man textures
    int getSpeed() { return speed; }  // Returns Pac-Man's speed value
    void initilisePacManImages();  // Loads Pac-Man's textures for different movement directions
    bool isInvincible() const;
    void setInvincible(bool invincible);
    void updateInvincibility(float deltaTime);

private:
    std::vector<Texture2D> pacManImages;  // Holds Pac-Man's textures for different directions (left, right, up, down)
    float x, y;  // Pac-Man's current position on the screen (x, y)
    float dx, dy;  // Direction of movement (change in x, change in y)
    int newDirection;
    int radius;  // Radius of Pac-Man (used for collision detection)
    float speed;  // Movement speed of Pac-Man (pixels per second)
    bool invincible;
    float invincibilityTime;
    float invincibilityDuration;
};

#endif // PACMAN_H
