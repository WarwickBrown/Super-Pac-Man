/**
 * @file PacMan.cpp
 * @brief Implements the PacMan class, which represents the player character and its behavior.
 * 
 * The PacMan class manages Pac-Man's movement, state changes, and interactions within the game,
 * such as collision detection with the maze walls and activation of special modes.
 */

#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>

using namespace std;

/**
 * @brief Constructs a PacMan object with a specified starting position.
 * 
 * Initializes Pac-Man's starting position, movement speed, radius, and various states, such as
 * invincibility and super mode. The initial direction is set to no movement.
 * 
 * @param startX The initial x-coordinate of Pac-Man's position.
 * @param startY The initial y-coordinate of Pac-Man's position.
 */
PacMan::PacMan(int startX, int startY) 
    : x(765), y(525), dx(0), dy(0), normalSpeed(250), radius(34), superSpeed(400),
      superModeActive(false), superModeDuration(10), superModeTimer(0), invincible(false),
      invincibilityTime(0.0f), invincibilityDuration(2.0f) {}

/**
 * @brief Destructor for the PacMan class.
 * 
 * This destructor does not perform any specific actions but is defined for completeness.
 * There is no dynamic memory to clean up in this class.
 */
PacMan::~PacMan() {}

/**
 * @brief Sets Pac-Man's movement direction based on the given direction.
 * 
 * This method updates Pac-Man's movement direction by adjusting the dx and dy variables,
 * which represent movement in the x and y directions, respectively.
 * 
 * @param direction The new direction for Pac-Man to move (e.g., RIGHT, LEFT, UP, DOWN, NONE).
 */
void PacMan::setDirection(Direction direction) {
    switch (direction) {
        case RIGHT: 
            dx = 1; dy = 0;
            break;
        case LEFT: 
            dx = -1; dy = 0;
            break;
        case UP: 
            dx = 0; dy = -1;
            break;
        case DOWN: 
            dx = 0; dy = 1;
            break;
        default: 
            dx = 0; dy = 0;  // No movement
    }
}

/**
 * @brief Determines and returns the current animation frame based on direction and frame time.
 * 
 * This method manages the frame timing to control how quickly Pac-Man's sprite animation changes
 * as he moves. The animation frame cycles through 6 frames (0 to 5).
 * 
 * @param frame The current frame index.
 * @return The animation frame index based on Pac-Man's direction and frame time.
 */
int PacMan::location(int frame) const {
    static auto timer = 0.0f;  ///< Timer to control the speed of the frame change.
    timer += GetFrameTime();   ///< Add time since the last frame.

    // If the timer exceeds 0.2 seconds, advance to the next frame.
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;  ///< Cycle through 6 frames (0 to 5).
    }

    return frame;  ///< Return the updated frame number.
}

/**
 * @brief Moves Pac-Man based on the direction and checks for wall collisions.
 * 
 * This method calculates Pac-Man's new position based on his direction and speed.
 * If there is no collision with the walls, Pac-Man's position is updated accordingly.
 * 
 * @param maze The maze object used to check for wall collisions.
 * @param deltaTime The time elapsed since the last frame (for smooth movement).
 * @param direction The direction in which Pac-Man is moving.
 */
void PacMan::move(const Maze& maze, float deltaTime, Direction direction) {
    auto speed = superModeActive ? superSpeed : normalSpeed;  ///< Use super speed if in super mode.

    setDirection(direction);  ///< Set the movement direction based on input direction.

    // Calculate the new position.
    auto newX = x + dx;
    auto newY = y + dy;

    // Check if the new position is not colliding with a wall.
    if ((dx != 0 || dy != 0) && !maze.isWall(newX, newY, radius)) {
        x += dx * speed * deltaTime;  ///< Update x position if no collision.
        y += dy * speed * deltaTime;  ///< Update y position if no collision.
    }
}

/**
 * @brief Sets Pac-Man's invincibility state.
 * 
 * When Pac-Man becomes invincible, his invincibility timer is reset, and his position is set to (765, 525).
 * 
 * @param invincible The new invincibility state of Pac-Man.
 */
void PacMan::setInvincible(bool invincible) {
    this->invincible = invincible;
    setPosition(765, 525);  ///< Reset Pac-Man's position.
    if (invincible) {
        invincibilityTime = 0.0f;  ///< Reset the invincibility timer.
    }
}

/**
 * @brief Updates Pac-Man's invincibility timer based on elapsed time.
 * 
 * If Pac-Man is invincible, the timer counts down. Once the invincibility duration is over,
 * Pac-Man's invincibility state is deactivated.
 * 
 * @param deltaTime The time elapsed since the last frame (for smooth updates).
 */
void PacMan::updateInvincibility(float deltaTime) {
    if (invincible) {
        invincibilityTime += deltaTime;  ///< Increment the invincibility timer.
        if (invincibilityTime >= invincibilityDuration) {
            invincible = false;          ///< Deactivate invincibility.
            invincibilityTime = 0.0f;
        }
    }
}

/**
 * @brief Activates super mode for Pac-Man.
 * 
 * Super mode increases Pac-Man's speed and visual radius, allowing him to interact differently with ghosts.
 */
void PacMan::activateSuperMode() {
    superModeActive = true;
    superModeTimer = 4.0f;      ///< Set the super mode timer duration.
    visualRadius = radius * 1.5f;  ///< Increase visual radius.
}

/**
 * @brief Deactivates super mode for Pac-Man.
 * 
 * Resets Pac-Man's state back to normal mode, including his visual radius and speed.
 */
void PacMan::deactivateSuperMode() {
    superModeActive = false;
    visualRadius = radius;  ///< Reset visual radius to normal.
}

/**
 * @brief Updates Pac-Man's super mode timer based on elapsed time.
 * 
 * If super mode is active, the timer decreases. When the timer reaches zero,
 * super mode is deactivated.
 * 
 * @param deltaTime The time elapsed since the last frame (for smooth updates).
 */
void PacMan::updateSuperMode(float deltaTime) {
    if (superModeActive) {
        superModeTimer -= deltaTime;  ///< Decrease timer based on elapsed time.
        if (superModeTimer <= 0.0f) {
            deactivateSuperMode();  ///< Deactivate super mode when timer ends.
        }
    }
}

/**
 * @brief Sets Pac-Man's position to a new location.
 * 
 * Updates Pac-Man's x and y coordinates to the specified position.
 * 
 * @param newX The new x-coordinate of Pac-Man's position.
 * @param newY The new y-coordinate of Pac-Man's position.
 */
void PacMan::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
