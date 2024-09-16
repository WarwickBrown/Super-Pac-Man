#include "Game.h"
#include "Screen.h"
#include "Ghost.h"
#include "Fruit.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

// Constructor - Initializes game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), direction(0), frame(0), gameWon(false) {}

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
    initialiseFruits();
    initialiseKeys();
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
        screen->drawKeys(keys);
        frame = pacMan->location(frame, direction);  // Update Pac-Man's frame for animation
        screen->drawFruits(fruits);
        // Draw each fruit on the screen
        for (const auto& fruit : fruits) {
            fruit.draw();
        }
        screen->drawPacMan(*pacMan, frame, oldDirection);  // Draw Pac-Man with its current frame and direction

        screen->drawInner();
        // Draw the fruits on the screen

        for (const auto& ghost : ghosts) {
            int ghostDirection = ghost.getGhostDirection();
            screen->drawGhost(ghost, ghostDirection);
            std::cout << ghostDirection << std::endl;
        }
        

        
/*
        // Draw each ghost
        for (const auto& ghost : ghosts) {
            screen->drawGhost(ghost, ghostDirection);
            std::cout << ghostDirection << std::endl;
        }*/

                // If the game has been won, break the loop
        if (gameWon) {
            break;
        }
    }

        // If the game is won, show the win screen
        if (gameWon) {
            isRunning = screen->winGame();
        } else {
            // Otherwise, show the end game screen
            isRunning = screen->endGame();  
        }

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

    // Check if Pac-Man collects any fruits
    for (auto& fruit : fruits) {
        if (!fruit.isEaten() && fruit.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-35,
                { (float)fruit.getX(), (float)fruit.getY() }, fruit.getRadius())) {
            fruit.collect();
            fruit.markAsEaten();
            // Increase score or trigger other game events
        }
    }

        // Check if all fruits have been collected
    checkWinCondition();

        // Check if Pac-Man collects any keys
    for (auto& key : keys) {
        if (key.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            key.collect();
            // Unlock associated walls
            for (int wallIndex : key.getWallsToUnlock()) {
                maze->getWalls()[wallIndex].active = false;
            }
        }
    }


    // Update each ghost's behavior
    for (auto& ghost : ghosts) {
        // Move each ghost, passing the maze and Pac-Man as references
        ghost.move(*maze, deltaTime, *pacMan, ghost.getState());

        // Check for collision with Pac-Man
        if (ghost.checkCollisionWithPacMan(*pacMan)) {
            // Collision detected, end the game
            isRunning = false;
            return;
        }
    }
}


// Initializes game objects like the maze, Pac-Man, and the screen
void Game::initialiseGameObjects() {
    maze = new Maze();  // Create and initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Create and initialize Pac-Man at the starting position
    screen = new Screen(); // Create and initialize the screen

    ghosts.push_back(Ghost(685, 445, 150.0f));  // Ghost 1 at (200, 200) with speed 150
    ghosts.push_back(Ghost(765, 445, 150.0f));  // Ghost 2 at (400, 400) with speed 150
    ghosts.push_back(Ghost(845, 445, 150.0f));  // Ghost 3 at (600, 600) with speed 150
    ghosts.back().switchState(GhostState::Escaping, *maze); // Set initial state to Escaping
}

// Initializes game images (like the arrow key instructions)
void Game::initiliseGameImages() {
    // Load the texture for the arrow key image and store it in the gameImages vector
    Texture2D arrowKeyImage = LoadTexture("../resources/pacman-images/inputkeys.png");
    gameImages.push_back(arrowKeyImage);  // Add the loaded image to the vector
    Texture2D keyTexture = LoadTexture("../resources/pacman-images/ghostyUP.png");
    gameImages.push_back(keyTexture);
}

// Returns a reference to the vector of game images (to be used for rendering)
const std::vector<Texture2D>& Game::getGameImages() const {
    return gameImages;  // Return a reference to the vector containing game images
}

// Initialize the fruits in the game
void Game::initialiseFruits() {
    // Load fruit texture (replace with the correct path)
    Texture2D fruitTexture = LoadTexture("../resources/pacman-images/fruit.png");

    // Add fruits to specific positions
    fruits.emplace_back(40, 840, fruitTexture);
    fruits.emplace_back(1480, 840, fruitTexture);
    fruits.emplace_back(920, 760, fruitTexture);
    fruits.emplace_back(600, 760, fruitTexture);
    fruits.emplace_back(440, 440, fruitTexture);
    fruits.emplace_back(1160, 440, fruitTexture);
    // Add more fruits as needed
}

void Game::initialiseKeys() {
    Texture2D keyTexture = LoadTexture("../resources/pacman-images/ghostyUP.png");

    // Suppose walls[5] and walls[10] are to be unlocked by the key at (500, 500)
    keys.emplace_back(500, 500, std::vector<int>{5, 10});

    // Another key that unlocks walls[15] and walls[20]
    keys.emplace_back(700, 300, std::vector<int>{15, 20});
}


// Implement the method to check if all fruits are collected
void Game::checkWinCondition() {
    for (const auto& fruit : fruits) {
        if (fruit.isActive()) {
            return;  // If any fruit is still active, return early
        }
    }
    // If all fruits are collected, set gameWon to true
    gameWon = true;
    isRunning = false;  // Stop the game loop
}