#include "Ghost.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// Constructor
Ghost::Ghost(int startX, int startY, float speed) : startX(startX), startY(startY), x(startX), y(startY), speed(100), radius(34), frightened(false), eaten(false) {
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
// Move ghost in a direction while avoiding walls
int Ghost::move(const Maze& maze, float deltaTime) {
    if (eaten) {
        // If eaten, don't move until respawn logic is handled
        return direction;
    }
    float newX = x;
    float newY = y;

    // Calculate the next position based on the current direction
    switch (direction) {
        case 1: newX += speed * deltaTime; break;  // Move right
        case 2: newX -= speed * deltaTime; break;  // Move left
        case 3: newY -= speed * deltaTime; break;  // Move up
        case 4: newY += speed * deltaTime; break;  // Move down
    }

    // Check if the new position collides with the maze walls
    if (maze.isWall(newX, newY, radius)) {
        // If a collision is detected, find a new direction
        chooseNewDirection(maze);
    } else {
        // If no collision, update the ghost's position
        x = newX;
        y = newY;
    }
    return direction;
}

// Chooses a new direction for the ghost when a collision occurs
void Ghost::chooseNewDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    // Check all four directions and add the valid ones to the possible directions list
    if (!maze.isWall(x + speed, y, radius)) possibleDirections.push_back(1);  // Right
    if (!maze.isWall(x - speed, y, radius)) possibleDirections.push_back(2);  // Left
    if (!maze.isWall(x, y - speed, radius)) possibleDirections.push_back(3);  // Up
    if (!maze.isWall(x, y + speed, radius)) possibleDirections.push_back(4);  // Down

    // If possible directions exist, choose one randomly
    if (!possibleDirections.empty()) {
        // Choose a random valid direction from possible directions
        int newDirection = possibleDirections[rand() % possibleDirections.size()];
        direction = newDirection;
    }
}

// Getters for ghost's current position and radius
int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }
int Ghost::getRadius() const { return radius; }

// Set the ghost's direction
void Ghost::setDirection(int newDirection) {
    direction = newDirection;
}

// Set ghost to frightened state
void Ghost::setFrightened(bool state) {
    frightened = state;
}

// Simple chase behavior towards Pac-Man
void Ghost::chase(const PacMan& pacman) {
    if (!frightened) {
        // Implement a simple chase logic towards Pac-Man's current position
        if (pacman.getX() > x) {
            setDirection(1); // Move right
        } else if (pacman.getX() < x) {
            setDirection(2); // Move left
        } else if (pacman.getY() > y) {
            setDirection(4); // Move down
        } else if (pacman.getY() < y) {
            setDirection(3); // Move up
        }
    }
}

// Scatter behavior: Move to a random corner of the maze
void Ghost::scatter() {
    // Implement scatter logic, e.g., move to a random direction
    setDirection(rand() % 4 + 1); // Choose a random new direction (1 to 4)
}


// Getter for the ghost's movement in X direction
int Ghost::getDX() const {
    return dx;
}

// Getter for the ghost's movement in Y direction
int Ghost::getDY() const {
    return dy;
}

int Ghost::getDirection() const {
    return direction;
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

void Ghost::setNormal() {
    frightened = false;
}

bool Ghost::isFrightened() const {
    return frightened;
}