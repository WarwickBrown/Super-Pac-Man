#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Screen.h"
#include "Fruit.h"
#include "Ghost.h"
#include "GameKey.h"
#include "Star.h"
#include "Score.h"
#include "Lives.h"
#include "PowerPellet.h"
#include "SuperPellet.h"

// Forward declaration of the Screen class to allow Game class to reference it
class Screen;
class Ghost;

class Game {
public:
    Game();  // Constructor - Initializes game properties and sets up the game window
    ~Game(); // Destructor - Cleans up dynamically allocated memory

    void initialise();   // Initializes the game (calls functions to setup game objects, loads images, etc.)
    void initiliseGameImages(); // Loads game images (like arrow keys) into a vector
    void initialiseFruits();
    void initialisePowerPellets();  // Function to initialize power pellets
    void initialiseKeys();
    void initialiseSuperPellets();
    void run();          // Main game loop - Handles input, updates the game state, and renders the game
    void handleInput();  // Handles user input (e.g., arrow keys for controlling Pac-Man)
    void update();       // Updates the game state (e.g., moves Pac-Man and updates positions)
    void render();       // Renders game objects (maze, Pac-Man, etc.) on the screen
    void endGame();      // Ends the game (shows game over screen or exits)
    void checkWinCondition(); // Add this method to check the win condition
    void inputStar();

    std::vector<GameKey> keys;

    
    const std::vector<Texture2D>& getGameImages() const;  // Returns a constant reference to the game images (for rendering)

private:
    std::vector<Texture2D> gameImages;  // Vector to hold game-related images (e.g., arrow key instructions)
    std::vector<Fruit> fruits;
    std::vector<Star> stars;
    std::vector<PowerPellet> powerPellets;  // Add a list of power pellets
    std::vector<Ghost> ghosts;  // Vector to hold multiple ghosts
    std::vector<SuperPellet> superPellets;
    
    // Pointers to various game objects
    Maze* maze;  // Pointer to the maze object
    PacMan* pacMan;  // Pointer to the Pac-Man object
    Screen* screen;  // Pointer to the screen object
    Score* score;
    Lives* playerLives; // Pointer to Lives object

    bool isRunning;  // Boolean to track whether the game is running or not
    int totalFrames = 1;
    int direction, ghostDirection;         // Integer representing the direction Pac-Man is moving (right, left, up, down)
    int oldDirection = 2;
    raylib::Window window;  // The game window where the game will be rendered
    int frame;       // Current frame number (used for animation)
    bool gameWon;    // Track if the game is won
    int symbolCounter = 0;
    float timerStart = GetTime();
    int multi = 0, multi2 = 1;
    int num1 = 1, num2 = 1, num3 = 1;
    float powerPelletTimer;
    
    Texture2D arrowKeyImage;  // Texture for the arrow key instructions

    void initialiseGameObjects(); // Initializes game objects like the maze, Pac-Man, and screen

};

#endif // GAME_H
