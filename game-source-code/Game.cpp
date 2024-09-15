#include "Game.h"
#include "Screen.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

// Constructor - Initializes game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), direction(0), frame(0) {}

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
        frame = pacMan->location(frame, direction);  // Update Pac-Man's frame for animation
        screen->drawPacMan(*pacMan, frame, oldDirection);  // Draw Pac-Man with its current frame and direction
    }
    
    // Display the end game screen and stop running the game
    isRunning = screen->endGame();  
}

// Handles user input for controlling Pac-Man's direction
void Game::handleInput() {
    auto key = GetKeyPressed();
    // Check if the ESCAPE key is pressed to exit the game
    if (key == KEY_ESCAPE) {
        isRunning = false;  // Stop the game loop
        return;
    }

    // Detect arrow key presses to update Pac-Man's direction
    switch (key) {
    case KEY_RIGHT:
        direction = 1;  // Move right
        break;
    case KEY_LEFT:
        direction = 2;  // Move left
        break;
    case KEY_UP:
        direction = 3;  // Move up
        break;
    case KEY_DOWN:
        direction = 4;  // Move down
        break;
    default:
        // No direction change
        break;
    }
}

// Updates the game state (e.g., Pac-Man's position)
void Game::update() {
    int dx, dy;
    switch (direction) {
    case 1: 
            dx = 1; 
            dy = 0; 
            break;  // Right movement
        case 2: 
            dx = -1; 
            dy = 0; 
            break; // Left movement
        case 3: 
            dx = 0; 
            dy = -1; 
            break; // Down movement
        case 4: 
            dx = 0; 
            dy = 1; 
            break;  // Up movement
        default: 
            dx = 0; 
            dy = 0; 
            break;
    }
    float newX = pacMan->getX()+dx;
    float newY = pacMan->getY()+dy;
    if (!maze->isWallRec(newX, newY, 39)) {
        oldDirection = direction;
    }
    
    float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
    pacMan->move(*maze, deltaTime, oldDirection);  // Move Pac-Man based on the direction and elapsed time
}

// For checking collisions with ghosts later
// Maybe we should check pacman collisions here too
// void Game::checkCollisions() {
    
// }

// Initializes game objects like the maze, Pac-Man, and the screen
void Game::initialiseGameObjects() {
    maze = new Maze();  // Create and initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Create and initialize Pac-Man at the starting position
    screen = new Screen(); // Create and initialize the screen
}

// Initializes game images (like the arrow key instructions)
void Game::initiliseGameImages() {
    // Load the texture for the arrow key image and store it in the gameImages vector
    Texture2D arrowKeyImage = LoadTexture("../resources/pacman-images/inputkeys.png");
    gameImages.push_back(arrowKeyImage);  // Add the loaded image to the vector
}

// Returns a reference to the vector of game images (to be used for rendering)
const std::vector<Texture2D>& Game::getGameImages() const {
    return gameImages;  // Return a reference to the vector containing game images
}


