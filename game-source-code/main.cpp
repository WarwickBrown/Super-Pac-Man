/**
 * @file main.cpp
 * @brief Entry point for the Pac-Man game.
 * 
 * This file contains the main function, which initializes and starts the game loop.
 */

#include <raylib-cpp.hpp>
#include <iostream>
#include "Game.h"

/**
 * @brief The main function that serves as the entry point for the game.
 * 
 * The function creates an instance of the Game class, initializes the game, and starts the main game loop.
 * It continues to run until the player exits the game.
 * 
 * @return An integer value indicating the status of the program upon termination (0 = successful).
 */
int main()
{
    // Create an instance of the Game class.
    Game game;

    // Call the initialise method to set up the game objects, load images, and get ready for the game to start.
    game.initialise(false);

    // Enter the main game loop, where the game is run until the player exits.
    game.run();

    // Return 0 to indicate successful completion of the program.
    return 0;
}
