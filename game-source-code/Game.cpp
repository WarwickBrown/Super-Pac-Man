#include "Game.h"
#include "Screen.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

// Constructor - Initializes game window, running state, and sets pointers to nullptr
Game::Game() : window(1600, 900, "Super Pac-Man"), isRunning(true), maze(nullptr), pacMan(nullptr), dir(0), frame(0) {}

// Destructor - Frees dynamically allocated memory for maze, pacMan, and screen
Game::~Game() {
    // Clean up dynamically allocated memory
    delete maze;
    delete pacMan;
    delete screen;
}

// Function to initialize the game
void Game::initialise() {
    initialiseGameObjects();    // Initializes game objects (maze, pacMan, screen)
    initiliseGameImages();      // Initializes game images like arrow keys
    pacMan->initilisePacManImages(); // Loads Pac-Man images

    // Display the start screen until the player presses ENTER or closes the window
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        screen->startScreen(this); // Shows the start screen and passes the current game instance
    }

    // Check if the window is closed by the user
    if (window.ShouldClose()) {
        isRunning = false;  // Stop running the game if the window is closed
    }
}

// Main game loop
void Game::run() {
    int pixelX; // Coordinates for rendering
    int pixelY;

    // Continue the game loop until the window is closed or the game stops running
    while (isRunning && !window.ShouldClose()) {
        handleInput();   // Handle user input like key presses for movement
        update();        // Update game state (Pac-Man's position, etc.)
        screen->render(); // Render the current state of the game
        screen->drawMaze(*maze);  // Draw the maze
        frame = pacMan->location(frame, dir);  // Update Pac-Man's frame for animation
        screen->drawPacMan(*pacMan, frame, dir);  // Draw Pac-Man with its current frame and direction
    }
    
    // Display the end game screen and stop running the game
    isRunning = screen->endGame();  
}

// Handles user input for controlling Pac-Man's direction
void Game::handleInput() {
    // Check if the ESCAPE key is pressed to exit the game
    if (IsKeyDown(KEY_ESCAPE)) {
        isRunning = false;  // Stop the game loop
        return;
    }

    // Detect arrow key presses to update Pac-Man's direction
    if (IsKeyPressed(KEY_RIGHT)) {
        dir = 1;  // Move right
    } else if (IsKeyPressed(KEY_LEFT)) {
        dir = 2;  // Move left
    } else if (IsKeyPressed(KEY_UP)) {
        dir = 3;  // Move up
    } else if (IsKeyPressed(KEY_DOWN)) {
        dir = 4;  // Move down
    }
}

// Updates the game state (e.g., Pac-Man's position)
void Game::update() {
    float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
    pacMan->move(*maze, deltaTime, dir);  // Move Pac-Man based on the direction and elapsed time
}

// Initializes game objects like the maze, Pac-Man, and the screen
void Game::initialiseGameObjects() {
    maze = new Maze();  // Create and initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Create and initialize Pac-Man at the starting position
    screen = new Screen(); // Create and initialize the screen
}

// Initializes game images (like the arrow key instructions)
void Game::initiliseGameImages() {
    // Load the texture for the arrow key image and store it in the gameImages vector
    Texture2D arrowKeyImage = LoadTexture("../resources/game-images/inputkeys.png");
    gameImages.push_back(arrowKeyImage);  // Add the loaded image to the vector
}

// Returns a reference to the vector of game images (to be used for rendering)
const std::vector<Texture2D>& Game::getGameImages() const {
    return gameImages;  // Return a reference to the vector containing game images
}
