#include "Maze.h"
#include <sstream>
#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>

Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    // Initialization
}

Maze::~Maze() {
    // Destructor
}

void Maze::initialiseCustomWalls() {
    // Create an instance of WallReader to read the wall file
    WallReader wallReader;
    wallReader.readFile();  // Read the file, storing lines into `data`

    // Get the data from WallReader
    const std::vector<std::string>& data = wallReader.getData();

    // Now, process each line from the data vector
    for (const auto& line : data) {
        std::istringstream iss(line);
        float x, y, width, height;
        std::string colourString;
        
        // Read the rectangle coordinates and color
        if (!(iss >> x >> y >> width >> height >> colourString)) {
            continue;  // Skip to next line if there's an error
        }
        
        // Determine the color based on the string
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

        // Emplace the wall (Rectangle and color) into the walls vector
        walls.emplace_back(Rectangle{x, y, width, height}, colour);
    }
}

bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    for (const auto& wall : walls) {
        if (wall.active && CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, wall.rect)) {
            return true;
        }
    }
    return false;
}

bool Maze::isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const {
    for (const auto& wall : walls) {
        if (wall.active && CheckCollisionRecs(Rectangle{(float)pacmanX - 35, (float)pacmanY - 35, 70, 70}, wall.rect)) {
            return true;
        }
    }
    return false;
}

const std::vector<Maze::Wall>& Maze::getWalls() const {
    return walls;
}

std::vector<Maze::Wall>& Maze::getWalls() {
    return walls;
}
