/**
 * @file Ghost.h
 * @brief Defines the Ghost class, which represents a ghost character in the game.
 * 
 * Ghosts are enemies in the game that interact with Pac-Man. They have different states,
 * can move in various directions, and can be frightened or eaten based on game events.
 */

#ifndef GHOST_H
#define GHOST_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"

/**
 * @class Ghost
 * @brief Represents a ghost character in the game with movement and collision logic.
 * 
 * The Ghost class handles all aspects of ghost behavior, including movement, direction changes,
 * and interactions with the Pac-Man character. Ghosts can chase Pac-Man, move randomly, or
 * respawn when they are eaten.
 */
class Ghost {
public:
    /**
     * @enum Direction
     * @brief Defines the possible movement directions for the ghost.
     */
    enum Direction {
        RIGHT = 1, ///< Moving right.
        LEFT,      ///< Moving left.
        UP,        ///< Moving up.
        DOWN       ///< Moving down.
    };

    /**
     * @brief Constructs a Ghost object with a specified starting position and speed.
     * 
     * @param startX The initial x-coordinate of the ghost.
     * @param startY The initial y-coordinate of the ghost.
     * @param speed The speed at which the ghost moves (pixels per second).
     */
    Ghost(int startX, int startY, float speed);

    /**
     * @brief Destructor for the Ghost class.
     * 
     * This destructor does not perform any specific actions but is defined for completeness.
     */
    ~Ghost();
    /**
     * @brief Resets the ghost's position and state to its initial values.
     * 
     * This method is used to respawn the ghost at its starting position and reset its state.
     */
    void respawn();  // New method to handle respawn logic
    /**
     * @brief Chooses a random valid direction for the ghost to move.
     * 
     * @param maze The maze object used to check for wall collisions.
     */
    void chooseRandomDirection(const Maze& maze);
    /**
     * @brief Checks if the ghost collides with Pac-Man.
     * 
     * @param pacman The Pac-Man object to check for collisions.
     * @return true if the ghost collides with Pac-Man, false otherwise.
     */
    bool checkCollisionWithPacMan(const PacMan& pacman) const;
    /**
     * @brief Chooses a new direction for the ghost when a collision occurs.
     * 
     * @param maze The maze object used to check for wall collisions.
     */
    void chooseNewDirection(const Maze& maze);
    /**
     * @brief Handles the ghost's movement to escape the starting box.
     * 
     * @param direction The current direction of the ghost.
     * @param newX The new x-coordinate to move the ghost to.
     * @param newY The new y-coordinate to move the ghost to.
     * @param deltaTime The time elapsed since the last frame (for smooth movement).
     */
    void ghostEscapeBox(int direction, auto newX, auto newY, float deltaTime);
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
    void ghostChasePacMan(int direction, auto newX, auto newY, float deltaTime, const Maze& maze, const PacMan& pacman);
    /**
     * @brief Moves the ghost based on its current direction and state.
     * 
     * @param maze The maze object used to check for wall collisions.
     * @param pacman The Pac-Man object used to determine chase behavior.
     * @param deltaTime The time elapsed since the last frame (for smooth movement).
     * @return The direction in which the ghost is moving.
     */
    int move(const Maze& maze,const PacMan& pacman, float deltaTime);  // Moves the ghost based on direction

    // Getters and setters for the ghost's position, state, and attributes.

    /**
     * @brief Gets the current x-coordinate of the ghost.
     * @return The x-coordinate of the ghost.
     */
    int getX() const { return x; }

    /**
     * @brief Gets the current y-coordinate of the ghost.
     * @return The y-coordinate of the ghost.
     */
    int getY() const { return y; }

    /**
     * @brief Gets the radius of the ghost for collision detection.
     * @return The radius of the ghost.
     */
    int getRadius() const { return radius; }

    /**
     * @brief Gets the current direction of the ghost.
     * @return The direction of the ghost.
     */
    int getDirection() const { return direction; }

    /**
     * @brief Gets the horizontal movement delta of the ghost.
     * @return The horizontal movement delta.
     */
    int getDX() const { return dx; }

    /**
     * @brief Gets the vertical movement delta of the ghost.
     * @return The vertical movement delta.
     */
    int getDY() const { return dy; }

    /**
     * @brief Gets the speed of the ghost.
     * @return The speed of the ghost in pixels per second.
     */
    int getSpeed() const { return speed; }

    /**
     * @brief Checks if the ghost is currently in an "eaten" state.
     * @return true if the ghost is eaten, false otherwise.
     */
    bool isEaten() const { return eaten; }
    /**
     * @brief Sets the ghost's "eaten" state.
     * @param state The new "eaten" state of the ghost.
     */
    void setEaten(bool state) { eaten = state; }


    /**
     * @brief Sets the ghost's movement direction.
     * @param newDirection The new direction of the ghost.
     */
    void setDirection(int newDirection) { direction = newDirection; }

    /**
     * @brief Checks if the ghost is currently in a frightened state.
     * @return true if the ghost is frightened, false otherwise.
     */
    bool isFrightened() const { return frightened; }
    /**
     * @brief Sets the ghost's frightened state.
     * @param state The new frightened state of the ghost.
     */
    void setFrightened(bool state) { frightened = state; }
    /**
     * @brief Resets the ghost's state to normal (not frightened).
     */
    void setNormal() { frightened = false; }
    /**
     * @brief Sets the position of the ghost.
     * @param newX The new x-coordinate of the ghost.
     * @param newY The new y-coordinate of the ghost.
     */
    void setPosition(float newX, float newY) { x = newX; y = newY; }

private:
    float x, y;          ///< Current position of the ghost.
    float dx, dy;        ///< Direction of the ghost's movement.
    float speed;         ///< Movement speed in pixels per second.
    int direction;       ///< Current direction of the ghost.
    int radius;          ///< Radius of the ghost for collision detection.
    bool frightened;     ///< Whether the ghost is in a frightened state.
    bool eaten;          ///< Whether the ghost has been eaten by Pac-Man.
    float startX, startY;///< Starting position of the ghost (for respawn).
};

#endif // GHOST_H