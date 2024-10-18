/**
 * @file Update.h
 * @brief Defines the Update class, responsible for updating the state of various game components.
 * 
 * The Update class manages the state of game elements such as power pellets, super pellets, fruits,
 * stars, and keys. It interacts with the Game and Draw classes to update the game world as
 * the game progresses.
 */

#ifndef UPDATE_H
#define UPDATE_H

#include "Game.h"
#include "Draw.h"
#include "SoundManager.h"
#include <memory>

class Draw;
class Game;

/**
 * @class Update
 * @brief Manages the state and behavior of various game components.
 * 
 * The Update class is responsible for handling the interactions and updates of different
 * game elements, including power pellets, super pellets, fruits, stars, and keys. It also
 * manages Pac-Man's invincibility and collision detection with ghosts and other collectibles.
 */
class Update {
public:
    /**
     * @brief Constructs an Update object using a reference to the Game instance and a pointer to the Draw instance.
     * 
     * Initialises the Update class with references to the main Game and Draw instances, allowing
     * it to access and modify game components during each frame update.
     * 
     * @param game Reference to the Game instance.
     * @param drawInstance Pointer to the Draw instance.
     */
    explicit Update(Game& game, Draw* drawInstance);

    /**
     * @brief Updates the state of the entire game, including all collectibles and player status.
     * 
     * This method calls individual update functions for each collectible type and player state,
     * ensuring that the game elements are properly updated during each frame.
     * 
     * @param deltaTime The time elapsed since the last frame, used for smooth updates.
     */
    void updateGame(float deltaTime);

    /**
     * @brief Updates the state of power pellets and handles collision detection with Pac-Man.
     * 
     * Checks if Pac-Man collides with any active power pellet, and if so, activates frightened mode
     * for all ghosts and awards points to Pac-Man.
     */
    void updatePowerPellets();

    /**
     * @brief Updates the state of super pellets and handles collision detection with Pac-Man.
     * 
     * Checks if Pac-Man collides with any active super pellet, and if so, activates super mode for
     * Pac-Man, deactivates the pellet, and awards points to Pac-Man.
     */
    void updateSuperPellets();

    /**
     * @brief Updates the state of fruits and handles collision detection with Pac-Man.
     * 
     * Checks if Pac-Man collides with any active fruit, and if so, collects the fruit and awards
     * points to Pac-Man.
     */
    void updateFruits();

    /**
     * @brief Updates the state of stars and handles collision detection with Pac-Man.
     * 
     * Manages the appearance of stars, checks for collisions with Pac-Man, and awards points based
     * on the current star conditions.
     */
    void updateStars();

    /**
     * @brief Updates the state of keys and handles collision detection with Pac-Man.
     * 
     * Checks if Pac-Man collides with any active key, and if so, deactivates the key, unlocks the
     * corresponding walls, and awards points to Pac-Man.
     */
    void updateKeys();

    /**
     * @brief Updates Pac-Man's invincibility state and handles collision detection with ghosts.
     * 
     * Manages Pac-Man's invincibility state and handles collision detection between Pac-Man and
     * ghosts. If Pac-Man collides with a ghost, determines the outcome based on Pac-Man's state.
     * 
     * @param deltaTime The time elapsed since the last frame, used for smooth updates.
     */
    void updateInvincibility(float deltaTime);

private:
    Game& game;  ///< Reference to the Game instance for accessing game elements and state.
    Draw* draw;  ///< Pointer to the Draw instance for rendering and visual updates.
    std::unique_ptr<SoundManager> soundManager; ///< Unique pointer to the SoundManager object.
};

#endif // UPDATE_H