/**
 * @file Ghost.cpp
 * @brief Implements the Ghost class, which represents a ghost character in the game.
 */

#include "Ghost.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>


// Constructor
Ghost::Ghost(int startX, int startY, float speed) : startX(startX), startY(startY), x(startX), y(startY), speed(250), radius(34), frightened(false), eaten(false) {
    // initialise random seed
    std::srand(std::time(0));
    // initialise random direction
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

// Picks a random valid direction for the ghost to move
void Ghost::chooseRandomDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    // Check all four directions and add valid ones to the possible directions
    if (!maze.isWallRec(x + speed, y, radius)) possibleDirections.push_back(RIGHT);
    if (!maze.isWallRec(x - speed, y, radius)) possibleDirections.push_back(LEFT);
    if (!maze.isWallRec(x, y - speed, radius)) possibleDirections.push_back(UP);
    if (!maze.isWallRec(x, y + speed, radius)) possibleDirections.push_back(DOWN);


    // Randomly pick a new valid direction if there are possible directions
    if (!possibleDirections.empty()) {
        direction = static_cast<Direction>(rand() % 4 + 1);  // Random direction: RIGHT, LEFT, UP, or DOWN
    }
}

// Move ghost towards Pac-Man using similar movement logic as Pac-Man
int Ghost::move(const Maze& maze, const PacMan& pacman, float deltaTime) {
    if (eaten) {
        return direction; // Ghost stays in place if eaten
    }
    auto newX = x;
    auto newY = y;

    // This block checks if the ghost is inside the starting box
    std::vector<int> possibleDirections;
    if(x < 870 && x > 650 && y > 366 && y < 446)
    {
        ghostEscapeBox(direction, newX, newY, deltaTime);
    }
    else
    {
        ghostChasePacMan(direction, newX, newY, deltaTime, maze, pacman);
        // Add randomness by occasionally overriding the calculated best movement
        // For example, 1 in 4 times the ghost will pick a random direction
        auto randomChance = rand() % 4; // 1 in 4 chance
        if (randomChance == 0) {
            chooseRandomDirection(maze); // Pick a random valid direction
            return direction;
        }
    }
    return direction;
}

// Check if the ghost is colliding with Pac-Man
bool Ghost::checkCollisionWithPacMan(const PacMan& pacman) const {
    if (eaten) {
        return false;
    }
    // Calculate the distance between the ghost and Pac-Man
    auto distance = std::sqrt(std::pow(x - pacman.getX(), 2) + std::pow(y - pacman.getY(), 2));

    // Check if the distance is less than the sum of the radii (indicating a collision)
    return distance < (radius + pacman.getRadius());
}

// Chooses a new direction for the ghost when a collision occurs
void Ghost::chooseNewDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    // Check if the ghost can move in each direction (up, down, left, right)
    if (!maze.isWallRec(x + speed, y, radius)) possibleDirections.push_back(RIGHT);  // Right
    if (!maze.isWallRec(x - speed, y, radius)) possibleDirections.push_back(LEFT);  // Left
    if (!maze.isWallRec(x, y - speed, radius)) possibleDirections.push_back(UP);  // Up
    if (!maze.isWallRec(x, y + speed, radius)) possibleDirections.push_back(DOWN);  // Down

    // Randomly pick a new valid direction if there are possible directions
    if (!possibleDirections.empty()) {
        direction = possibleDirections[rand() % possibleDirections.size()];
    }
}

void Ghost::ghostEscapeBox(int direction, auto newX, auto newY, float deltaTime)
{
    if (getX() > 765) {
            direction = LEFT;  // Move left toward the center
    } else if (getX() < 765) {
            direction = RIGHT;  // Move right toward the center
    } else if (getX() == 765) {
            direction = UP;  // Move up to exit the box
    }
    switch (direction) {
        case RIGHT: newX += speed * deltaTime; break;  // Move right
        case LEFT: newX -= speed * deltaTime; break;  // Move left
        case UP: newY -= speed * deltaTime; break;  // Move up (exit the box)
    }
    x = newX;
    y = newY;
}

void Ghost::ghostChasePacMan(int direction, auto newX, auto newY, float deltaTime, const Maze& maze, const PacMan& pacman)
{
    switch (direction) {
            case RIGHT: newX += speed * deltaTime; break;  // Move right
            case LEFT: newX -= speed * deltaTime; break;  // Move left
            case UP: newY -= speed * deltaTime; break;  // Move up
            case DOWN: newY += speed * deltaTime; break;  // Move down
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

    
    // This section makes the ghost chase Pac-Man
    auto deltaX = pacman.getX() - x;
    auto deltaY = pacman.getY() - y;

    // Prioritize movement direction based on Pac-Man's position
    if (std::abs(deltaX) > std::abs(deltaY)) {
        // Try moving horizontally first (closer to Pac-Man)
        if (deltaX > 0 && !maze.isWallRec(x + speed * deltaTime, y, radius)) {
        setDirection(RIGHT);  // Move right
        } else if (deltaX < 0 && !maze.isWallRec(x - speed * deltaTime, y, radius)) {
            setDirection(LEFT);  // Move left
        } else {
            // If horizontal movement is blocked, try vertical
            if (deltaY > 0 && !maze.isWallRec(x, y + speed * deltaTime, radius)) {
                setDirection(DOWN);  // Move down
            } else if (deltaY < 0 && !maze.isWallRec(x, y - speed * deltaTime, radius)) {
                setDirection(UP);  // Move up
            }
        }
    } else {
        // Try moving vertically first (closer to Pac-Man)
        if (deltaY > 0 && !maze.isWallRec(x, y + speed * deltaTime, radius)) {
            setDirection(DOWN);  // Move down
        } else if (deltaY < 0 && !maze.isWallRec(x, y - speed * deltaTime, radius)) {
            setDirection(UP);  // Move up
        } else {
            // If vertical movement is blocked, try horizontal
            if (deltaX > 0 && !maze.isWallRec(x + speed * deltaTime, y, radius)) {
                setDirection(RIGHT);  // Move right
            } else if (deltaX < 0 && !maze.isWallRec(x - speed * deltaTime, y, radius)) {
                setDirection(LEFT);  // Move left
            }
        }
    }
}