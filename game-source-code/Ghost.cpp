#include "Ghost.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <cmath>   // For abs()
#include <iostream>

// Constructor
Ghost::Ghost(int startX, int startY, float speed) : startX(startX), startY(startY), x(startX), y(startY), speed(250), radius(34), frightened(false), eaten(false) {
    // Initialize random seed
    std::srand(std::time(0));
    // Initialize random direction
    direction = rand() % 4 + 1; // Randomly set to 1 (right), 2 (left), 3 (up), or 4 (down)
}

// Destructor
Ghost::~Ghost() {
    // No dynamic memory to clean up in this class, but the definition is needed
}

void Ghost::respawn() {
    // Reset position to the starting point and set ghost to non-frightened and non-eaten state
    x = startX;
    y = startY;
    eaten = false;
    frightened = false;
}

bool Ghost::isEaten() const {
    return eaten;
}

void Ghost::setEaten(bool state) {
    eaten = state;
}

// Move ghost towards Pac-Man using similar movement logic as Pac-Man
int Ghost::move(const Maze& maze, const PacMan& pacman, float deltaTime) {
    if (eaten) {
        return direction; // Ghost stays in place if eaten
    }
    float currentTime = GetTime() - time;
    float newX = x;
    float newY = y;

    // --- Add logic for exiting the box at the start of the game ---
    // This block checks if the ghost is inside the starting box
    std::vector<int> possibleDirections;
    if(x < 870 && x > 650 && y > 366 && y < 446)
    {
         if (getX() > 765) {
            direction = 2;  // Move left toward the center
        } else if (getX() < 765) {
            direction = 1;  // Move right toward the center
        }
        else if (getX() == 765) {
            direction = 3;  // Move up to exit the box
        }
        switch (direction) {
            case 1: newX += speed * deltaTime; break;  // Move right
            case 2: newX -= speed * deltaTime; break;  // Move left
            case 3: newY -= speed * deltaTime; break;  // Move up (exit the box)
        }
        
        x = newX;
        y = newY;
      
    }
    else
    {
        // --- PAC-MAN's movement logic: continuous movement with directional locking ---
        // First, let's ensure the ghost maintains its current direction if it's not blocked.
        switch (direction) {
            case 1: newX += speed * deltaTime; break;  // Move right
            case 2: newX -= speed * deltaTime; break;  // Move left
            case 3: newY -= speed * deltaTime; break;  // Move up
            case 4: newY += speed * deltaTime; break;  // Move down
        }

        // Check if the new position hits a wall
        if (!maze.isWallRec(newX, newY, radius)) {
            // If no collision, the ghost can continue moving in the current direction
            x = newX;
            y = newY;
        } else {
            // If there is a wall, let's choose a new direction
            chooseNewDirection(maze);
        }

        // --- Add some randomness to movement to avoid ghosts moving in predictable patterns ---
        // Add randomness by occasionally overriding the calculated best movement
        // For example, 1 in 5 times the ghost will pick a random direction
        int randomChance = rand() % 5; // 1 in 5 chance
        if (randomChance == 0) {
            chooseRandomDirection(maze); // Pick a random valid direction
            return direction;
        }

        // --- GHOST'S chasing behavior ---
        // This section makes the ghost chase Pac-Man
        float deltaX = pacman.getX() - x;
        float deltaY = pacman.getY() - y;

        // Prioritize movement direction based on Pac-Man's position
        if (std::abs(deltaX) > std::abs(deltaY)) {
            // Try moving horizontally first (closer to Pac-Man)
            if (deltaX > 0 && !maze.isWallRec(x + speed * deltaTime, y, radius)) {
                setDirection(1);  // Move right
            } else if (deltaX < 0 && !maze.isWallRec(x - speed * deltaTime, y, radius)) {
                setDirection(2);  // Move left
            } else {
                // If horizontal movement is blocked, try vertical
                if (deltaY > 0 && !maze.isWallRec(x, y + speed * deltaTime, radius)) {
                    setDirection(4);  // Move down
                } else if (deltaY < 0 && !maze.isWallRec(x, y - speed * deltaTime, radius)) {
                    setDirection(3);  // Move up
                }
            }
        } else {
            // Try moving vertically first (closer to Pac-Man)
            if (deltaY > 0 && !maze.isWallRec(x, y + speed * deltaTime, radius)) {
                setDirection(4);  // Move down
            } else if (deltaY < 0 && !maze.isWallRec(x, y - speed * deltaTime, radius)) {
                setDirection(3);  // Move up
            } else {
                // If vertical movement is blocked, try horizontal
                if (deltaX > 0 && !maze.isWallRec(x + speed * deltaTime, y, radius)) {
                    setDirection(1);  // Move right
                } else if (deltaX < 0 && !maze.isWallRec(x - speed * deltaTime, y, radius)) {
                    setDirection(2);  // Move left
                }
            }
        }
    }
    return direction;
}

