/**
 * @file Ghost.cpp
 * @brief Implements the Ghost class, which represents a ghost character in the game.
 */

#include "Ghost.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>


/**
 * @brief Constructs a Ghost object with a specified starting position and speed.
 * 
 * @param startX The initial x-coordinate of the ghost.
 * @param startY The initial y-coordinate of the ghost.
 * @param speed The speed at which the ghost moves (pixels per second).
 * 
 * Initialises the ghost's state, including position, speed, and initial direction.
 */
Ghost::Ghost(int startX, int startY, float speed) : startX(startX), startY(startY), x(startX), y(startY), speed(250), radius(34), frightened(false), eaten(false) {
    // initialise random seed
    std::srand(std::time(0));
    // initialise random direction
    direction = rand() % 4 + 1; // Randomly set to 1 (right), 2 (left), 3 (up), or 4 (down)
}


/**
 * @brief Destructor for the Ghost class.
 * 
 * This destructor does not perform any specific actions but is defined for completeness.
 */
Ghost::~Ghost() {
    // No dynamic memory to clean up in this class, but the definition is needed
}

/**
 * @brief Resets the ghost's position and state to its initial values.
 * 
 * This method is used to respawn the ghost at its starting position and reset its state.
 */
void Ghost::respawn() {
    // Reset position to the starting point and set ghost to non-frightened and non-eaten state
    x = startX;
    y = startY;
    eaten = false;
    frightened = false;
}

/**
 * @brief Chooses a random valid direction for the ghost to move.
 * 
 * @param maze The maze object used to check for wall collisions.
 */
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

/**
 * @brief Moves the ghost based on its current direction and state.
 * 
 * @param maze The maze object used to check for wall collisions.
 * @param pacman The Pac-Man object used to determine chase behavior.
 * @param deltaTime The time elapsed since the last frame (for smooth movement).
 * @return The direction in which the ghost is moving.
 */
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
        // For example, 1 in 5 times the ghost will pick a random direction
        auto randomChance = rand() % 4; // 1 in 5 chance
        if (randomChance == 0) {
            chooseRandomDirection(maze); // Pick a random valid direction
            return direction;
        }
    }
    return direction;
}

/**
 * @brief Checks if the ghost collides with Pac-Man.
 * 
 * @param pacman The Pac-Man object to check for collisions.
 * @return true if the ghost collides with Pac-Man, false otherwise.
 */
bool Ghost::checkCollisionWithPacMan(const PacMan& pacman) const {
    if (eaten) {
        return false;
    }
    // Calculate the distance between the ghost and Pac-Man
    auto distance = std::sqrt(std::pow(x - pacman.getX(), 2) + std::pow(y - pacman.getY(), 2));

    // Check if the distance is less than the sum of the radii (indicating a collision)
    return distance < (radius + pacman.getRadius());
}

/**
 * @brief Chooses a new direction for the ghost when a collision occurs.
 * 
 * @param maze The maze object used to check for wall collisions.
 */
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

/**
 * @brief Handles the ghost's movement to escape the starting box.
 * 
 * @param direction The current direction of the ghost.
 * @param newX The new x-coordinate to move the ghost to.
 * @param newY The new y-coordinate to move the ghost to.
 * @param deltaTime The time elapsed since the last frame (for smooth movement).
 */
void Ghost::ghostEscapeBox(int direction, auto newX, auto newY, float deltaTime)
{
    if (getX() > 765) {
            direction = 2;  // Move left toward the center
    } else if (getX() < 765) {
            direction = 1;  // Move right toward the center
    } else if (getX() == 765) {
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

/**
 * @brief Handles the ghost's movement to chase Pac-Man.
 * 
 * @param direction The current direction of the ghost.
 * @param newX The new x-coordinate to move the ghost to.
 * @param newY The new y-coordinate to move the ghost to.
 * @param deltaTime The time elapsed since the last frame (for smooth movement).
 * @param maze The maze object used to check for wall collisions.
 * @param pacman The Pac-Man object used to determine chase behavior.
 */
void Ghost::ghostChasePacMan(int direction, auto newX, auto newY, float deltaTime, const Maze& maze, const PacMan& pacman)
{
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

    
    // This section makes the ghost chase Pac-Man
    auto deltaX = pacman.getX() - x;
    auto deltaY = pacman.getY() - y;

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