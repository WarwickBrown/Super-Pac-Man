#include "Game.h"
#include "Screen.h"
#include "Ghost.h"
#include "Star.h"
#include "Fruit.h"
#include "Lives.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <cmath>
#include <memory>

// Constructor - Initialises game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), direction(0), frame(0), gameWon(false) {}

// Destructor - Frees dynamically allocated memory for maze, pacMan, and screen
Game::~Game() = default;

// Function to initialise the game
void Game::initialise() {
    initialiseGameObjects();    // Initialises game objects (maze, pacMan, screen)
    initialiseFruits();
    initialiseKeys();
    inputStar();
    initialisePowerPellets();
    initialiseSuperPellets();
    maze->initialiseCustomWalls();

    score = std::make_unique<Score>("highscore.txt"); // Initialise the score object
    playerLives = std::make_unique<Lives>(3);

    // Display the start screen until the player presses ENTER or closes the window
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        screen->startScreen(this, screen.get(), *score); // Shows the start screen and passes the current game instance
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
        float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
        handleInput();   // Handle user input like key presses for movement
        update();        // Update game state (Pac-Man's position, etc.)
        screen->render(); // Render the current state of the game
        screen->drawMaze(*maze);  // Draw the maze
        screen->drawKeys(keys);
        frame = pacMan->location(frame);  // Update Pac-Man's frame for animation
        screen->drawFruits(fruits, num3);
        screen->drawStars(stars);

        for (const auto& star : stars) {
            star->determineChange();  // Use the star object directly
        }

        screen->drawPowerPellets(powerPellets);
        screen->drawSuperPellets(superPellets);
        
        // Draw the fruits on the screen
        screen->drawScores(*score); // Draw the scores
        screen->drawLives(playerLives->getLives());

        for (const auto& ghost : ghosts) {
            screen->drawGhost(*ghost, *pacMan, ghostDirection);
        }

        if (pacMan->isSuper()) {
            screen->drawSuperPacMan(*pacMan, frame, oldDirection);
        }
        else{
            screen->drawPacMan(*pacMan, frame, oldDirection);  // Draw Pac-Man with its current frame and direction
        }
        // If the game has been won, break the loop
        if (gameWon) {
            break;
        }
    }

    // Save high score when the game ends
    score->saveHighScore();

    // If the game is won, show the win screen
    if (gameWon) {
        isRunning = screen->winGame(*score);
    } else {
        isRunning = screen->endGame(*score);
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
    if (!maze->isWallRec(newX, newY, 34)) {
        oldDirection = direction;
    }
    
    float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame
    // Update Pac-Man's invincibility timer
    pacMan->updateSuperMode(deltaTime);
    pacMan->updateInvincibility(deltaTime);
    pacMan->move(*maze, deltaTime, oldDirection);  // Move Pac-Man based on the direction and elapsed time

    updateFruits();
    // Check if all fruits have been collected
    checkWinCondition();
    updatePowerPellets();
    updateKeys();
    updateSuperPellets();
    updateInvincibility(deltaTime);
    updateStars();
}

void Game::updateStars(){
    float updatedTimer = GetTime() - timerStart;
    for (auto& stars : stars) {
            if((updatedTimer) >= 3*multi){
                num1 = rand()%6+1;
                num2 = rand()%6+1;
                multi++;
            }
            
            screen->drawSymbols(num1, num2);
            if((updatedTimer) >= 30*multi2)
            {
                stars->markAsNotEaten();
                stars->show();
                screen->setSymbolActive(true);
                totalFrames = 1;
                multi2++;
            }
            else
            {
                totalFrames++;
            }
        if (!stars->isEaten() && stars->isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-30,
                { (float)stars->getX(), (float)stars->getY() }, stars->getRadius())) {
                    if(num1 == num2 && num2 == num3)
                    {
                        score->addPoints(5000); // Add points for collecting a key
                    }
                    else if(num1 == num2)
                    {
                        score->addPoints(2000); // Add points for collecting a key
                    }
                    else{
                        score->addPoints(500); // Add points for collecting a key
                    }
            stars->collect();
            stars->markAsEaten();
            screen->setSymbolActive(false);
        }
    }
}

