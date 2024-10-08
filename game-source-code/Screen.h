/**
 * @file Screen.h
 * @brief Defines the Screen class, which handles rendering and displaying different screens in the game.
 * 
 * The Screen class provides methods to display the start screen, the game over screen, and the win screen.
 * It manages drawing various game elements on the screen and handles window-related operations.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <raylib-cpp.hpp>
#include <memory>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Ghost.h"
#include "Fruit.h"
#include "GameKey.h"
#include "Score.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"


/**
 * @class Screen
 * @brief Manages rendering and displaying different screens in the game.
 * 
 * The Screen class provides functionality to render the start screen, the game over screen,
 * and the win screen. It also handles drawing game elements and managing the game window.
 */
class Screen {
public:
    /**
     * @brief Constructs a Screen object and initialises the game window.
     * 
     * Initialises the window with specified dimensions and title. Sets up the initial state of the game.
     */
    Screen();

    /**
     * @brief Destructor for the Screen class.
     * 
     * Cleans up any dynamically allocated memory or resources (if applicable).
     */
    ~Screen();

    /**
     * @brief Displays the start screen with game instructions and high score.
     * 
     * This method displays the game title, instructions for starting the game, and high score information.
     * It waits for the player to press ENTER to begin the game.
     * 
     * @param score Reference to the Score object to display the high score.
     */
    void startScreen(const Score& score, int frameNumber);

    /**
     * @brief Clears the screen and prepares it for rendering.
     * 
     * This method is used to reset the screen and draw a new frame, setting a black background.
     */
    void render();

    /**
     * @brief Draws additional game images (e.g., controls) on the start screen.
     * 
     * This method displays controls and other images on the start screen, such as input keys and game hints.
     */
    void drawGameImages();

    /**
     * @brief Displays the game over screen and waits for user input to exit.
     * 
     * This method displays the game over message, the player's score, and the high score. It waits
     * for a few seconds before closing the window and exiting the game.
     * 
     * @param score Reference to the Score object to display the current score and high score.
     * @param skipDelay Boolean that allows the function to skip the 3 second delay.
     * @return false Always returns false to ensure the game loop stops.
     */
    bool endGame(const Score& score, bool skipDelay = false);

    /**
     * @brief Displays the win screen and waits for user input to exit.
     * 
     * This method displays the win message, the player's score, and the high score. It waits
     * for a few seconds before restarting the game.
     * 
     * @param score Reference to the Score object to display the current score and high score.
     * @param skipDelay Boolean that allows the function to skip the 3 second delay.
     * @return false Always returns false to ensure the game loop stops.
     */
    bool winGame(const Score& score, bool skipDelay = false);

private:
    std::unique_ptr<Maze> maze;     ///< Pointer to the Maze object for managing maze-related operations.
    bool isRunning;                 ///< State to check if the game is running.
    int direction;                  ///< Current direction for Pac-Man's movement.
    raylib::Window window;          ///< Game window object for rendering.
    int num = 0;                    ///< Variable used for various counters and operations.
    bool eaten;                     ///< Flag to track if a certain object is eaten.
    Texture2D picture;              ///< Texture object to hold the picture to be drawn on the screen.

    /**
     * @brief Textures for various game images such as control keys and other hints.
     */
    std::vector<Texture2D> gameImages = {
        LoadTexture("../resources/pacman-images/inputkeys.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/pacman-images/SplashScreenBackground.png"),
    };

    std::vector<Texture2D> backgroundAnimation = {
        LoadTexture("../resources/backgroundAnimation/frame1.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/backgroundAnimation/frame2.png"),
        LoadTexture("../resources/backgroundAnimation/frame3.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/backgroundAnimation/frame4.png"),
        LoadTexture("../resources/backgroundAnimation/frame5.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/backgroundAnimation/frame6.png"),
        LoadTexture("../resources/backgroundAnimation/frame7.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/backgroundAnimation/frame8.png"),
        LoadTexture("../resources/backgroundAnimation/frame9.png"),  ///< Image showing the input keys.
        LoadTexture("../resources/backgroundAnimation/frame10.png"),
    };
};

#endif // SCREEN_H