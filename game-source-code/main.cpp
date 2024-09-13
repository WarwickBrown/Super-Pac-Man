#include <raylib-cpp.hpp>
#include <iostream>
#include "Game.h"

// Entry point of the program
int main()
{
    // Create an instance of the Game class
    Game game;

    // Call the initialise method to set up the game objects, load images, and get ready for the game to start
    game.initialise();

    // Enter the main game loop, where the game is run until the player exits
    game.run();

    // Return 0 to indicate successful completion of the program
    return 0;
}