void Game::updateSuperPellets(){
    for (auto& superPellet : superPellets) {
        if (superPellet->isActive() && superPellet->checkCollision(pacMan->getX(), pacMan->getY(), pacMan->getRadius())) {
            superPellet->collect(); // Pac-Man collects the super pellet
            // Trigger super mode for Pac-Man (e.g., enlarge Pac-Man, increase speed, etc.)
            pacMan->activateSuperMode();
            score->addPoints(500); // Add points for collecting a super pellet
        }
    }

    // If Pac-Man is in super mode, check if he's moving through any locked walls
    if (pacMan->isSuper()) {
        for (auto& key : keys) {
            // Iterate through the walls that the key can unlock
            for (int wallIndex : key.getWallsToUnlock()) {
                Maze::Wall& wall = maze->getWalls()[wallIndex];  // Get the wall

                // Only proceed if the wall is still active (locked)
                if (wall.active) {
                    // Output Pac-Man and wall positions for debugging

                    // Define Pac-Man's bounding circle
                    Vector2 pacManCenter = { pacMan->getX(), pacMan->getY() };
                    float pacManRadius = pacMan->getRadius() * 1.1;

                    // Define the wall's rectangle
                    Rectangle wallRec = wall.rect;

                    // Check for a collision between Pac-Man's circle and the wall's rectangle
                    if (CheckCollisionCircleRec(pacManCenter, pacManRadius, wallRec)) {
                        wall.active = false;  // Unlock the wall (deactivate it)
                    }
                }
            }
        }
    }
}

void Game::updateFruits(){
    // Check if Pac-Man collects any fruits
    for (auto& fruit : fruits) {
        if (!fruit->isEaten() && fruit->isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-35,
                { (float)fruit->getX(), (float)fruit->getY() }, fruit->getRadius())) {
            fruit->collect();
            fruit->markAsEaten();
            score->addPoints(10); // Add points for collecting a fruit
        }
    }
}

void Game::updateKeys(){
    // Check if Pac-Man collects any keys
    for (auto& key : keys) {
        if (key.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius(),
                { static_cast<float>(key.getX()), static_cast<float>(key.getY()) }, key.getRadius())) {
            key.collect();
            score->addPoints(50); // Add points for collecting a key
            // Unlock associated walls
            for (int wallIndex : key.getWallsToUnlock()) {
                maze->getWalls()[wallIndex].active = false;
            }
        }
    }
}

void Game::updatePowerPellets(){
    // Check if Pac-Man collects any power pellets
    for (auto& pellet : powerPellets) {
        if (pellet->checkCollisionWithPacMan(*pacMan)) {
            score->addPoints(100);  // Add 100 points for eating a power pellet

            // Make ghosts frightened
            for (auto& ghost : ghosts) {
                ghost->setFrightened(true);
            }

            // Start a timer to end frightened mode after a certain time
            // You can manage this with a timer or frame counting
            powerPelletTimer = GetTime();  // Set the time when pellet is eaten
        }
    }

    // Revert ghosts to normal if the frightened mode time has expired
    if (GetTime() - powerPelletTimer > 5.0f) {  // For example, frightened lasts 5 seconds
        for (auto& ghost : ghosts) {
            ghost->setFrightened(false);  // Switch back to normal texture and mode
        }
    }
}

void Game::updateInvincibility(float deltaTime){
    if (!pacMan->isInvincible()) {
        for (const auto& ghost : ghosts) {
            int ghostDirection = ghost->move(*maze,*pacMan, deltaTime);
            // Check for collision with Pac-Man
            if (ghost->checkCollisionWithPacMan(*pacMan)) {
                if (ghost->isFrightened()) {
                    // Pac-Man eats the ghost
                    ghost->setEaten(true);  // Mark the ghost as eaten
                    ghost->respawn();       // Respawn the ghost at the center of the maze
                    score->addPoints(200); // Increase score for eating a ghost
                } 
                else if (pacMan->isSuper()) {
                    continue;
                }
                else {
                    // Pac-Man is hit by a non-frightened ghost
                    playerLives->loseLife(); // Deduct a life
                    for (const auto& ghost : ghosts) {
                        ghost->respawn();
                    }
                    if (!playerLives->isAlive()) {
                        // Game over
                        isRunning = false;
                        return;
                    }

                    // Make Pac-Man invincible for a short time to avoid losing multiple lives instantly
                    pacMan->setInvincible(true);
                    break; // Exit the loop if Pac-Man is hit, as we don't need to check other ghosts
                }
            }
        }
    }
    else {
        for (const auto& ghost : ghosts) {
            int ghostDirection = ghost->move(*maze,*pacMan, deltaTime);
        }
    }
}

