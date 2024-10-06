/**
 * @file Maze.cpp
 * @brief Implements the Maze class, which represents the game environment and handles wall collisions.
 */

#include "Maze.h"
#include <sstream>
#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>

/**
 * @brief Constructs a Maze object and initialises default values.
 * 
 * Sets the default width and height of the maze to zero and the starting position of Pac-Man to (10, 10).
 */
Maze::Maze() : width(0), height(0), startX(10), startY(10) {
    // Initialization
}

/**
 * @brief Destructor for the Maze class.
 * 
 * This destructor does not perform any specific actions but is defined for completeness.
 */
Maze::~Maze() {}

/**
 * @brief initialises custom walls in the maze by reading data from a file.
 * 
 * This method uses the `Reader` class to read wall data from a file. Each line of the file
 * is parsed to create rectangle-shaped walls with specific positions, sizes, and colors,
 * which are then added to the maze.
 */
void Maze::initialiseCustomWalls() {
    Reader wallReader;           ///< Create an instance of WallReader to read the wall file.
    wallReader.readFile();       ///< Read the file, storing lines into `data`.

    const auto data = wallReader.getData();  ///< Get the data from WallReader.

    // Process each line from the data vector
    for (const auto& line : data) {
        std::istringstream iss(line);
        float x, y, width, height;
        std::string colourString;

        // Read the rectangle coordinates and color
        if (!(iss >> x >> y >> width >> height >> colourString)) {
            continue;  // Skip to next line if there's an error
        }

        // Determine the color based on the string
        auto colour = BLACK;  // Default to BLACK if no match
        if (colourString == "BLACK") {
            colour = BLACK;
        } else if (colourString == "BROWN") {
            colour = BROWN;
        } else if (colourString == "PINK") {
            colour = PINK;
        }

        // Emplace the wall (Rectangle and color) into the walls vector
        walls.emplace_back(Rectangle{x, y, width, height}, colour);
    }
}

/**
 * @brief Checks if Pac-Man is colliding with any of the walls in the maze.
 * 
 * @param pacmanX The x-coordinate of Pac-Man.
 * @param pacmanY The y-coordinate of Pac-Man.
 * @param pacmanRadius The radius of Pac-Man.
 * @return true if Pac-Man is colliding with any wall, false otherwise.
 */
bool Maze::isWall(int pacmanX, int pacmanY, int pacmanRadius) const {
    for (const auto& wall : walls) {
        if (wall.active && CheckCollisionCircleRec({ static_cast<float>(pacmanX), static_cast<float>(pacmanY) }, pacmanRadius, wall.rect)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if Pac-Man's rectangular bounds are colliding with any of the walls in the maze.
 * 
 * @param pacmanX The x-coordinate of Pac-Man.
 * @param pacmanY The y-coordinate of Pac-Man.
 * @param pacmanRadius The radius of Pac-Man.
 * @return true if Pac-Man's rectangle is colliding with any wall, false otherwise.
 */
bool Maze::isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const {
    for (const auto& wall : walls) {
        if (wall.active && CheckCollisionRecs(Rectangle{(float)pacmanX - 35, (float)pacmanY - 35, 70, 70}, wall.rect)) {
            return true;
        }
    }
    return false;
}
