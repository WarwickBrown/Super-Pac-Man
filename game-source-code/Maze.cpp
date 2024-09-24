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
    // Path to the text file
    std::string filePath = "../resources/walls.txt";
    
    // Open the file
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y, width, height;
        std::string colorString;
        
        // Read the rectangle coordinates and color
        if (!(iss >> x >> y >> width >> height >> colorString)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;  // Skip to next line if there's an error
        }
        
        // Determine the color based on the string (assuming you have predefined constants)
        Color color = BLACK;  // Default to BLACK
        if (colorString == "BLACK") {
            color = BLACK;
        } 
        else if (colorString == "BROWN") {
            color = BROWN;
        } 
        else if (colorString == "PINK") {
            color = PINK;
        }

        // Emplace the wall into the vector
        walls.emplace_back(Rectangle{x, y, width, height}, color);
    }

    // Close the file
    file.close();
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