// Picks a random valid direction for the ghost to move
void Ghost::chooseRandomDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    // Check all four directions and add valid ones to the possible directions
    if (!maze.isWallRec(x + speed, y, radius)) possibleDirections.push_back(1);  // Right
    if (!maze.isWallRec(x - speed, y, radius)) possibleDirections.push_back(2);  // Left
    if (!maze.isWallRec(x, y - speed, radius)) possibleDirections.push_back(3);  // Up
    if (!maze.isWallRec(x, y + speed, radius)) possibleDirections.push_back(4);  // Down

    // Randomly pick a new valid direction if there are possible directions
    if (!possibleDirections.empty()) {
        direction = possibleDirections[rand() % possibleDirections.size()];
    }
}

// Chooses a new direction for the ghost when a collision occurs
void Ghost::chooseNewDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    // Check if the ghost can move in each direction (up, down, left, right)
    if (!maze.isWallRec(x + speed, y, radius)) possibleDirections.push_back(1);  // Right
    if (!maze.isWallRec(x - speed, y, radius)) possibleDirections.push_back(2);  // Left
    if (!maze.isWallRec(x, y - speed, radius)) possibleDirections.push_back(3);  // Up
    if (!maze.isWallRec(x, y + speed, radius)) possibleDirections.push_back(4);  // Down

    // Randomly pick a new valid direction if there are possible directions
    if (!possibleDirections.empty()) {
        direction = possibleDirections[rand() % possibleDirections.size()];
    }
}



// Simple chase behavior towards Pac-Man
void Ghost::chase(const PacMan& pacman) {
    if (!frightened) {
        // Calculate the differences in X and Y between the ghost and Pac-Man
        float deltaX = pacman.getX() - x;
        float deltaY = pacman.getY() - y;

        // Adjust both X and Y direction to move towards Pac-Man
        if (std::abs(deltaX) > std::abs(deltaY)) {
            // Move horizontally
            if (deltaX > 0) {
                setDirection(1); // Move right
            } else {
                setDirection(2); // Move left
            }
        } else {
            // Move vertically
            if (deltaY > 0) {
                setDirection(4); // Move down
            } else {
                setDirection(3); // Move up
            }
        }
    }
}

// Scatter behavior: Move to a random corner of the maze
void Ghost::scatter() {
    // Implement scatter logic, e.g., move to a random direction
    setDirection(rand() % 4 + 1); // Choose a random new direction (1 to 4)
}

// Check if the ghost is colliding with Pac-Man
bool Ghost::checkCollisionWithPacMan(const PacMan& pacman) const {
    if (eaten) {
        return false;
    }
    // Calculate the distance between the ghost and Pac-Man
    float distance = std::sqrt(std::pow(x - pacman.getX(), 2) + std::pow(y - pacman.getY(), 2));

    // Check if the distance is less than the sum of the radii (indicating a collision)
    return distance < (radius + pacman.getRadius());
}

// Set ghost to frightened state
void Ghost::setFrightened(bool state) {
    frightened = state;
}

void Ghost::setNormal() {
    frightened = false;
}

bool Ghost::isFrightened() const {
    return frightened;
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }
int Ghost::getRadius() const { return radius; }
int Ghost::getDirection() const { return direction; }
int Ghost::getDX() const { return dx; }
int Ghost::getDY() const { return dy; }
void Ghost::setDirection(int newDirection) { direction = newDirection; }
