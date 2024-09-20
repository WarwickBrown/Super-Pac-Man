#include "Maze.h"
#include <fstream>
#include <iostream>
#include <string>
#include <raylib-cpp.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    struct WallData {
        Rectangle rect;
        Color color;
        int priority;

        // Comparator to sort by priority in descending order
        bool operator<(const WallData& other) const {
            return priority > other.priority;  // Sort descending by priority
        }
    };

    std::vector<WallData> wallDataList;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y, width, height;
        std::string colorString;
        int priority;
        
        // Read the rectangle coordinates, color, and priority
        if (!(iss >> x >> y >> width >> height >> colorString >> priority)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;  // Skip to next line if there's an error
        }
        
        // Determine the color based on the string
        Color color = PINK;  // Default to BLACK
        if (colorString == "BLACK") {
            color = BLACK;
        } else if (colorString == "BROWN") {
            color = BROWN;
        } else if (colorString == "PINK") {
            color = PINK;
        }
        // Add more colors as needed
        // Create a WallData object and store it in the list
        wallDataList.emplace_back(WallData{Rectangle{x, y, width, height}, color, priority});
    }

    // Close the file
    file.close();

    // Sort the walls based on priority (descending)
    std::sort(wallDataList.begin(), wallDataList.end());

    // Emplace sorted walls into the main wall vector
    for (const auto& wallData : wallDataList) {
        walls.emplace_back(wallData.rect, wallData.color);
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

// Checks if Pac-Man is colliding with a given rectangle (specified by the rectangle's coordinates).
// Takes in Pac-Man's X, Y coordinates and radius, as well as the rectangle to check against.
bool Maze::isCollidingWithRectangle(int pacmanX, int pacmanY, int pacmanRadius, const Rectangle& rect) const {
    // Use Raylib's CheckCollisionCircleRec to detect a collision between Pac-Man and the rectangle.
    return CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, rect);
}

const std::vector<Wall>& Maze::getWalls() const {
    return walls;
}

std::vector<Wall>& Maze::getWalls() {
    return walls;
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

