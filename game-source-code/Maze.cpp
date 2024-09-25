#include "Maze.h"
#include <fstream>
#include <raylib-cpp.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Constructor
Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    initialiseCustomWalls();  // Initialize a simple default maze for testing
}

// Destructor
Maze::~Maze() {
    // Nothing to clean up for now as vector manages its own memory
}

void Maze::initialiseCustomWalls() {
    // Create an instance of WallReader to read the wall file
    WallReader wallReader;
    wallReader.readFile();  // Read the file, storing lines into `data`

    // Get the data from WallReader
    const std::vector<std::string>& data = wallReader.getData();

    // Now, process each line from the `data` vector
    for (const auto& line : data) {
        std::istringstream iss(line);
        float x, y, width, height;
        std::string colourString;
        
        // Read the rectangle coordinates and color
        if (!(iss >> x >> y >> width >> height >> colourString)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;  // Skip to next line if there's an error
        }
        
        // Determine the color based on the string (assuming you have predefined constants)
        Color colour = BLACK;  // Default to BLACK if no match
        if (colourString == "BLACK") {
            colour = BLACK;
        } 
        else if (colourString == "BROWN") {
            colour = BROWN;
        } 
        else if (colourString == "PINK") {
            colour = PINK;
        }

        // Emplace the wall (Rectangle and color) into the `walls` vector
        walls.emplace_back(Rectangle{x, y, width, height}, colour);
    }
}
// Checks if Pac-Man is colliding with any wall in the custom walls.
// Takes in Pac-Man's X, Y coordinates and his radius, and checks for collision with each wall.
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    for (const auto& wall : walls) {
        if (wall.active && CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, wall.rect)) {
            //std::cout << "THE CIRCLE WALLS" << std::endl;
            return true;
        }
    }
    return false;
}

bool Maze::isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const {
    // Loop through all custom walls in the vector and check for collisions. 
    for (const auto& wall : walls) {
        
        // CheckCollisionCircleRec checks for collision between a circle (Pac-Man) and a rectangle (wall).
        if (wall.active && CheckCollisionRecs(Rectangle{(float)pacmanX-35, (float)pacmanY-35, 70, 70}, wall.rect)) {
            return true;  // Collision detected, return true.
            std::cout << "THE RECT WALLS" << std::endl;
        }
    }
    return false;  // No collision detected, return false.
}

const std::vector<Maze::Wall>& Maze::getWalls() const {
    return walls;
}

std::vector<Maze::Wall>& Maze::getWalls() {
    return walls;
}
