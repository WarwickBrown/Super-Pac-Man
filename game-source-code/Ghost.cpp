#include "Ghost.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

// Constructor
Ghost::Ghost(int startX, int startY, float speed) : x(startX), y(startY), speed(100), radius(34), state(GhostState::Escaping) {
    // Initialize random seed
    std::srand(std::time(0));
    // Initialize random direction
    direction = rand() % 4 + 1; // Randomly set to 1 (right), 2 (left), 3 (up), or 4 (down)
}


// Move ghost based on current state
void Ghost::move(const Maze& maze, float deltaTime, const PacMan& pacman, GhostState newState) {
    // Update the state timers
    updateTimers(newState, deltaTime, maze);

    switch (state) {
        case GhostState::Escaping:
            escapeBox(maze, pacman);
            break;
        case GhostState::Chase:
            chase(maze, pacman);
            break;
        case GhostState::Scatter:
            scatter(maze);
            break;
        case GhostState::Frightened:
            frightened(maze);
            break;
    }

    // Calculate new position
    float newX = x;
    float newY = y;

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
}

int Ghost::getGhostDirection() const {
    return direction;
}

void Ghost::escapeBox(const Maze& maze, const PacMan& pacman) {
    // Define the boundary of the box (replace these with the actual coordinates of the box)
    int boxTop = 400;
    int boxBottom = 500;
    int boxLeft = 600;
    int boxRight = 800;

    // If the ghost is outside the box, set `inBox` to false
    if (x < boxLeft || x > boxRight || y < boxTop || y > boxBottom) {
        inBox = false;
        return; // Ghost has exited the box, no need to continue
    }

    // Simple logic to guide the ghost out
    if (!maze.isWall(x, y - speed, radius)) { // Try moving up
        direction = 3; // Move up
    } else if (!maze.isWall(x + speed, y, radius)) { // Try moving right
        direction = 1; // Move right
    } else if (!maze.isWall(x - speed, y, radius)) { // Try moving left
        direction = 2; // Move left
    } else if (!maze.isWall(x, y + speed, radius)) { // Try moving down
        direction = 4; // Move down
    }

    // Move the ghost in the chosen direction
    move(maze, GetFrameTime(), pacman, GhostState::Escaping); // Pass Escaping state
}


// Update all switchState calls in Ghost.cpp
void Ghost::updateTimers(GhostState newState, float deltaTime, const Maze& maze) {
    if (state == GhostState::Chase) {
        chaseTime -= deltaTime;
        if (chaseTime <= 0) {
            switchState(GhostState::Scatter, maze);  // Add 'maze' argument
        }
    } else if (state == GhostState::Scatter) {
        scatterTime -= deltaTime;
        if (scatterTime <= 0) {
            switchState(GhostState::Chase, maze);  // Add 'maze' argument
        }
    } else if (state == GhostState::Frightened) {
        frightenedTime -= deltaTime;
        if (frightenedTime <= 0) {
            switchState(GhostState::Chase, maze);  // Add 'maze' argument
        }
    }
}


// Switch the ghost's state
void Ghost::switchState(GhostState newState, const Maze& maze) {
    state = newState;

    if (state == GhostState::Chase) {
        chaseTime = 20.0f; // Set chase time duration
    } else if (state == GhostState::Scatter) {
        scatterTime = 7.0f; // Set scatter time duration
    } else if (state == GhostState::Frightened) {
        frightenedTime = 5.0f; // Set frightened time duration
        setRandomDirection(maze);
    }
}

// Chase Pac-Man
void Ghost::chase(const Maze& maze, const PacMan& pacman) {
    // Basic chase algorithm: move toward Pac-Man's current position
    if (pacman.getX() > x) {
        direction = 1; // Move right
    } else if (pacman.getX() < x) {
        direction = 2; // Move left
    } else if (pacman.getY() > y) {
        direction = 4; // Move down
    } else if (pacman.getY() < y) {
        direction = 3; // Move up
    }
    std::cout << "Ghost direction updated to: " << direction << std::endl;
}
// Scatter Mode: Move to a corner
void Ghost::scatter(const Maze& maze) {
    // Move towards a predefined corner (you can change the coordinates)
    if (x < 0) {
        direction = 1; // Move right
    } else if (x > maze.getWidth() - 1) {
        direction = 2; // Move left
    } else if (y < 0) {
        direction = 4; // Move down
    } else if (y > maze.getHeight() - 1) {
        direction = 3; // Move up
    }
}

// Frightened Mode: Move randomly
void Ghost::frightened(const Maze& maze) {
    // Move in a random direction
    setRandomDirection(maze);
}

// Set a random direction for the ghost
void Ghost::setRandomDirection(const Maze& maze) {
    std::vector<int> possibleDirections;

    if (!maze.isWall(x + speed, y, radius)) possibleDirections.push_back(1);  // Right
    if (!maze.isWall(x - speed, y, radius)) possibleDirections.push_back(2);  // Left
    if (!maze.isWall(x, y - speed, radius)) possibleDirections.push_back(3);  // Up
    if (!maze.isWall(x, y + speed, radius)) possibleDirections.push_back(4);  // Down

    if (!possibleDirections.empty()) {
        direction = possibleDirections[rand() % possibleDirections.size()];
    }
}

// Check collision with Pac-Man
bool Ghost::checkCollisionWithPacMan(const PacMan& pacman) {
    return CheckCollisionCircles({ x, y }, radius, { pacman.getX(), pacman.getY() }, pacman.getRadius());
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





// Getter for state
GhostState Ghost::getState() const {
    return state;
}