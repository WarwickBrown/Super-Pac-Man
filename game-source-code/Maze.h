/**
 * @file Maze.h
 * @brief Defines the Maze class, which represents the game environment and handles wall collisions.
 * 
 * The Maze class stores the structure of the game environment, including walls and their properties,
 * and provides methods to initialize and check collisions with the walls.
 */

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Reader.h"

/**
 * @class Maze
 * @brief Represents the maze structure in the game, including walls and collision detection.
 * 
 * The Maze class is responsible for managing the custom walls and collision detection within the game.
 * It reads wall data from a file and initializes the maze layout. It provides methods to check if Pac-Man
 * is colliding with any walls and to retrieve wall properties.
 */
class Maze : public Reader {
public:
    /**
     * @struct Wall
     * @brief Represents a single wall in the maze.
     * 
     * The Wall struct stores information about a rectangle-shaped wall, including its position, size,
     * active state, and color.
     */
    struct Wall {
        Rectangle rect;   ///< Rectangle defining the wall's position and dimensions.
        bool active;      ///< Indicates if the wall is currently active.
        Color color;      ///< The color of the wall.

        /**
         * @brief Constructs a Wall object with a given rectangle and color.
         * 
         * @param rect The rectangle representing the wall's position and size.
         * @param color The color of the wall.
         */
        Wall(const Rectangle& rect, Color color) : rect(rect), active(true), color(color) {}
    };

    /**
     * @brief Constructs a Maze object and initializes default values.
     * 
     * The constructor sets the default starting positions and initializes the maze's dimensions.
     */
    Maze();

    /**
     * @brief Destructor for the Maze class.
     * 
     * This destructor doesn't perform any specific actions but is defined for completeness.
     */
    ~Maze();

    /**
     * @brief Initializes custom walls in the maze by reading data from a file.
     * 
     * This method reads wall data from a file using the Reader class and sets up custom walls
     * with specific positions, sizes, and colors based on the file content.
     */
    void initialiseCustomWalls();

    /**
     * @brief Checks if Pac-Man is colliding with any of the walls in the maze.
     * 
     * @param pacmanX The x-coordinate of Pac-Man.
     * @param pacmanY The y-coordinate of Pac-Man.
     * @param pacmanRadius The radius of Pac-Man.
     * @return true if Pac-Man is colliding with any wall, false otherwise.
     */
    bool isWall(int pacmanX, int pacmanY, int pacmanRadius) const;

    /**
     * @brief Checks if Pac-Man's rectangular bounds are colliding with any of the walls in the maze.
     * 
     * @param pacmanX The x-coordinate of Pac-Man.
     * @param pacmanY The y-coordinate of Pac-Man.
     * @param pacmanRadius The radius of Pac-Man.
     * @return true if Pac-Man's rectangle is colliding with any wall, false otherwise.
     */
    bool isWallRec(int pacmanX, int pacmanY, int pacmanRadius) const;

    /**
     * @brief Gets a constant reference to the list of walls in the maze.
     * 
     * @return A constant reference to the vector of Wall objects.
     */
    const std::vector<Maze::Wall>& getWalls() const;

    /**
     * @brief Gets a reference to the list of walls in the maze.
     * 
     * @return A reference to the vector of Wall objects.
     */
    std::vector<Maze::Wall>& getWalls();

    /**
     * @brief Gets the height of the maze.
     * 
     * @return The height of the maze.
     */
    int getHeight() const { return height; }

    /**
     * @brief Gets the starting x-coordinate position of Pac-Man in the maze.
     * 
     * @return The starting x-coordinate of Pac-Man.
     */
    int getStartX() const { return startX; }

    /**
     * @brief Gets the starting y-coordinate position of Pac-Man in the maze.
     * 
     * @return The starting y-coordinate of Pac-Man.
     */
    int getStartY() const { return startY; }

private:
    std::vector<Wall> walls; ///< A vector containing all the walls in the maze.
    int width;               ///< Width of the maze.
    int height;              ///< Height of the maze.
    int startX, startY;      ///< Starting position for Pac-Man in the maze.
};

#endif // MAZE_H
