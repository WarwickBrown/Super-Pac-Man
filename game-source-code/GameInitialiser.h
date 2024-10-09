/**
 * @file GameInitialiser.h
 * @brief Defines the GameInitialiser class, which handles the initialisation of various game objects and collectables.
 */

#pragma once

#include "GameInitialiser.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Reader.h"

/**
 * @class GameInitialiser
 * @brief A helper class responsible for initialising game objects such as the maze, Pac-Man, ghosts, and collectables.
 * 
 * The GameInitialiser class provides static methods to set up various game components, ensuring that all necessary objects
 * are properly initialised before the game starts. This includes creating fruits, power pellets, super pellets, keys, and stars.
 */

class GameInitialiser : public Reader{
public:
    /**
     * @brief Initialises the primary game objects such as the maze, Pac-Man, screen, and ghosts.
     * 
     * @param game The Game instance to which the objects are added.
     */
    static void initialiseGameObjects(Game& game);

    /**
    * @brief Initialises the fruit at specific positions on the game map.
    * 
    * @param game The Game instance to which the fruit are added.
    * @param iss Data line that contains the fruits coordinates.
    * 
    * Fruits are special objects that provide additional points when collected.
    */
    static void processFruit(Game& game, std::istringstream& iss);

    /**
    * @brief Initialises the keys at specific positions on the game map.
    * 
    * @param game The Game instance to which the keys are added.
    * @param iss Data line that contains the keys coordinates.
    * 
    * Keys are special objects that unlock doors when collected.
    */
    static void processKey(Game& game, std::istringstream& iss);

    /**
    * @brief Initialises the Super Pellets at specific positions on the game map.
    * 
    * @param game The Game instance to which the Super Pellets are added.
    * @param iss Data line that contains the Super Pellets coordinates.
    * 
    * Super Pellets are special objects that provide additional effects when collected.
    */
    static void processSuperPellet(Game& game, std::istringstream& iss);

    /**
    * @brief Initialises the Power Pellets at specific positions on the game map.
    * 
    * @param game The Game instance to which the Power Pellets are added.
    * @param iss Data line that contains the Power Pellets coordinates.
    * 
    * Power Pellets are special objects that provide additional effects when collected.
    */
    static void processPowerPellet(Game& game, std::istringstream& iss);

    /**
    * @brief Initialises the star at specific positions on the game map.
    * 
    * @param game The Game instance to which the star is added.
    * @param iss Data line that contains the star coordinates.
    * 
    * Stars are special objects that provide additional points when collected.
    */
    static void processStar(Game& game, std::istringstream& iss);

    /**
    * @brief Initialises the collectables at specific positions on the game map.
    * 
    * @param game The Game instance to which the collectables are extracted.
    * 
    * Collectables are special objects that may provide additional points or effects when collected.
    */
    static void initialiseCollectables(Game& game);
};