// Initialises game objects like the maze, Pac-Man, and the screen
void Game::initialiseGameObjects() {
    maze = std::make_unique<Maze>();  // initialise using make_unique
    pacMan = std::make_unique<PacMan>(maze->getStartX(), maze->getStartY());
    screen = std::make_unique<Screen>();  // initialise the screen

    ghosts.push_back(std::make_unique<Ghost>(685, 445, 150.0f));
    ghosts.push_back(std::make_unique<Ghost>(765, 445, 150.0f));
    ghosts.push_back(std::make_unique<Ghost>(845, 445, 150.0f));
}

// initialise the fruits in the game
void Game::initialiseFruits() {
    //Left Long Wall
    num3 = rand()%6+1;
    fruits.emplace_back(std::make_unique<Fruit>(120, 360));
    fruits.emplace_back(std::make_unique<Fruit>(120, 440));
    fruits.emplace_back(std::make_unique<Fruit>(120, 520));
    fruits.emplace_back(std::make_unique<Fruit>(120, 600));

    //Right Long Wall
    fruits.emplace_back(std::make_unique<Fruit>(1400, 360));
    fruits.emplace_back(std::make_unique<Fruit>(1400, 440));
    fruits.emplace_back(std::make_unique<Fruit>(1400, 520));
    fruits.emplace_back(std::make_unique<Fruit>(1400, 600));

    //Bottom Left Small L
    fruits.emplace_back(std::make_unique<Fruit>(280, 600));
    fruits.emplace_back(std::make_unique<Fruit>(360, 600));
    fruits.emplace_back(std::make_unique<Fruit>(440, 600));
    fruits.emplace_back(std::make_unique<Fruit>(520, 600));
    fruits.emplace_back(std::make_unique<Fruit>(600, 680));

    //Bottom Right Small L
    fruits.emplace_back(std::make_unique<Fruit>(1000, 600));
    fruits.emplace_back(std::make_unique<Fruit>(1080, 600));
    fruits.emplace_back(std::make_unique<Fruit>(1160, 600));
    fruits.emplace_back(std::make_unique<Fruit>(1240, 600));
    fruits.emplace_back(std::make_unique<Fruit>(920, 680));

    //Bottom Left Big L
    fruits.emplace_back(std::make_unique<Fruit>(280, 200));
    fruits.emplace_back(std::make_unique<Fruit>(280, 280));
    fruits.emplace_back(std::make_unique<Fruit>(280, 360));
    fruits.emplace_back(std::make_unique<Fruit>(280, 440));
    fruits.emplace_back(std::make_unique<Fruit>(360, 440));
    fruits.emplace_back(std::make_unique<Fruit>(440, 440));
    fruits.emplace_back(std::make_unique<Fruit>(520, 440));

    //Bottom Right Big L
    fruits.emplace_back(std::make_unique<Fruit>(1240, 200));
    fruits.emplace_back(std::make_unique<Fruit>(1240, 280));
    fruits.emplace_back(std::make_unique<Fruit>(1240, 360));
    fruits.emplace_back(std::make_unique<Fruit>(1240, 440));
    fruits.emplace_back(std::make_unique<Fruit>(1000, 440));
    fruits.emplace_back(std::make_unique<Fruit>(1080, 440));
    fruits.emplace_back(std::make_unique<Fruit>(1160, 440));

    //Top Left Small L
    fruits.emplace_back(std::make_unique<Fruit>(440, 200));
    fruits.emplace_back(std::make_unique<Fruit>(440, 280));
    fruits.emplace_back(std::make_unique<Fruit>(520, 280));
    fruits.emplace_back(std::make_unique<Fruit>(600, 280));
    fruits.emplace_back(std::make_unique<Fruit>(680, 280));

    //Top Right Small L
    fruits.emplace_back(std::make_unique<Fruit>(1080, 200));
    fruits.emplace_back(std::make_unique<Fruit>(1080, 280));
    fruits.emplace_back(std::make_unique<Fruit>(840, 280));
    fruits.emplace_back(std::make_unique<Fruit>(920, 280));
    fruits.emplace_back(std::make_unique<Fruit>(1000, 280));

    //Upper Symbol
    fruits.emplace_back(std::make_unique<Fruit>(600, 120));
    fruits.emplace_back(std::make_unique<Fruit>(680, 120));
    fruits.emplace_back(std::make_unique<Fruit>(760, 120));
    fruits.emplace_back(std::make_unique<Fruit>(840, 120));
    fruits.emplace_back(std::make_unique<Fruit>(920, 120));

    //Bottom Left Small 
    fruits.emplace_back(std::make_unique<Fruit>(280, 760));
    fruits.emplace_back(std::make_unique<Fruit>(360, 760));
    fruits.emplace_back(std::make_unique<Fruit>(440, 760));

    //Bottom Right Small 
    fruits.emplace_back(std::make_unique<Fruit>(1080, 760));
    fruits.emplace_back(std::make_unique<Fruit>(1160, 760));
    fruits.emplace_back(std::make_unique<Fruit>(1240, 760));

    // Bottom T
    fruits.emplace_back(std::make_unique<Fruit>(600, 840));
    fruits.emplace_back(std::make_unique<Fruit>(920, 840));
    fruits.emplace_back(std::make_unique<Fruit>(840, 840));
    fruits.emplace_back(std::make_unique<Fruit>(760, 840));
    fruits.emplace_back(std::make_unique<Fruit>(680, 840));
    fruits.emplace_back(std::make_unique<Fruit>(760, 760));
}

