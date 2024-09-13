#include "Game.h"
#include "Screen.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

// Constructor
Game::Game() : window(1600, 900, "Super Pac-Man"), isRunning(true), maze(nullptr), pacMan(nullptr), dir(0), frame(0) {
    
}
// Destructor
Game::~Game() {
    // Clean up dynamically allocated memory
    delete maze;
    delete pacMan;
}

void Game::initialize() {
    initializeGameObjects();
    pacMan->initilisePacManImages();
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        screen->startScreen();
    }

    if (IsKeyPressed(KEY_ENTER)) {
        std::cout << "Enter pressed, starting game..." << std::endl;
    }

    if (window.ShouldClose()) {
        std::cout << "Window close detected" << std::endl;
        isRunning = false;
    }
}

// Main game loop
void Game::run() {
    int pixelX;
    int pixelY;

    while (isRunning && !window.ShouldClose()) {
        handleInput();   // Handle user input
        update();        // Update game state
        screen->render();        // Render the game
        screen->drawMaze(*maze);
        //maze->draw();  // Draw the maze (based on tile grid)
        frame = pacMan->location(frame, dir);  //
        screen->drawPacMan(*pacMan, frame, dir);    
    }
    isRunning = screen->endGame();  // End the game
}

void Game::handleInput() {
    if (IsKeyDown(KEY_ESCAPE)) {
        isRunning = false;  // Exit the game loop immediately
        return;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        dir = 1;
    } else if (IsKeyPressed(KEY_LEFT)) {
        dir = 2;
    } else if (IsKeyPressed(KEY_UP)) {
        dir = 3;
    } else if (IsKeyPressed(KEY_DOWN)) {
        dir = 4;
    }
}

void Game::update() {
    float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
    pacMan->move(*maze, deltaTime, dir);  // Update Pac-Man's position
    //checkCollisions();  // Check for collisions
}

// For checking collisions with ghosts later
// Maybe we should check pacman collisions here too
// void Game::checkCollisions() {
    
// }

// Initialize game objects
void Game::initializeGameObjects() {
    maze = new Maze();  // Initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Initialize Pac-Man at the maze start
}


