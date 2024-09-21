#include "Game.h"
#include "Screen.h"
#include "Ghost.h"
#include "Star.h"
#include "Fruit.h"
#include "Lives.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <cmath>

// Constructor - Initializes game window, running state, and sets pointers to nullptr
Game::Game() : isRunning(true), maze(nullptr), pacMan(nullptr), direction(0), frame(0), gameWon(false), score(nullptr), playerLives(nullptr) {}

// Destructor - Frees dynamically allocated memory for maze, pacMan, and screen
Game::~Game() {
    // Clean up dynamically allocated memory
    delete maze;
    delete pacMan;
    delete screen;
    delete score;
    delete playerLives;
}

// Function to initialize the game
void Game::initialise() {
    initialiseGameObjects();    // Initializes game objects (maze, pacMan, screen)
    initiliseGameImages();      // Initializes game images like arrow keys
    initialiseFruits();
    initialiseKeys();
    inputStar();
    initialisePowerPellets();
    initialiseSuperPellets();
    pacMan->initilisePacManImages(); // Loads Pac-Man images

    score = new Score("highscore.txt"); // Initialize the score object
    playerLives = new Lives(3);

    // Display the start screen until the player presses ENTER or closes the window
    while (!IsKeyPressed(KEY_ENTER) && !window.ShouldClose()) {
        screen->startScreen(this, screen, *score); // Shows the start screen and passes the current game instance
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
    int addedFrame = 1;

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

        // Draw each star on the screen
        for (const auto& star : stars) {
            star.draw(addedFrame);
        }

        for (const auto& pellet : powerPellets) {
            pellet.draw();
        }
                // Render and check for SuperPellet collisions
        for (auto& superPellet : superPellets) {
            superPellet.draw();  // Draw the super pellet
            if (superPellet.isActive() && superPellet.checkCollision(pacMan->getX(), pacMan->getY(), pacMan->getRadius())) {
                superPellet.collect(); // Pac-Man collects the super pellet
                // Trigger super mode for Pac-Man (e.g., enlarge Pac-Man, increase speed, etc.)
                pacMan->activateSuperMode();
                score->addPoints(500); // Add points for collecting a super pellet
            }
        }
        
        addedFrame += frame;
        screen->drawInner();
        // Draw the fruits on the screen
        screen->drawScores(*score); // Draw the scores
        screen->drawLives(playerLives->getLives());
        
         
        
        if (pacMan->isSuper()) {
            screen->drawSuperPacMan(*pacMan, frame, oldDirection);
        }
        else{
            screen->drawPacMan(*pacMan, frame, oldDirection);  // Draw Pac-Man with its current frame and direction
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
    float newTimer = GetTime();
    float updatedTimer = newTimer - timerStart;
    int updateFrames = GetFrameTime();
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

    // Check if Pac-Man collects any fruits
    for (auto& fruit : fruits) {
        if (!fruit.isEaten() && fruit.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-35,
                { (float)fruit.getX(), (float)fruit.getY() }, fruit.getRadius())) {
            fruit.collect();
            fruit.markAsEaten();
            score->addPoints(10); // Add points for collecting a fruit
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
            score->addPoints(50); // Add points for collecting a key
            // Unlock associated walls
            for (int wallIndex : key.getWallsToUnlock()) {
                maze->getWalls()[wallIndex].active = false;
            }
        }
    }

    // Check if Pac-Man collects any power pellets
    for (auto& pellet : powerPellets) {
        if (pellet.checkCollisionWithPacMan(*pacMan)) {
            score->addPoints(100);  // Add 100 points for eating a power pellet

            // Make ghosts frightened
            for (auto& ghost : ghosts) {
                ghost.setFrightened(true);
            }

            // Start a timer to end frightened mode after a certain time
            // You can manage this with a timer or frame counting
            powerPelletTimer = GetTime();  // Set the time when pellet is eaten
        }
    }

    // Revert ghosts to normal if the frightened mode time has expired
    if (GetTime() - powerPelletTimer > 5.0f) {  // For example, frightened lasts 5 seconds
        for (auto& ghost : ghosts) {
            ghost.setNormal();  // Switch back to normal texture and mode
        }
    }

    // If Pac-Man is in super mode, check if he's moving through any locked walls
    if (pacMan->isSuper()) {
        for (auto& key : keys) {
            // Iterate through the walls that the key can unlock
            for (int wallIndex : key.getWallsToUnlock()) {
                Wall& wall = maze->getWalls()[wallIndex];  // Get the wall

                // Only proceed if the wall is still active (locked)
                if (wall.active) {
                    // Output Pac-Man and wall positions for debugging

                    // Define Pac-Man's bounding circle
                    Vector2 pacManCenter = { pacMan->getX(), pacMan->getY() };
                    float pacManRadius = pacMan->getRadius() * 1.5;

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


    if (!pacMan->isInvincible()) {
    for (auto& ghost : ghosts) {
        int ghostDirection = ghost.move(*maze, deltaTime);
        screen->drawGhost(ghost, *pacMan, ghostDirection);

        // Check for collision with Pac-Man
        if (ghost.checkCollisionWithPacMan(*pacMan)) {
            if (ghost.isFrightened()) {
                // Pac-Man eats the ghost
                ghost.setEaten(true);  // Mark the ghost as eaten
                ghost.respawn();       // Respawn the ghost at the center of the maze
                score->addPoints(200); // Increase score for eating a ghost
            } 
            else if (pacMan->isSuper()) {
                continue;
            }
            else {
                // Pac-Man is hit by a non-frightened ghost
                playerLives->loseLife(); // Deduct a life

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
    } else {
        // Even if Pac-Man is invincible, still update ghosts
        for (auto& ghost : ghosts) {
            int ghostDirection = ghost.move(*maze, deltaTime);
            screen->drawGhost(ghost, *pacMan, ghostDirection);
        }
    }


    for (auto& stars : stars) {
            if((updatedTimer) >= 0.5*multi){
                num1 = rand()%6+1;
                num2 = rand()%6+1;
                num3 = rand()%6+1;
                multi++;
            }
            
            screen->symbols(num1, num2, num3);
            if((updatedTimer) >= 30*multi2)
            {
                stars.markAsNotEaten();
                stars.show();
                screen->setSymbolActive(true);
                totalFrames = 1;
                multi2++;
            }
            else
            {
                totalFrames++;
            }
        if (!stars.isEaten() && stars.isActive() && CheckCollisionCircles(
                { pacMan->getX(), pacMan->getY() }, pacMan->getRadius()-30,
                { (float)stars.getX(), (float)stars.getY() }, stars.getRadius())) {
                    if(num1 == num2 && num2 == num3)
                    {
                        score->addPoints(5000); // Add points for collecting a key
                    }
                    else if(num1 == num2 || num2 == num3 || num1 == num3)
                    {
                        score->addPoints(2000); // Add points for collecting a key
                    }
                    else{
                        score->addPoints(500); // Add points for collecting a key
                    }
            stars.collect();
            stars.markAsEaten();
            screen->setSymbolActive(false);
            
            // Increase score or trigger other game events
        }
    }
    
}


// Initializes game objects like the maze, Pac-Man, and the screen
void Game::initialiseGameObjects() {
    maze = new Maze();  // Create and initialize the maze
    pacMan = new PacMan(maze->getStartX(), maze->getStartY());  // Create and initialize Pac-Man at the starting position
    screen = new Screen(); // Create and initialize the screen

    ghosts.push_back(Ghost(685, 445, 150.0f));
    ghosts.push_back(Ghost(765, 445, 150.0f));
    ghosts.push_back(Ghost(845, 445, 150.0f));
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



    //Left Long Wall
    fruits.emplace_back(120, 360, fruitTexture);
    fruits.emplace_back(120, 440, fruitTexture);
    fruits.emplace_back(120, 520, fruitTexture);
    fruits.emplace_back(120, 600, fruitTexture);

    //Right Long Wall
    fruits.emplace_back(1400, 360, fruitTexture);
    fruits.emplace_back(1400, 440, fruitTexture);
    fruits.emplace_back(1400, 520, fruitTexture);
    fruits.emplace_back(1400, 600, fruitTexture);

    //Bottom Left Small L
    fruits.emplace_back(280, 600, fruitTexture);
    fruits.emplace_back(360, 600, fruitTexture);
    fruits.emplace_back(440, 600, fruitTexture);
    fruits.emplace_back(520, 600, fruitTexture);
    fruits.emplace_back(600, 680, fruitTexture);

    //Bottom Right Small L
    fruits.emplace_back(1000, 600, fruitTexture);
    fruits.emplace_back(1080, 600, fruitTexture);
    fruits.emplace_back(1160, 600, fruitTexture);
    fruits.emplace_back(1240, 600, fruitTexture);
    fruits.emplace_back(920, 680, fruitTexture);

    //Bottom Left Big L
    fruits.emplace_back(280, 200, fruitTexture);
    fruits.emplace_back(280, 280, fruitTexture);
    fruits.emplace_back(280, 360, fruitTexture);
    fruits.emplace_back(280, 440, fruitTexture);
    fruits.emplace_back(360, 440, fruitTexture);
    fruits.emplace_back(440, 440, fruitTexture);
    fruits.emplace_back(520, 440, fruitTexture);

    //Bottom Right Big L
    fruits.emplace_back(1240, 200, fruitTexture);
    fruits.emplace_back(1240, 280, fruitTexture);
    fruits.emplace_back(1240, 360, fruitTexture);
    fruits.emplace_back(1240, 440, fruitTexture);
    fruits.emplace_back(1000, 440, fruitTexture);
    fruits.emplace_back(1080, 440, fruitTexture);
    fruits.emplace_back(1160, 440, fruitTexture);

    //Top Left Small L
    fruits.emplace_back(440, 200, fruitTexture);
    fruits.emplace_back(440, 280, fruitTexture);
    fruits.emplace_back(520, 280, fruitTexture);
    fruits.emplace_back(600, 280, fruitTexture);
    fruits.emplace_back(680, 280, fruitTexture);

    //Top Right Small L
    fruits.emplace_back(1080, 200, fruitTexture);
    fruits.emplace_back(1080, 280, fruitTexture);
    fruits.emplace_back(840, 280, fruitTexture);
    fruits.emplace_back(920, 280, fruitTexture);
    fruits.emplace_back(1000, 280, fruitTexture);

    //Upper Symbol
    fruits.emplace_back(600, 120, fruitTexture);
    fruits.emplace_back(680, 120, fruitTexture);
    fruits.emplace_back(840, 120, fruitTexture);
    fruits.emplace_back(920, 120, fruitTexture);

    //Bottom Left Small 
    fruits.emplace_back(280, 760, fruitTexture);
    fruits.emplace_back(360, 760, fruitTexture);
    fruits.emplace_back(440, 760, fruitTexture);

    //Bottom Right Small 
    fruits.emplace_back(1080, 760, fruitTexture);
    fruits.emplace_back(1160, 760, fruitTexture);
    fruits.emplace_back(1240, 760, fruitTexture);

    // Bottom T
    fruits.emplace_back(600, 840, fruitTexture);
    fruits.emplace_back(920, 840, fruitTexture);
    fruits.emplace_back(840, 840, fruitTexture);
    fruits.emplace_back(760, 840, fruitTexture);
    fruits.emplace_back(680, 840, fruitTexture);
    fruits.emplace_back(760, 760, fruitTexture);
}

void Game::initialiseKeys() {
   // Texture2D keyTexture = LoadTexture("../resources/pacman-images/key.png");

    keys.emplace_back(40, 120, std::vector<int>{0, 1, 2, 3});
    keys.emplace_back(1480, 120, std::vector<int>{4, 5, 6, 7});
    keys.emplace_back(40, 840, std::vector<int>{8, 9, 10 , 11});
    keys.emplace_back(1480, 840, std::vector<int>{12, 13, 14, 15});
    keys.emplace_back(360, 360, std::vector<int>{16, 17, 18, 19});
    keys.emplace_back(1160, 360, std::vector<int>{20, 21, 22, 23});
    keys.emplace_back(520, 680, std::vector<int>{24, 25, 26, 27});
    keys.emplace_back(1000, 680, std::vector<int>{28, 29, 30, 31});
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

void Game::inputStar() {
    // Load star texture (replace with the correct path)
    std::vector<Texture2D> starImage;
    starImage.push_back(LoadTexture("../resources/pacman-images/star1.png"));
    starImage.push_back(LoadTexture("../resources/pacman-images/star2.png"));
    starImage.push_back(LoadTexture("../resources/pacman-images/star3.png"));
    stars.emplace_back(760, 600, starImage);
}

void Game::initialisePowerPellets() {
    // Add power pellets at specific locations
    powerPellets.emplace_back(120, 760); 
    powerPellets.emplace_back(1400, 760); 
    powerPellets.emplace_back(120, 200); 
    powerPellets.emplace_back(1400, 200); 
}

void Game::initialiseSuperPellets() {
    superPellets.emplace_back(600, 600); // Add super pellets at specific coordinates
    superPellets.emplace_back(920, 600); // Add more as needed
}