void Game::initialisePowerPellets() {
    powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 760)); 
    powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 760)); 
    powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 200)); 
    powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 200)); 
}

void Game::initialiseSuperPellets() {
    superPellets.emplace_back(std::make_unique<SuperPellet>(600, 600));
    superPellets.emplace_back(std::make_unique<SuperPellet>(920, 600));
}

void Game::initialiseKeys() {
    // Top Left Box
    keys.emplace_back(40, 120, std::vector<int>{0, 1, 2, 3});
    // Top Right Box
    keys.emplace_back(1480, 120, std::vector<int>{4, 5, 6, 7});
    // Bottom Left
    keys.emplace_back(40, 840, std::vector<int>{8, 9, 10 , 11});
    // Bottom Right Box
    keys.emplace_back(1480, 840, std::vector<int>{12, 13, 14, 15});
    //Left Long Wall
    keys.emplace_back(40, 440, std::vector<int>{16, 17 , 18, 19});
    //Right Long Wall
    keys.emplace_back(1480, 440, std::vector<int>{20, 21, 22, 23});
    // Big L Left
    keys.emplace_back(360, 360, std::vector<int>{24, 25, 26, 27});
    // Big L Right
    keys.emplace_back(1160, 360, std::vector<int>{28, 29, 30, 31});
    // Left Top Small L
    keys.emplace_back(520, 200, std::vector<int>{32, 33, 34, 35});
    // Right Top Small L
    keys.emplace_back(1000, 200, std::vector<int>{36, 37, 38, 39});
    // Upper Symbol
    keys.emplace_back(760, 280, std::vector<int>{40, 41, 42, 43});
    // Left Bottom Small L 
    keys.emplace_back(280, 520, std::vector<int>{44, 45, 48, 49});
    // Right Bottom Small L 
    keys.emplace_back(1240, 520, std::vector<int>{50, 51, 54, 55});
    // Bottom Left Short 
    keys.emplace_back(360, 680, std::vector<int>{56, 57, 58, 59});
    // Bottom Right Short
    keys.emplace_back(1160, 680, std::vector<int>{60, 61, 62, 63});
    // Bottom T-Shaped 
    keys.emplace_back(760, 680, std::vector<int>{64, 65, 66, 67});
    keys.emplace_back(680, 760, std::vector<int>{46, 47, 68, 69});
    keys.emplace_back(840, 760, std::vector<int>{52, 53, 70, 71});
}

// Implement the method to check if all fruits are collected
void Game::checkWinCondition() {
    for (const auto& fruit : fruits) {
        if (fruit->isActive()) {
            return;  // If any fruit is still active, return early
        }
    }
    // If all fruits are collected, set gameWon to true
    gameWon = true;
    isRunning = false;  // Stop the game loop
}

void Game::inputStar() {
    stars.emplace_back(std::make_unique<Star>(760, 600));
}