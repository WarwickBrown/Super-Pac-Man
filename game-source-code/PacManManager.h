/**
 * @file PacManManager.h
 * @brief Defines the PacManManager class, which manages the movement and state of Pac-Man in the game.
 * 
 * The PacManManager class is responsible for updating Pac-Man's state and controlling his movement
 * within the game environment. It interacts with the game object to check for collisions and updates
 * Pac-Man's behavior based on the current game state.
 */

#ifndef PACMANMANAGER_H
#define PACMANMANAGER_H

#include "Game.h"
#include <memory>

class Game;

/**
 * @class PacManManager
 * @brief Manages Pac-Man's movement, direction, and state updates within the game.
 * 
 * The PacManManager class handles Pac-Man's interactions with the game environment, including movement,
 * collision detection, and state changes such as activating super mode or invincibility. It communicates
 * directly with the game object to access necessary information, such as the maze layout and Pac-Man's state.
 */
class PacManManager {
public:

    /**
     * @brief Constructs a PacManManager object and associates it with the given game instance.
     * 
     * @param game A reference to the Game instance that this PacManManager will manage.
     */
    explicit PacManManager(Game& game);

    /**
     * @brief Updates Pac-Man's direction, movement, and state based on the elapsed time.
     * 
     * This method updates Pac-Man's state, such as super mode and invincibility, and controls his movement
     * within the game environment. It checks for wall collisions and updates Pac-Man's direction accordingly.
     * 
     * @param deltaTime The time elapsed since the last frame (used for smooth movement and state updates).
     */
    void updatePacMan(float deltaTime);

private:
    Game& game;  ///< Reference to the game object to access maze, Pac-Man, and other game elements.
};

#endif // PACMANMANAGER_H
