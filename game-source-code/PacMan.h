/**
 * @file PacMan.h
 * @brief Defines the PacMan class, which represents the player character and its behavior.
 * 
 * The PacMan class handles the movement, state, and collision detection of the Pac-Man character in the game.
 * It manages Pac-Man's direction, speed, super mode, and invincibility.
 */

#ifndef PACMAN_H
#define PACMAN_H

#include <raylib-cpp.hpp>
#include "Maze.h"

/**
 * @class PacMan
 * @brief Represents the Pac-Man character in the game, handling its movement, collision detection, and states.
 * 
 * The PacMan class provides methods to control the movement and state of Pac-Man, including changing direction,
 * activating super mode, and managing invincibility. It also handles animation frames based on movement.
 */
class PacMan {
public:
    /**
     * @enum Direction
     * @brief Defines the possible movement directions for Pac-Man.
     */
    enum Direction {
        RIGHT = 1, ///< Moving right.
        LEFT,      ///< Moving left.
        UP,        ///< Moving up.
        DOWN,      ///< Moving down.
        NONE       ///< No movement.
    };

    /**
     * @brief Constructs a PacMan object with a specified starting position.
     * 
     * @param startX The initial x-coordinate of Pac-Man's starting position.
     * @param startY The initial y-coordinate of Pac-Man's starting position.
     */
    PacMan(int startX, int startY);

    /**
     * @brief Destructor for the PacMan class.
     * 
     * This destructor does not perform any specific actions but is defined for completeness.
     */
    ~PacMan();

    /**
     * @brief Sets Pac-Man's movement direction.
     * 
     * @param direction The new movement direction for Pac-Man.
     */
    void setDirection(Direction direction);

    /**
     * @brief Determines and returns the current animation frame based on direction and frame time.
     * 
     * @param frame The current frame index.
     * @return The animation frame index based on Pac-Man's direction and frame time.
     */
    int location(int frame) const;

    /**
     * @brief Moves Pac-Man based on the direction and delta time, and checks for collisions with the maze.
     * 
     * @param maze The maze object used to check for wall collisions.
     * @param deltaTime The time elapsed since the last frame (for smooth movement).
     * @param direction The direction in which Pac-Man is moving.
     */
    void move(const Maze& maze, float deltaTime, Direction direction);

    // Getters for Pac-Man's position, movement, radius, and speed.
    /**
     * @brief Gets Pac-Man's current x-coordinate.
     * 
     * @return The x-coordinate of Pac-Man.
     */
    float getX() const { return x; }

    /**
     * @brief Gets Pac-Man's current y-coordinate.
     * 
     * @return The y-coordinate of Pac-Man.
     */
    float getY() const { return y; }

    /**
     * @brief Gets Pac-Man's visual radius (used for rendering).
     * 
     * @return The visual radius of Pac-Man.
     */
    float getVisualRadius() const { return visualRadius; }

    /**
     * @brief Gets Pac-Man's movement in the x direction.
     * 
     * @return The horizontal movement delta of Pac-Man.
     */
    int getDX() const { return dx; }

    /**
     * @brief Gets Pac-Man's movement in the y direction.
     * 
     * @return The vertical movement delta of Pac-Man.
     */
    int getDY() const { return dy; }

    /**
     * @brief Gets the current frame time for Pac-Man animations.
     * 
     * @return The frame time value.
     */
    int getFrames() const { return GetFrameTime(); }

    /**
     * @brief Gets Pac-Man's radius for collision detection.
     * 
     * @return The radius of Pac-Man.
     */
    int getRadius() const { return radius; }

    /**
     * @brief Gets Pac-Man's normal movement speed.
     * 
     * @return The speed of Pac-Man in pixels per second.
     */
    int getSpeed() { return normalSpeed; }

    /**
     * @brief Checks if Pac-Man is in an invincible state.
     * 
     * @return true if Pac-Man is invincible, false otherwise.
     */
    bool isInvincible() const { return invincible; }

    /**
     * @brief Checks if Pac-Man is in super mode.
     * 
     * @return true if Pac-Man is in super mode, false otherwise.
     */
    bool isSuper() const { return superModeActive; }

    /**
     * @brief Sets Pac-Man's position to a new location.
     * 
     * @param newX The new x-coordinate of Pac-Man's position.
     * @param newY The new y-coordinate of Pac-Man's position.
     */
    void setPosition(int newX, int newY);

    /**
     * @brief Sets Pac-Man's invincibility state.
     * 
     * @param invincible The new invincibility state.
     */
    void setInvincible(bool invincible);

    /**
     * @brief Updates Pac-Man's invincibility timer based on elapsed time.
     * 
     * @param deltaTime The time elapsed since the last frame (for smooth updates).
     */
    void updateInvincibility(float deltaTime);

    /**
     * @brief Updates Pac-Man's super mode timer based on elapsed time.
     * 
     * @param deltaTime The time elapsed since the last frame (for smooth updates).
     */
    void updateSuperMode(float deltaTime);

    /**
     * @brief Activates super mode for Pac-Man.
     * 
     * Super mode increases Pac-Man's speed and allows him to interact differently with ghosts.
     */
    void activateSuperMode();

    /**
     * @brief Deactivates super mode for Pac-Man.
     * 
     * Resets Pac-Man's state back to normal mode.
     */
    void deactivateSuperMode();

private:
    float x, y;             ///< Pac-Man's current position on the screen (x, y).
    float dx, dy;           ///< Direction of movement (change in x, change in y).
    int newDirection;       ///< The new direction Pac-Man wants to move in.
    int radius;             ///< Radius of Pac-Man (used for collision detection).
    float visualRadius;     ///< Visual radius for rendering Pac-Man.
    float normalSpeed;      ///< Movement speed of Pac-Man (pixels per second).
    float superSpeed;       ///< Movement speed during super mode.
    bool superModeActive;   ///< Indicates if super mode is active.
    float superModeDuration;///< Duration of super mode.
    float superModeTimer;   ///< Timer for tracking super mode state.
    bool invincible;        ///< Indicates if Pac-Man is currently invincible.
    float invincibilityTime;///< Remaining time of invincibility.
    float invincibilityDuration; ///< Duration of invincibility mode.
};

#endif // PACMAN_H
