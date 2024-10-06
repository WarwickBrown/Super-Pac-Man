/**
 * @file GameInitialiser.h
 * @brief Defines the GameInitialiser class, which handles the initialization of various game objects and collectables.
 */

#pragma once

#include "Game.h"
#include <memory>

/**
 * @class GameInitialiser
 * @brief A helper class responsible for initializing game objects such as the maze, Pac-Man, ghosts, and collectables.
 * 
 * The GameInitialiser class provides static methods to set up various game components, ensuring that all necessary objects
 * are properly initialized before the game starts. This includes creating fruits, power pellets, super pellets, keys, and stars.
 */
class GameInitialiser {
public:
    /**
     * @brief Initializes the primary game objects such as the maze, Pac-Man, screen, and ghosts.
     * 
     * @param game The Game instance to which the objects are added.
     */
    static void initialiseGameObjects(Game& game);

    /**
     * @brief Initializes the fruits at specific positions on the game map.
     * 
     * @param game The Game instance to which the fruits are added.
     * 
     * This function places fruits at various locations in a structured manner to form patterns or paths.
     */
    static void initialiseFruits(Game& game);

    /**
     * @brief Initializes the power pellets at specific positions on the game map.
     * 
     * @param game The Game instance to which the power pellets are added.
     * 
     * Power pellets provide special abilities or effects when collected by Pac-Man.
     */
    static void initialisePowerPellets(Game& game);

    /**
     * @brief Initializes the super pellets at specific positions on the game map.
     * 
     * @param game The Game instance to which the super pellets are added.
     * 
     * Super pellets grant Pac-Man additional abilities such as invincibility or enhanced speed.
     */
    static void initialiseSuperPellets(Game& game);

    /**
     * @brief Initializes the game keys at specific positions on the game map.
     * 
     * @param game The Game instance to which the keys are added.
     * 
     * Keys can be used to unlock certain sections of the maze, providing new pathways or access to collectables.
     */
    static void initialiseKeys(Game& game);

    /**
     * @brief Initializes the stars at specific positions on the game map.
     * 
     * @param game The Game instance to which the stars are added.
     * 
     * Stars are special objects that may provide additional points or effects when collected.
     */
    static void initialiseStars(Game& game);
};
