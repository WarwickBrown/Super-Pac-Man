#include "Maze.h"
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

// Constructor
// Initializes the Maze object with default values for width, height, and starting position.
// Calls initialiseCustomWalls to set up the maze's outer walls.
Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    initialiseCustomWalls();  // Initialize a simple default maze for testing
}

// Destructor
// Since the walls vector manages its own memory, nothing special needs to be cleaned up here.
Maze::~Maze() {
    // Nothing to clean up for now as vector manages its own memory
}

// Initialize custom walls for the maze.
// This function adds outer boundary walls to the maze to enclose the gameplay area.
void Maze::initialiseCustomWalls() {
    // Outer walls
    walls.push_back(Rectangle{0, 0, 10, 900});     // Left wall
    walls.push_back(Rectangle{0, 0, 1600, 10});    // Top wall
    walls.push_back(Rectangle{1590, 0, 10, 900});  // Right wall
    walls.push_back(Rectangle{0, 890, 1600, 10});  // Bottom wall
}

// Checks if Pac-Man is colliding with any wall in the custom walls.
// Takes in Pac-Man's X, Y coordinates and his radius, and checks for collision with each wall.
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions.
    for (const auto& wall : walls) {
        // CheckCollisionCircleRec checks for collision between a circle (Pac-Man) and a rectangle (wall).
        if (CheckCollisionCircleRec({ static_cast<float>((pacmanX)), static_cast<float>((pacmanY)) }, pacmanRadius, wall)) {
            return true;  // Collision detected, return true.
        }
    }
    return false;  // No collision detected, return false.
}

// Checks if Pac-Man is colliding with a given rectangle (specified by the rectangle's coordinates).
// Takes in Pac-Man's X, Y coordinates and radius, as well as the rectangle to check against.
bool Maze::isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const {
    // Use Raylib's CheckCollisionCircleRec to detect a collision between Pac-Man and the rectangle.
    return CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, rect);
}

// Getter to access the walls vector.
// This allows other objects or functions to access the vector of walls in the maze.
const std::vector<Rectangle>& Maze::getWalls() const {
    return walls;
}

// Getter function that returns the maze width.
// Currently, this is not set explicitly in the constructor but could be useful for dynamic mazes.
int Maze::getWidth() const {
    return width;
}

// Getter function that returns the maze height.
// Like the width, the height is not currently set explicitly but could be used for future features.
int Maze::getHeight() const {
    return height;
}

// Getter function to return the starting X position of Pac-Man in the maze.
// This is initialized as `startX = 10` in the constructor.
int Maze::getStartX() const {
    return startX;
}

// Getter function to return the starting Y position of Pac-Man in the maze.
// This is initialized as `startY = 10` in the constructor.
int Maze::getStartY() const {
    return startY;
}
