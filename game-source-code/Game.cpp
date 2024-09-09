#include "Game.h"
#include <raylib-cpp.hpp>

// Constructor
Game::Game() : window(800, 600, "Super Pac-Man"), isRunning(true), maze(nullptr), pacMan(nullptr) {}

// Destructor
Game::~Game() {
    // Clean up dynamically allocated memory
    delete maze;
    delete pacMan;
    for (auto ghost : ghosts) {
        delete ghost;
    }
}

void Game::initialize() {
    // Initialize game objects
    initializeGameObjects();
    
    // Show splash screen
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);
    DrawText("Press Arrow Keys to Control Pac-Man", 200, 200, 20, BLACK);
    DrawText("Press ESC to Exit", 200, 230, 20, BLACK);
    window.EndDrawing();

    // Wait for a key press
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        // Just wait
    }
}


// Maingameloop
void Game::run() {
    while (isRunning && !window.ShouldClose()) {
        handleInput();   // Handle user input
        update();        // Update game state
        render();        // Render the game
    }

    endGame();  // End the game
}

// Handle user input
void Game::handleInput() {
    if (IsKeyDown(KEY_RIGHT)) {
        pacMan->setDirection(1, 0); // Move right
    } else if (IsKeyDown(KEY_LEFT)) {
        pacMan->setDirection(-1, 0); // Move left
    } else if (IsKeyDown(KEY_UP)) {
        pacMan->setDirection(0, -1); // Move up
    } else if (IsKeyDown(KEY_DOWN)) {
        pacMan->setDirection(0, 1); // Move down
    }
}

// Update game state
void Game::update() {
    pacMan->move(*maze);  // Update Pac-Man's position
    for (auto& ghost : ghosts) {
        ghost->move(*maze,*pacMan);  // Update each ghost's position
    }
    checkCollisions();  // Check for collisions
}

// Render game objects
void Game::render() {
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);

    maze->draw();  // Draw the maze
    pacMan->draw();  // Draw Pac-Man
    for (auto& ghost : ghosts) {
        ghost->draw();  // Draw each ghost
    }

    window.EndDrawing();
}

// Check for collisions between objects
void Game::checkCollisions() {
    // Collision detection logic
    for (auto& ghost : ghosts) {
        if (pacMan->checkCollision(*ghost)) {
            isRunning = false;  // Stop the game if Pac-Man collides with a ghost
        }
    }
}

// End the game
void Game::endGame() {
    // Display game over screen or perform clean-up tasks
    DrawText("Game Over!", window.GetWidth() / 2 - 100, window.GetHeight() / 2, 20, RED);
}

// Initialize game objects
void Game::initializeGameObjects() {
    maze = new Maze();  // Initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Initialize Pac-Man at the maze start
    ghosts.push_back(new Ghost(maze->getGhostStartX(), maze->getGhostStartY()));  // Initialize ghost(s)
}

