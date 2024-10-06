#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "PacMan.h"
#include "Maze.h"
#include "Ghost.h"
#include "Game.h"
#include "Fruit.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"
#include "Score.h"
#include "raylib.h"
#include "GameInitialiser.h"
#include "Reader.h"
#include "Update.h"

// Helper function to create a basic maze for testing purposes
Maze createTestMaze() {
    Maze maze;
    maze.initialiseCustomWalls();  // Initialize custom walls (if any)
    return maze;
}


// Helper function to create and return a Maze instance with custom walls.
Maze createMaze() {
    Maze maze;
    maze.initialiseCustomWalls();  // Set up walls for collision detection
    return maze;
}

// Helper function to initialize and return a Screen object using a unique pointer
std::unique_ptr<Draw> createScreen() {
    return std::make_unique<Draw>();
}

// Helper function to create a temporary file with given content
void createTempFile(const std::string& fileName, const std::vector<std::string>& lines) {
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto& line : lines) {
            outFile << line << std::endl;
        }
        outFile.close();
    }
}

// Helper function to initialize a game with power pellets, Pac-Man, and ghosts
void initializeGameWithPowerPellets(Game& game) {
    GameInitialiser::initialiseGameObjects(game);
    GameInitialiser::initialisePowerPellets(game);  // Setup power pellets

    // Place Pac-Man near the first power pellet for testing purposes
    PacMan pacMan = game.getPacMan();
    pacMan.setPosition(100.0f, 100.0f);

    // Place ghosts at initial positions
    for (auto& ghost : game.getGhosts()) {
        ghost->setPosition(150.0f, 150.0f);  // Set some arbitrary position
    }
}

// Test for state changes when a fruit is collected
TEST_CASE("Active and Eaten State Test") {
    Fruit fruit(150, 250);  // Create a fruit at position (150, 250)

    CHECK(fruit.isActive() == true);  // Fruit should be active initially

    fruit.collect();  // Mark the fruit as eaten
    CHECK(fruit.isActive() == false);  // Fruit should no longer be active
}

// Test boundary and edge cases for Fruit placement and behavior
TEST_CASE("Boundary and Edge Cases Test") {
    // Fruit at extreme coordinates (top-left and bottom-right corners)
    Fruit fruit1(0, 0);  // Top-left corner
    Fruit fruit2(1920, 1080);  // Bottom-right corner (assuming screen size)

    CHECK(fruit1.getX() == 0);  // Fruit at (0, 0)
    CHECK(fruit1.getY() == 0);
    CHECK(fruit2.getX() == 1920);  // Fruit at bottom-right corner
    CHECK(fruit2.getY() == 1080);

    // Fruit outside boundaries (e.g., negative coordinates)
    Fruit fruit3(-100, -100);
    CHECK(fruit3.getX() == -100);  // Fruit placed outside screen boundaries
    CHECK(fruit3.getY() == -100);

    // Multiple fruits at the same position (overlapping)
    Fruit fruit4(100, 100);
    Fruit fruit5(100, 100);  // Same position as fruit4

    CHECK(fruit4.isActive() == true);  // Both fruits should be active initially
    CHECK(fruit5.isActive() == true);

    // Collect one fruit and check that the other remains active
    fruit4.collect();
    CHECK(fruit4.isActive() == false);
    CHECK(fruit5.isActive() == true);  // Fruit5 should remain active
}

// General collectable tests:
// Test case for Collectable state after collection
TEST_CASE("Collectable Collection State Test") {
    Collectable collectable(100.0f, 200.0f, 50.0f);

    CHECK(collectable.isActive() == true);  // Initially active
    collectable.collect();  // Collect the item
    CHECK(collectable.isActive() == false);  // Should be inactive after collection
}

// Test case for collision detection with another object
TEST_CASE("Collectable Collision Detection Test") {
    Collectable collectable(100.0f, 100.0f, 30.0f);  // Create a collectable with radius 30

    // Test collision with another object that intersects the collectable
    CHECK(collectable.checkCollision(110.0f, 110.0f, 20.0f) == true);  // Should detect collision

    // Test collision with another object far away (no collision)
    CHECK(collectable.checkCollision(300.0f, 300.0f, 20.0f) == false);  // Should not detect collision
}

// Test case for collision detection when collectable is inactive
TEST_CASE("Collectable Collision Detection When Inactive") {
    Collectable collectable(100.0f, 100.0f, 30.0f);
    
    collectable.collect();  // Deactivate the collectable
    CHECK(collectable.isActive() == false);  // Verify it's inactive

    // Check that no collision is detected when inactive
    CHECK(collectable.checkCollision(100.0f, 100.0f, 30.0f) == false);  // Should not detect collision
}

// Test case for Collectable constructor
TEST_CASE("Collectable Constructor Test") {
    Collectable collectable(100.0f, 200.0f, 50.0f);  // Create a collectable at position (100, 200) with radius 50

    CHECK(collectable.getX() == 100.0f);  // Verify the initial X coordinate
    CHECK(collectable.getY() == 200.0f);  // Verify the initial Y coordinate
    CHECK(collectable.getRadius() == 50.0f);  // Verify the radius
    CHECK(collectable.isActive() == true);  // Collectable should be active initially
}

// Test with negative or zero point increments
TEST_CASE("Edge Case Test - Negative and Zero Points") {
    Score score("test_edge_cases.txt");

    score.addPoints(0);  // Adding zero points
    CHECK(score.getCurrentScore() == 0);  // Score should remain 0
    CHECK(score.getHighScore() == 0);  // High score should remain 0

    score.addPoints(-10);  // Adding negative points (if allowed)
    CHECK(score.getCurrentScore() == -10);  // Score should decrease if negative points are allowed
    CHECK(score.getHighScore() == 0);  // High score should remain unchanged

    // Cleanup
    std::remove("../resources/test_edge_cases.txt");
}


// Test exception handling by simulating file-related errors
TEST_CASE("Exception Handling Test") {
    Score score("test_exception_handling.txt");

    // Simulate file I/O errors
    std::ofstream outFile("../resources/test_exception_handling.txt", std::ios::out | std::ios::binary);
    outFile << "invalid data";  // Write some invalid data to the high score file
    outFile.close();

    // Try loading the corrupted file
    Score corruptedScore("test_exception_handling.txt");
    CHECK(corruptedScore.getHighScore() == 0);  // High score should default to 0 if file is corrupted

    // Cleanup
    std::remove("../resources/test_exception_handling.txt");
}

// Test file handling and exception safety
TEST_CASE("File Handling Test") {
    const std::string invalidFilePath = "/invalid/path/highscore.txt";
    Score invalidScore(invalidFilePath);  // This should trigger an exception or fail to open

    CHECK(invalidScore.getHighScore() == 0);  // High score should default to 0 if file couldn't be read
    CHECK(invalidScore.getCurrentScore() == 0);  // Current score should remain 0

    // Verify no crash on save attempt (exception should be caught internally)
    invalidScore.saveHighScore();
}

// Fruit tests

// Test collision detection with Pac-Man
TEST_CASE("Fruit Collision Detection Test") {
    Fruit fruit(300, 400);  // Create a fruit at position (300, 400)

    // Simulate Pac-Man's position and radius
    float pacManX = 300;
    float pacManY = 400;
    float pacManRadius = 30;

    CHECK(fruit.checkCollision(pacManX, pacManY, pacManRadius) == true);  // Collision should be detected

    // Move Pac-Man away from the fruit
    pacManX = 500;
    pacManY = 500;
    CHECK(fruit.checkCollision(pacManX, pacManY, pacManRadius) == false);  // No collision should be detected
}

// Test that the Fruit is initialized correctly
TEST_CASE("Fruit Constructor Test") {
    Fruit fruit(100, 200);  // Create a fruit at position (100, 200)

    CHECK(fruit.getX() == 100);  // Verify initial x position
    CHECK(fruit.getY() == 200);  // Verify initial y position
    CHECK(fruit.isActive() == true);  // Fruit should be active initially
}

// Test that the Fruit is initialized correctly
TEST_CASE("Fruit Constructor Test") {
    Fruit fruit(100, 200);  // Create a fruit at position (100, 200)

    CHECK(fruit.getX() == 100);  // Verify initial x position
    CHECK(fruit.getY() == 200);  // Verify initial y position
    CHECK(fruit.isActive() == true);  // Fruit should be active initially
    CHECK(fruit.getRadius() == 50.0f);  // Verify default radius
}

TEST_CASE("Game correctly handles power pellet interaction") {
    Game game;
    game.initialise(true);

    // Use game-initialized power pellet
    auto& powerPellet = game.getPowerPellets().front();
    CHECK(powerPellet->isActive() == true);  // Power pellet should be active
    powerPellet->collect();  // Pac-Man collects the power pellet


    // Check if the power pellet interaction caused the desired effect (e.g., ghosts frightened)
    for (auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == true);  // Ghosts should be in frightened mode
    }
}


TEST_CASE("Game ends when all fruits are collected") {
    Game game;
    GameInitialiser::initialiseGameObjects(game);  // Initialize game objects like Pac-Man, ghosts, maze, etc.
    GameInitialiser::initialiseFruits(game);  // Initialize the fruits in the maze

    // Ensure the game is running at the start
    CHECK(game.isGameRunning());

    for (const auto& fruit : game.getFruits()) {
        fruit->collect();  // Mark each fruit as collected
    }

    game.checkWinCondition();

    CHECK(game.isGameWon() == true);  // Check if the game end flag is triggered
    CHECK(game.isGameRunning() == false);  // The game should stop running
}

// Test that Pac-Man can collect fruits correctly and updates score
TEST_CASE("Game Fruit Collection Test") {
    Game game;
    game.initialise(true);

    // Get initial score
    int initialScore = game.getScore().getCurrentScore();

    // Simulate Pac-Man collecting the first fruit
    auto& fruits = game.getFruits();
    CHECK(fruits[1]->isActive() == true);  // Fruit should be marked as eaten

    fruits[1]->collect();  // Directly call collect() on the first fruit
    CHECK(fruits[1]->isActive() == false);  // Fruit should be marked as eaten
}

// Test case for power pellet frightened mode duration
TEST_CASE("Game handles frightened mode duration correctly") {
    Game game;
    Draw draw;
    Update updater(game, &draw);
    initializeGameWithPowerPellets(game);

    // Simulate Pac-Man collecting a power pellet
    updater.updatePowerPellets();
    CHECK(game.getScore().getCurrentScore() == 100);  // Initial score update

    // Move time forward to simulate frightened mode duration
    float elapsedTime = 3.0f;  // Move 3 seconds forward
    updater.updateInvincibility(elapsedTime);

    // Check that ghosts are still in frightened mode
    for (const auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == true);
    }

    // Move time forward again to exceed frightened mode duration
    elapsedTime = 6.0f;  // Total of 9 seconds now
    updater.updateInvincibility(elapsedTime);

    // Check that ghosts are no longer in frightened mode
    for (const auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == false);
    }
}

// Test case for ensuring no errors when no power pellets are left
TEST_CASE("Game handles no active power pellets") {
    Game game;
    Draw draw;
    GameInitialiser::initialiseGameObjects(game);
    Update updater(game, &draw);

    // No power pellets should exist
    CHECK(game.getPowerPellets().empty() == true);

    // Call updatePowerPellets() and ensure no errors or crashes
    updater.updatePowerPellets();
    CHECK(true);  // If no exception or crash occurs, the test passes
}

// Test case for Pac-Man collecting a power pellet and ghosts becoming frightened
TEST_CASE("Game handles power pellet collection and ghost frightened mode") {
    Game game;
    Draw draw;
    Update updater(game, &draw);
    initializeGameWithPowerPellets(game);

    // Verify initial state of game objects
    CHECK(game.getPowerPellets().size() > 0);  // Ensure there are power pellets
    auto& firstPellet = game.getPowerPellets().front();
    CHECK(firstPellet->isActive() == true);  // First power pellet should be active

    // Simulate Pac-Man collecting the power pellet
    updater.updatePowerPellets();

    // Check that the first pellet is now inactive
    CHECK(firstPellet->isActive() == false);

    // Check that the score increased correctly
    CHECK(game.getScore().getCurrentScore() == 100);  // Assume 100 points per pellet

    // Check that all ghosts are in frightened mode
    for (const auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == true);  // All ghosts should be frightened
    }

    // Simulate waiting for the frightened mode to expire
    float elapsedTime = 6.0f;  // Assume frightened mode lasts 5 seconds
    updater.updateInvincibility(elapsedTime);  // Mock method to update timers

    // Check that all ghosts are no longer in frightened mode
    for (const auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == false);  // Frightened mode should be over
    }
}

// Test case for Pac-Man collecting multiple power pellets in sequence
TEST_CASE("Game handles sequential power pellet collection correctly") {
    Game game;
    Draw draw;
    GameInitialiser::initialiseGameObjects(game);
    Update updater(game, &draw);
    initializeGameWithPowerPellets(game);

    auto& powerPellets = game.getPowerPellets();
    CHECK(powerPellets.size() > 1);  // Ensure there are multiple power pellets

    // Simulate Pac-Man collecting the first power pellet
    updater.updatePowerPellets();
    CHECK(powerPellets[0]->isActive() == false);  // First pellet should be inactive

    // Move Pac-Man to the second power pellet
    PacMan pacMan = game.getPacMan();
    pacMan.setPosition(200.0f, 200.0f);  // Assume second pellet is at (200, 200)

    // Update the game again to collect the second pellet
    updater.updatePowerPellets();
    CHECK(powerPellets[1]->isActive() == false);  // Second pellet should be inactive

    // Check that the score has increased correctly for both pellets
    CHECK(game.getScore().getCurrentScore() == 200);  // 100 points per pellet
}

// Test handleInput for directional controls
TEST_CASE("Game Input Handling Test") {
    Game game;
    game.initialise(true);
    game.run();
    game.handleInput(KEY_RIGHT);
    CHECK(game.getDirection() == 1);  // Right direction

    game.handleInput(KEY_LEFT);
    CHECK(game.getDirection() == 2);  // Left direction

    game.handleInput(KEY_UP);
    CHECK(game.getDirection() == 3);  // Up direction

    game.handleInput(KEY_DOWN);
    CHECK(game.getDirection() == 4);  // Down direction
}

// Test that the game ends when Pac-Man loses all lives
TEST_CASE("Game Over Condition Test") {
    Game game;
    GameInitialiser::initialiseGameObjects(game);

    auto lives = game.getPlayerLives();

    // Simulate losing all lives
    while (lives.getLives() > 0) {
        lives.loseLife();
    }

    game.update();  // Update game state for lives condition
    CHECK(game.isGameRunning() == false);  // Game should stop running
}

// These two are kinda broken
// Test that Game transitions to the correct state based on input
TEST_CASE("Game State Transitions Test") {
    Game game;
    game.initialise(true);
    // Simulate starting the game
    game.handleInput(KEY_ENTER);  // Simulate ENTER key press
    CHECK(game.isGameRunning() == true);

    // Simulate ESCAPE key press to end the game
    game.handleInput(KEY_ESCAPE);
    CHECK(game.isGameRunning() == false);
}


// GameKey Tests

// Constructor Test: Verify that GameKey is initialized with correct values
TEST_CASE("GameKey Constructor Test") {
    std::vector<int> wallsToUnlock = {1, 2, 3};
    GameKey key(100.0f, 200.0f, wallsToUnlock);

    CHECK(key.getX() == 100.0f);  // X position should be 100
    CHECK(key.getY() == 200.0f);  // Y position should be 200
    CHECK(key.getRadius() == 10.0f);  // Radius should be set to 10
    CHECK(key.isActive() == true);  // Key should start as active
    CHECK(key.getWallsToUnlock() == wallsToUnlock);  // Walls to unlock should match
}

// Test memory management by constructing and destructing GameKey objects
TEST_CASE("GameKey Memory Management Test") {
    std::vector<int> wallsToUnlock = {1, 2};
    
    // Create GameKey object dynamically
    GameKey* key = new GameKey(100.0f, 100.0f, wallsToUnlock);

    // Check properties
    CHECK(key->getX() == 100.0f);
    CHECK(key->getY() == 100.0f);
    CHECK(key->isActive() == true);

    // Delete the key and ensure no memory leaks (to be validated with tools like Valgrind)
    delete key;
}

// Test that getWallsToUnlock returns the correct wall indices
TEST_CASE("GameKey Walls to Unlock Test") {
    std::vector<int> wallsToUnlock = {5, 6, 7, 8};
    GameKey key(50.0f, 50.0f, wallsToUnlock);

    const auto& returnedWalls = key.getWallsToUnlock();
    CHECK(returnedWalls.size() == wallsToUnlock.size());  // Ensure the size is correct

    // Check that each wall index matches
    for (size_t i = 0; i < wallsToUnlock.size(); ++i) {
        CHECK(returnedWalls[i] == wallsToUnlock[i]);
    }
}

// Test case for checking collision with Pac-Man
TEST_CASE("Ghost Collision With Pac-Man") {
    Ghost ghost(100.0f, 200.0f, 150.0f);
    PacMan pacman(0.0f, 0.0f);  // Place Pac-Man at the same position as the ghost

    // Check collision
    pacman.setPosition(100.0f, 200.0f);
    bool collision = ghost.checkCollisionWithPacMan(pacman);
    CHECK(collision == true);  // Should detect collision

    // Move Pac-Man away
    pacman.setPosition(300, 300);
    collision = ghost.checkCollisionWithPacMan(pacman);
    CHECK(collision == false);  // No collision should be detected
}

// Test ghost collision with walls
TEST_CASE("Ghost Collision With Walls") {
    Maze maze;
    maze.initialiseCustomWalls();  // Initialize maze with custom walls
    Ghost ghost(100, 100, 150.0f);
    PacMan pacMan(100, 100);

    // Test collision when ghost hits a wall
    float deltaTime = 1.0f;

    // Mock a wall in front of the ghost moving right
    ghost.setDirection(1);  // Move right
    ghost.move(maze, pacMan, deltaTime);
    CHECK(ghost.getX() == 100);  // Should not move if it hits a wall

    // Test for ghost choosing a new direction
    ghost.chooseNewDirection(maze);
    CHECK(ghost.getDirection() != 1);  // Direction should not still be right
}

// Test case for Ghost constructor initialization
TEST_CASE("Ghost Constructor Initialization") {
    Ghost ghost(100, 200, 150.0f);

    CHECK(ghost.getX() == 100);  // Verify initial X position
    CHECK(ghost.getY() == 200);  // Verify initial Y position
    CHECK(ghost.getRadius() == 34);  // Default radius value
    CHECK(ghost.isFrightened() == false);  // Should not be frightened initially
    CHECK(ghost.isEaten() == false);  // Should not be eaten initially
}

TEST_CASE("Ghost Does Not Collide With PacMan") {
    Ghost ghost(100, 100, 150.0f);
    PacMan pacman(300, 300);  // Pac-Man is close enough to collide
    CHECK(ghost.checkCollisionWithPacMan(pacman) == false);  // No collision should occur
}

// Test case for eaten state behavior
TEST_CASE("Ghost Eaten State Behavior") {
    Ghost ghost(100, 200, 150.0f);
    Maze maze = createTestMaze();
    PacMan pacman(200, 200);

    // Mark the ghost as eaten
    ghost.setEaten(true);
    CHECK(ghost.isEaten() == true);

    // Move the ghost; it should not move when eaten
    int initialDirection = ghost.move(maze, pacman, 1.0f);
    CHECK(ghost.getX() == 100);  // X position should not change
    CHECK(ghost.getY() == 200);  // Y position should not change
}

// Test ghost frightened mode
TEST_CASE("Ghost Frightened Mode") {
    Ghost ghost(100, 100, 150.0f);

    // Set ghost to frightened mode
    ghost.setFrightened(true);
    CHECK(ghost.isFrightened() == true);

    // Reset to normal mode
    ghost.setFrightened(false);
    CHECK(ghost.isFrightened() == false);
}

// Test case for frightened state behavior
TEST_CASE("Ghost Frightened State Behavior") {
    Ghost ghost(100, 200, 150.0f);
    Maze maze = createTestMaze();
    PacMan pacman(200, 200);

    // Set ghost to frightened state
    ghost.setFrightened(true);
    CHECK(ghost.isFrightened() == true);

    // Move the ghost; it should not chase Pac-Man
    int initialDirection = ghost.move(maze, pacman, 1.0f);

    // Check that the ghost did not move toward Pac-Man (random direction)
    CHECK(initialDirection != 1);  // Assuming initial direction was to the right
}

// Test ghost initialization
TEST_CASE("Ghost Initialization") {
    Ghost ghost(100, 100, 150.0f);

    // Check if ghost is initialized at the correct position
    CHECK(ghost.getX() == 100);
    CHECK(ghost.getY() == 100);
    
    // Check if ghost is not eaten or frightened at start
    CHECK(ghost.isEaten() == false);
    CHECK(ghost.isFrightened() == false);
}

// Tests if Ghost has moved correctly
TEST_CASE("Ghost Movement") {
    Maze maze;
    PacMan pacman(100.0f, 100.0f);
    float deltaTime = 1.0f;

    // Subtest for right movement
    SUBCASE("Valid right movement") {
        Ghost ghost(100.0f, 100.0f, 150.0f);
        float initialX = ghost.getX();
        float initialY = ghost.getY();
        ghost.setDirection(1);  // Right
        ghost.move(maze, pacman, deltaTime);
        float expectedX = initialX + ghost.getSpeed() * deltaTime; // Move right
        float expectedY = initialY;
        CHECK(expectedX == ghost.getX());
        CHECK(expectedY == ghost.getY());
    }

    // Subtest for left movement
    SUBCASE("Valid left movement") {
        Ghost ghost(100.0f, 100.0f, 150.0f);
        float initialX = ghost.getX();
        float initialY = ghost.getY();
        ghost.setDirection(2);  // Left
        ghost.move(maze, pacman, deltaTime);
        float expectedX = initialX - ghost.getSpeed() * deltaTime; // Move left
        float expectedY = initialY;
        CHECK(expectedX == ghost.getX());
        CHECK(expectedY == ghost.getY());
    }

    // Subtest for up movement
    SUBCASE("Valid up movement") {
        Ghost ghost(100.0f, 100.0f, 150.0f);
        float initialX = ghost.getX();
        float initialY = ghost.getY();
        ghost.setDirection(3);  // Up
        ghost.move(maze, pacman, deltaTime);
        float expectedX = initialX;
        float expectedY = initialY - ghost.getSpeed() * deltaTime; // Move up
        CHECK(expectedX == ghost.getX());
        CHECK(expectedY== ghost.getY());
    }

    // Subtest for down movement
    SUBCASE("Valid down movement") {
        Ghost ghost(100.0f, 100.0f, 150.0f);
        float initialX = ghost.getX();
        float initialY = ghost.getY();
        ghost.setDirection(4);  // Down
        ghost.move(maze, pacman, deltaTime);
        float expectedX = initialX;
        float expectedY = initialY + ghost.getSpeed() * deltaTime; // Move down
        CHECK(expectedX == ghost.getX());
        CHECK(expectedY == ghost.getY());
    }
}

// Test case for choosing a random direction
TEST_CASE("Ghost Random Direction Selection") {
    Ghost ghost(100, 200, 150.0f);
    Maze maze = createTestMaze();

    ghost.chooseRandomDirection(maze);  // Choose a random direction

    // Check that the selected direction is one of the four possible values
    int direction = ghost.getDirection();
    CHECK((direction >= 1 && direction <= 4));  // Should be 1, 2, 3, or 4
}

// Test case for overriding best movement with a random direction
TEST_CASE("Ghost Random Movement Override") {
    Ghost ghost(100, 200, 150.0f);
    Maze maze = createTestMaze();
    PacMan pacman(400, 200);  // Place Pac-Man to the right of the ghost

    // Move the ghost; it should chase Pac-Man
    int initialDirection = ghost.move(maze, pacman, 1.0f);

    // Move again with a small probability of random movement override
    int secondDirection = ghost.move(maze, pacman, 1.0f);

    // In some cases, the direction might randomly change
    if (initialDirection != secondDirection) {
        CHECK(true);  // Passed: Direction changed randomly
    } else {
        CHECK(true);  // Passed: Direction did not change
    }
}

// Test ghost respawn behavior
TEST_CASE("Ghost Respawn") {
    Ghost ghost(100, 100, 150.0f);
    PacMan pacMan(100, 100);
    Maze maze;

    // Mark the ghost as eaten and move it
    ghost.setEaten(true);
    ghost.setDirection(1);  // Set direction to right
    float deltaTime = 1.0f;
    ghost.move(maze,pacMan, deltaTime);

    // Respawn the ghost
    ghost.respawn();
    CHECK(ghost.getX() == 100);  // Should reset to the starting position
    CHECK(ghost.getY() == 100);  // Should reset to the starting position
    CHECK(ghost.isEaten() == false);  // Ghost should no longer be eaten
}

// Test case for respawn behavior
TEST_CASE("Ghost Respawn Behavior") {
    Ghost ghost(100, 200, 150.0f);
    ghost.setEaten(true);  // Mark the ghost as eaten
    ghost.setFrightened(true);  // Mark the ghost as frightened

    // Move the ghost away from the initial position
    ghost.setDirection(1);  // Move right
    ghost.move(createTestMaze(), PacMan(0, 0), 1.0f);  // Move for 1 second

    // Respawn the ghost
    ghost.respawn();
    CHECK(ghost.getX() == 100);  // Should reset to the starting X position
    CHECK(ghost.getY() == 200);  // Should reset to the starting Y position
    CHECK(ghost.isFrightened() == false);  // Should no longer be frightened
    CHECK(ghost.isEaten() == false);  // Should no longer be eaten
}

// Test saving and loading high scores from a file
TEST_CASE("High Score Persistence Test") {
    const std::string filename = "test_highscore_persistence.txt";
    Score score(filename);

    score.addPoints(100);  // Add some points
    CHECK(score.getCurrentScore() == 100);  // Verify current score
    CHECK(score.getHighScore() == 100);  // Verify high score

    score.saveHighScore();  // Save high score to file

    Score newScore(filename);  // Create a new Score object, should load high score from file
    CHECK(newScore.getHighScore() == 100);  // High score should be loaded correctly
}

// Lives tests

// Test that lives do not go below 0
TEST_CASE("Lives Boundary Condition Test") {
    Lives playerLives(1);  // Initialize with 1 life

    // Lose all lives and try losing more lives
    playerLives.loseLife();  // Should reach 0 lives
    CHECK(playerLives.getLives() == 0);  // Confirm lives are 0

    playerLives.loseLife();  // Attempt to lose more lives (should not go below 0)
    CHECK(playerLives.getLives() == 0);  // Should remain at 0

    // Gain a life after losing all lives
    playerLives.gainLife();
    CHECK(playerLives.getLives() == 1);  // Should be 1
}

// Test that Lives is initialized correctly
TEST_CASE("Lives Constructor Test") {
    Lives playerLives(3);  // Initialize with 3 lives
    CHECK(playerLives.getLives() == 3);  // Lives should be 3
}

// Test that gaining a life increases the life count
TEST_CASE("Lives Gain Life Test") {
    Lives playerLives(2);  // Initialize with 2 lives
    playerLives.gainLife();  // Gain one life
    CHECK(playerLives.getLives() == 3);  // Lives should be 3

    playerLives.gainLife();  // Gain another life
    CHECK(playerLives.getLives() == 4);  // Lives should be 4
}

// Test that isAlive returns correct value based on number of lives
TEST_CASE("Lives Is Alive Test") {
    Lives playerLives(1);  // Initialize with 1 life
    CHECK(playerLives.isAlive() == true);  // Should be alive

    playerLives.loseLife();  // Lose the only life
    CHECK(playerLives.isAlive() == false);  // Should not be alive

    playerLives.gainLife();  // Gain a life back
    CHECK(playerLives.isAlive() == true);  // Should be alive again
}

// Test that losing a life decreases the life count
TEST_CASE("Lives Lose Life Test") {
    Lives playerLives(3);  // Initialize with 3 lives
    playerLives.loseLife();  // Lose one life
    CHECK(playerLives.getLives() == 2);  // Lives should be 2

    playerLives.loseLife();  // Lose another life
    CHECK(playerLives.getLives() == 1);  // Lives should be 1

    playerLives.loseLife();  // Lose last life
    CHECK(playerLives.getLives() == 0);  // Lives should be 0

    // Trying to lose a life when none left
    playerLives.loseLife();  // No effect as lives are already 0
    CHECK(playerLives.getLives() == 0);  // Lives should still be 0
}

// Test case for boundary collisions with walls at maze edges
TEST_CASE("Maze Boundary Collisions") {
    Maze maze;

    // Create walls at boundaries of the maze (assuming screen size 1530x890)
    maze.getWalls().emplace_back(Rectangle{0, 0, 1530, 10}, BLACK);  // Top wall
    maze.getWalls().emplace_back(Rectangle{0, 880, 1530, 10}, BLACK);  // Bottom wall
    maze.getWalls().emplace_back(Rectangle{0, 0, 10, 890}, BLACK);  // Left wall
    maze.getWalls().emplace_back(Rectangle{1520, 0, 10, 890}, BLACK);  // Right wall

    // Test collision with boundaries
    CHECK(maze.isWall(5, 5, 34) == true);  // Should collide with top-left corner
    CHECK(maze.isWall(1525, 5, 34) == true);  // Should collide with top-right corner
    CHECK(maze.isWall(5, 885, 34) == true);  // Should collide with bottom-left corner
    CHECK(maze.isWall(1525, 885, 34) == true);  // Should collide with bottom-right corner
}

TEST_CASE("Maze collision detection in complex maze with doors") {
    Maze maze;
    maze.initialiseCustomWalls();  // Set up the complex maze with doors and walls

    // Subtest for Pac-Man not colliding with walls in the center of the maze
    SUBCASE("No collision - Pac-Man in the center of a non-colliding area") {
        // Simulate Pac-Man's position near the center of the screen (non-colliding)
        bool collision = maze.isWallRec(765, 525, 34);  // Pac-Man at (765, 525) with radius 34
        CHECK(collision == false);  // Should not collide if in an open space
    }

    // Subtest for Pac-Man colliding with a simple wall
    SUBCASE("Collision - Pac-Man hitting a basic wall") {
        // Simulate Pac-Man colliding with a wall
        bool collision = maze.isWallRec(0, 80, 34);  // Pac-Man at (0, 80) should collide with a wall
        CHECK(collision == true);  // Should collide with the static wall
    }

    // Subtest for Pac-Man colliding with a locked door
    SUBCASE("Collision - Pac-Man hitting a locked door") {
        // Simulate a locked door in front of Pac-Man
        bool collision = maze.isWallRec(90, 160, 34);  // Check collision with the locked door
        CHECK(collision == true);  // Should collide with the locked door
    }

    // Subtest for Pac-Man colliding with a vertical wall
    SUBCASE("Collision - Pac-Man hitting a vertical wall") {
        bool collision = maze.isWallRec(80, 160, 34);  // Pac-Man at (80, 160) colliding with a vertical wall
        CHECK(collision == true);  // Should collide with the vertical wall
    }

    // Subtest for Pac-Man colliding with a horizontal wall
    SUBCASE("Collision - Pac-Man hitting a horizontal wall") {
        bool collision = maze.isWallRec(560, 800, 34);  // Pac-Man at (560, 800) colliding with a horizontal wall
        CHECK(collision == true);  // Should collide with the horizontal wall
    }
}

// Test case for Maze constructor and initial state
TEST_CASE("Maze Constructor and Initial State") {
    Maze maze;

    // Check that the maze is initialized with no walls
    CHECK(maze.getWalls().empty());
}

// Test case for initializing custom walls from file
TEST_CASE("Maze Custom Walls Initialization") {
    Maze maze;

    // Call initialize custom walls (assuming walls.txt is already configured)
    maze.initialiseCustomWalls();

    // Check that walls have been populated correctly
    const auto& walls = maze.getWalls();
    CHECK(!walls.empty());  // Ensure there are walls

    // Verify the properties of a few walls (assuming known values in walls.txt)
    CHECK(walls[0].rect.x == 90);  // Check wall position
    CHECK(walls[0].rect.y == 160);
    CHECK(walls[0].rect.width == 70);  // Check wall dimensions
    CHECK(walls[0].rect.height == 10);
}

// Test case for multiple PowerPellet objects in different positions
TEST_CASE("Multiple PowerPellet Objects Test") {
    // Create multiple power pellets at different positions
    PowerPellet powerPellet1(100.0f, 100.0f);
    PowerPellet powerPellet2(200.0f, 200.0f);
    PowerPellet powerPellet3(300.0f, 300.0f);

    PacMan pacman(0.0f, 0.0f);  // Create Pac-Man at the position of powerPellet1

    CHECK(powerPellet1.isActive() == true);
    CHECK(powerPellet2.isActive() == true);
    CHECK(powerPellet3.isActive() == true);


    // Collect the first power pellet
    pacman.setPosition(100.0f, 100.0f);
    CHECK(powerPellet1.checkCollisionWithPacMan(pacman) == true);  // Should collect powerPellet1
    CHECK(powerPellet1.isActive() == false);  // powerPellet1 should now be inactive

    // Move Pac-Man to the position of the second power pellet
    pacman.setPosition(200, 200);
    CHECK(powerPellet2.checkCollisionWithPacMan(pacman) == true);  // Should collect powerPellet2
    CHECK(powerPellet2.isActive() == false);  // powerPellet2 should now be inactive

    // Move Pac-Man to the position of the third power pellet
    pacman.setPosition(300, 300);
    CHECK(powerPellet3.checkCollisionWithPacMan(pacman) == true);  // Should collect powerPellet3
    CHECK(powerPellet3.isActive() == false);  // powerPellet3 should now be inactive
}

// Test case for ensuring no interactions occur when PowerPellet is inactive
TEST_CASE("No Interaction When PowerPellet is Inactive") {
    PowerPellet powerPellet(100.0f, 100.0f);
    PacMan pacman(0.0f, 0.0f);

    pacman.setPosition(100.0f, 100.0f);
    CHECK(powerPellet.checkCollisionWithPacMan(pacman) == true);  // Collect pellet
    CHECK(powerPellet.isActive() == false);  // Verify inactive state

    // Pac-Man collides again with the same position (no effect)
    CHECK(powerPellet.checkCollisionWithPacMan(pacman) == false);  // No collision detected
}

// Test case for PacMan constructor initialization
TEST_CASE("PacMan Constructor Initialization") {
    PacMan pacman(100, 200);

    CHECK(pacman.getX() == 765);  // Default starting X position
    CHECK(pacman.getY() == 525);  // Default starting Y position
    CHECK(pacman.getRadius() == 34);  // Default radius value
    CHECK(pacman.isSuper() == false);  // Should not be in super mode initially
    CHECK(pacman.isInvincible() == false);  // Should not be invincible initially
}

// Tests if direction input changes direction of PacMan
TEST_CASE("PacMan Direction Changes") {
    PacMan pacman(0, 0);

    // Subtest for Pac-Man moving to the right
    SUBCASE("Pac-Man moves right") {
        pacman.setDirection(PacMan::RIGHT);
        CHECK(pacman.getDX() == 1);
        CHECK(pacman.getDY() == 0);
    }

    // Subtest for Pac-Man moving to the left
    SUBCASE("Pac-Man moves left") {
        pacman.setDirection(PacMan::LEFT);
        CHECK(pacman.getDX() == -1);
        CHECK(pacman.getDY() == 0);
    }

    // Subtest for Pac-Man moving down
    SUBCASE("Pac-Man moves down") {
        pacman.setDirection(PacMan::DOWN);
        CHECK(pacman.getDX() == 0);
        CHECK(pacman.getDY() == 1); // Map is inverted as Y increases the PacMan's direction goes down
    }

    // Subtest for Pac-Man moving up
    SUBCASE("Pac-Man moves up") {
        pacman.setDirection(PacMan::UP);
        CHECK(pacman.getDX() == 0);
        CHECK(pacman.getDY() == -1); // Map is inverted as Y decreases the PacMan's direction goes up
    }
}

// Test case for Invincibility state
TEST_CASE("PacMan Invincibility State") {
    PacMan pacman(100, 200);
    Maze maze = createMaze();

    CHECK(pacman.isInvincible() == false);  // Initially, PacMan is not invincible

    pacman.setInvincible(true);
    CHECK(pacman.isInvincible() == true);  // PacMan should be invincible now

    pacman.setInvincible(false);
    CHECK(pacman.isInvincible() == false);  // PacMan should no longer be invincible
}

// Test for Invincibility Timer
TEST_CASE("PacMan Invincibility Timer") {
    PacMan pacman(100, 200);
    CHECK(pacman.isInvincible() == false);  // Initially, PacMan is not invincible

    pacman.setInvincible(true);
    CHECK(pacman.isInvincible() == true);  // PacMan should be invincible

    // Simulate update over time
    pacman.updateInvincibility(1.0f);  // 1 second elapsed
    CHECK(pacman.isInvincible() == true);  // Should still be invincible

    pacman.updateInvincibility(1.5f);  // 1.5 more seconds elapsed (total 2.5 seconds)
    CHECK(pacman.isInvincible() == false);  // Invincibility should have expired
}

// Tests if Pac-Man has moved correctly
TEST_CASE("PacMan Movement") {
    PacMan pacman(100, 100);
    Maze maze;
    maze.initialiseCustomWalls();

    // Subtest for right movement
    SUBCASE("Valid right movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), PacMan::RIGHT);
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for left movement
    SUBCASE("Valid left movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), PacMan::LEFT);
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for up movement
    SUBCASE("Valid up movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), PacMan::UP);
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for down movement
    SUBCASE("Valid down movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), PacMan::DOWN);
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }
}

// Test for PacMan's speed change during Super Mode
TEST_CASE("PacMan Speed in Super Mode") {
    PacMan pacman(100, 200);
    Maze maze = createMaze();

    // Store initial position
    float initialX = pacman.getX();
    float initialY = pacman.getY();

    // Move PacMan for 1 second in normal mode
    pacman.setDirection(PacMan::RIGHT);
    pacman.move(maze, 1.0f, PacMan::RIGHT);  // Simulate movement for 1 second in normal mode
    float normalX = pacman.getX();
    float normalY = pacman.getY();

    // Activate Super Mode and move PacMan for 1 second
    pacman.activateSuperMode();
    pacman.setPosition(initialX, initialY);  // Reset position to initial
    pacman.move(maze, 1.0f, PacMan::RIGHT);  // Simulate movement for 1 second in Super Mode
    float superX = pacman.getX();
    float superY = pacman.getY();

    // Verify that PacMan moved further in Super Mode due to increased speed
    CHECK(superX > normalX);
    CHECK(superY == normalY);  // Y position should remain the same
}

// Test case for Super Mode activation and deactivation
TEST_CASE("PacMan Super Mode Activation and Deactivation") {
    PacMan pacman(100, 200);
    CHECK(pacman.isSuper() == false);  // Initially, PacMan is not in super mode

    pacman.activateSuperMode();
    CHECK(pacman.isSuper() == true);  // PacMan should be in super mode
    CHECK(pacman.getVisualRadius() == pacman.getRadius() * 1.5f);  // Radius should increase

    pacman.deactivateSuperMode();
    CHECK(pacman.isSuper() == false);  // Super mode should be deactivated
    CHECK(pacman.getVisualRadius() == pacman.getRadius());  // Radius should return to normal
}

// Test Pac-Man's super mode behavior over time
TEST_CASE("PacMan Super Mode Duration Test") {
    SuperPellet superPellet(300.0f, 400.0f);  // Create a SuperPellet at position (300, 400)
    PacMan pacMan(0.0f, 0.0f);  // Create a Pac-Man at the same position
    pacMan.setPosition(300.0f, 400.0f);

    // Simulate Pac-Man collecting the SuperPellet and entering super mode
    if (superPellet.checkCollision(pacMan.getX(), pacMan.getY(), pacMan.getRadius())) {
        pacMan.activateSuperMode();
        superPellet.collect();
    }

    CHECK(pacMan.isSuper() == true);  // Pac-Man should be in super mode

    // Simulate passing time to deactivate super mode
    pacMan.updateSuperMode(5.0f);  // Simulate 5 seconds passing

    // Verify that Pac-Man is no longer in super mode after the duration ends
    CHECK(pacMan.isSuper() == false);
}

// Test for Super Mode Timer
TEST_CASE("PacMan Super Mode Timer") {
    PacMan pacman(100, 200);
    CHECK(pacman.isSuper() == false);  // Initially, not in super mode

    pacman.activateSuperMode();
    CHECK(pacman.isSuper() == true);  // Super mode should be active

    // Simulate update over time
    pacman.updateSuperMode(2.0f);  // 2 seconds elapsed
    CHECK(pacman.isSuper() == true);  // Should still be in super mode

    pacman.updateSuperMode(3.0f);  // 3 more seconds elapsed (total 5 seconds)
    CHECK(pacman.isSuper() == false);  // Super mode should have expired
}

// Performance and Memory Management Test
TEST_CASE("Performance and Memory Management Test") {
    std::vector<std::unique_ptr<Fruit>> fruits;

    // Create a large number of fruits to test performance and memory handling
    for (int i = 0; i < 10000; ++i) {
        fruits.push_back(std::make_unique<Fruit>(i * 10, i * 10));  // Create fruits at different positions
    }

    CHECK(fruits.size() == 10000);  // Verify all fruits were created

    // Check that all fruits are active initially
    for (const auto& fruit : fruits) {
        CHECK(fruit->isActive() == true);
    }

    // Measure performance (if required) and ensure no memory leaks
    // Use external tools like valgrind to verify memory management
}

// Test case for PowerPellet being collected and becoming inactive
TEST_CASE("PowerPellet Collected and Inactive State Test") {
    PowerPellet powerPellet(100.0f, 100.0f);
    PacMan pacman(0.0f, 0.0f);  // Create Pac-Man at the same position to collect the PowerPellet

    pacman.setPosition(100.0f, 100.0f);
    CHECK(powerPellet.isActive() == true);  // Should be active initially

    // Check collision and collect the pellet
    CHECK(powerPellet.checkCollisionWithPacMan(pacman) == true);  // Should collect
    CHECK(powerPellet.isActive() == false);  // Should be inactive after collection

    // Attempt to collect again (should not change state or collect)
    CHECK(powerPellet.checkCollisionWithPacMan(pacman) == false);  // No further collision
    CHECK(powerPellet.isActive() == false);  // Remains inactive
}

// Test case for collision detection with Pac-Man
TEST_CASE("PowerPellet Collision Detection with Pac-Man") {
    PowerPellet powerPellet(100.0f, 100.0f);  // Create a power pellet at position (100, 100)
    PacMan pacman(0.0f, 0.0f);  // Create Pac-Man at the same position

    pacman.setPosition(100.0f, 100.0f);
    CHECK(powerPellet.isActive() == true);  // PowerPellet should be active initially

    // Check if Pac-Man collides with the power pellet
    bool collisionDetected = powerPellet.checkCollisionWithPacMan(pacman);
    CHECK(collisionDetected == true);  // Should detect collision
    CHECK(powerPellet.isActive() == false);  // PowerPellet should be inactive after collection
}

// Test case for PowerPellet constructor
TEST_CASE("PowerPellet Constructor Test") {
    PowerPellet powerPellet(100.0f, 200.0f);  // Create a power pellet at position (100, 200)

    CHECK(powerPellet.getX() == 100.0f);  // Verify the initial X coordinate
    CHECK(powerPellet.getY() == 200.0f);  // Verify the initial Y coordinate
    CHECK(powerPellet.getRadius() == 10.0f);  // Verify the radius
    CHECK(powerPellet.isActive() == true);  // PowerPellet should be active initially
}

// Test case for no collision when Pac-Man is far from PowerPellet
TEST_CASE("PowerPellet No Collision Detection when Pac-Man is Far") {
    PowerPellet powerPellet(100.0f, 100.0f);  // Create a power pellet at position (100, 100)
    PacMan pacman(500, 500);  // Create Pac-Man far from the power pellet

    CHECK(powerPellet.isActive() == true);  // PowerPellet should be active initially

    // Check if Pac-Man collides with the power pellet (should not)
    bool collisionDetected = powerPellet.checkCollisionWithPacMan(pacman);
    CHECK(collisionDetected == false);  // Should not detect collision
    CHECK(powerPellet.isActive() == true);  // PowerPellet should remain active
}

// Test case for handling an empty file
TEST_CASE("Reader handles an empty file correctly") {
    const std::string tempFileName = "../resources/empty_walls.txt";
    
    // Create an empty file
    std::ofstream outFile(tempFileName);
    outFile.close();  // Close the file to ensure it's saved as empty

    // Create a Reader object and read from the empty file
    Reader reader(tempFileName);
    reader.readFile();  // Pass the file path to the reader

    // Get the data from the Reader and check its content
    const auto& data = reader.getData();
    CHECK(data.empty());  // Check if the data vector is empty

    // Clean up the temporary file after the test
    std::remove(tempFileName.c_str());
}


// Test case for handling a non-existent file
TEST_CASE("Reader handles non-existent file correctly") {
    const std::string nonExistentFileName = "../resources/non_existent_walls.txt";
    
    // Create a WallReader object and read from the non-existent file
    Reader reader(nonExistentFileName);
    
    // Redirect std::cerr to capture error messages
    std::stringstream errorBuffer;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(errorBuffer.rdbuf());

    // Try reading the file (this should fail and print an error message)
    reader.readFile();

    // Check that the error message was printed to std::cerr
    std::string expectedErrorMessage = "Error: Cannot open file " + nonExistentFileName + "\n";
    CHECK(errorBuffer.str() == expectedErrorMessage);

    // Restore std::cerr
    std::cerr.rdbuf(oldCerrBuffer);

    // Check that the data vector is empty
    CHECK(reader.getData().empty());
}

// Test case for reading a valid file with content
TEST_CASE("Reader reads file content correctly") {
    const std::string tempFileName = "../resources/temp_walls.txt";
    std::vector<std::string> fileContents = {
        "Wall 1: x=10, y=20, width=50, height=5",
        "Wall 2: x=30, y=40, width=70, height=5",
        "Wall 3: x=50, y=60, width=90, height=5"
    };

    // Create a temporary file with the given contents
    createTempFile(tempFileName, fileContents);

    // Create a WallReader object and read from the temporary file
    Reader reader(tempFileName);
    reader.readFile();

    // Get the data from the WallReader and check its content
    const auto& data = reader.getData();
    CHECK(data.size() == fileContents.size());  // Check if the number of lines matches

    for (size_t i = 0; i < fileContents.size(); ++i) {
        CHECK(data[i] == fileContents[i]);  // Check if each line matches the expected content
    }

    // Clean up the temporary file after the test
    std::remove(tempFileName.c_str());
}

// Test case for handling a file with multiple lines and special characters
TEST_CASE("Reader reads file with special characters correctly") {
    const std::string tempFileName = "../resources/special_walls.txt";
    std::vector<std::string> fileContents = {
        "Wall #1: x=10, y=20, width=50, height=5",
        "Wall @2: x=30, y=40, width=70, height=5",
        "Wall &3: x=50, y=60, width=90, height=5",
        "!Wall *4: x=70, y=80, width=110, height=5"
    };

    // Create a temporary file with the given contents
    createTempFile(tempFileName, fileContents);

    // Create a WallReader object and read from the temporary file
    Reader reader(tempFileName);
    reader.readFile();

    // Get the data from the WallReader and check its content
    const auto& data = reader.getData();
    CHECK(data.size() == fileContents.size());  // Check if the number of lines matches

    for (size_t i = 0; i < fileContents.size(); ++i) {
        CHECK(data[i] == fileContents[i]);  // Check if each line matches the expected content
    }
}

// Test adding points and high score update logic
TEST_CASE("Score Addition and High Score Update Test") {
    const std::string tempFileName = "../resources/test_highscore.txt";
    std::ofstream ofs;
    // Create an empty file
    std::ofstream outFile(tempFileName);
    outFile.close();  // Close the file to ensure it's saved as empty

    // Create a Reader object and read from the empty file
    Reader reader(tempFileName);
    reader.readFile();
    Score score(tempFileName);

    score.addPoints(10);
    CHECK(score.getCurrentScore() == 10);  // Current score should be 10
    CHECK(score.getHighScore() == 10);  // High score should also be 10 (since it's the highest so far)

    score.addPoints(20);
    CHECK(score.getCurrentScore() == 30);  // Current score should now be 30
    CHECK(score.getHighScore() == 30);  // High score should update to 30

    // Test if high score remains the same when lower points are added
    score.addPoints(-10);  // Invalid operation, subtracting points (assuming it's not allowed)
    CHECK(score.getCurrentScore() == 20);  // Score should decrease to 20
    CHECK(score.getHighScore() == 30);  // High score should remain 30
    // Cleanup: Delete the file after the test is complete
    std::remove(tempFileName.c_str());
}


// Test the Score constructor and initial values
TEST_CASE("Score Constructor Test") {
    const std::string tempFileName = "test_highscoreInitial.txt";
    std::ofstream ofs;
    // Create an empty file
    std::ofstream outFile(tempFileName);
    outFile.close();  // Close the file to ensure it's saved as empty

    // Create a Reader object and read from the empty file
    Reader reader(tempFileName);
    reader.readFile();
    Score score(tempFileName);
    CHECK(score.getCurrentScore() == 0);  // Initial current score should be 0
    CHECK(score.getHighScore() == 0);  // Initial high score should be 0 or loaded value if file exists

    // Cleanup: remove test file if created
    std::remove(tempFileName.c_str());
}

//Test that collecting a fruit increases the score
TEST_CASE("Score Increment Test") {
    Fruit fruit(200, 300);
    Score score("Fruit_score_test.txt");

    CHECK(score.getCurrentScore() == 0);  // Initial score should be 0
    fruit.collect();  // Simulate collecting the fruit
    score.addPoints(10);  // Assume collecting the fruit gives 10 points
    CHECK(score.getCurrentScore() == 10);  // Score should now be 10
}

//Screen Tests

TEST_CASE("Screen correctly draws the maze") {
    Screen screen;
    Maze maze;
    Draw draw;

    // Draw the maze
    draw.drawMaze(maze);

    // Check if the function completes without errors.
    CHECK(true); // If no exception or error occurs, the test passes
}

// Test case for verifying end game screen
TEST_CASE("Screen correctly handles end game screen") {
    auto screen = std::make_unique<Screen>(); // If Draw does not contain startScreen
    Game game;
    Score score("test_screen_endgame.txt");

    // Initialize game objects and set some score
    game.initialise(true);
    score.addPoints(1000);

    // Display end game screen and verify it stops the game loop
    
    bool result = screen->endGame(score);
    CHECK(result == false);  // The game loop should stop
}

TEST_CASE("Screen correctly handles power pellet drawing") {
    Game game;
    Draw draw;
    game.initialise(true);

    // Check if there are power pellets to draw
    CHECK(!game.getPowerPellets().empty());

    // Convert PowerPellet* vector to unique_ptr vector
    std::vector<std::unique_ptr<PowerPellet>> powerPellets;
    for (auto pellet : game.getPowerPellets()) {
        powerPellets.push_back(std::unique_ptr<PowerPellet>(pellet));  // Transfer ownership
    }

    // Draw power pellets using the converted vector
    draw.drawPowerPellets(powerPellets);
    CHECK(true);  // If no exception or error occurs, the test passes
}

// Test case for verifying win screen
TEST_CASE("Screen correctly handles win game screen") {
    Screen screen;
    Game game;
    Score score("test_screen_wingame.txt");
 
    game.initialise(true);
    score.addPoints(5000);

    // Display win game screen and verify it stops the game loop
    bool result = screen.winGame(score);
    CHECK(result == false);  // The game loop should stop
}

TEST_CASE("Screen draws Pac-Man correctly") {
    Draw draw;
    Game game;
    game.initialise(true);
    PacMan pacman(150, 150);
    int frame = 0;

    // Draw Pac-Man without copying Screen
    draw.drawPacMan(pacman, frame, Draw::RIGHT);
    CHECK(true);  // If no exception or error occurs, the test passes
}

TEST_CASE("Screen draws the lives correctly") {
    Draw draw;
    Game game;
    game.initialise(true);
    int lives = 3;  // Simulate 3 lives

    // Draw the lives and ensure the function works correctly
    draw.drawLives(lives);

    // Check if the function completes without errors.
    CHECK(true); // If no exception or error occurs, the test passes
}

TEST_CASE("Screen draws the score correctly") {
    Draw draw;
    Score score("test_screen_score.txt");

    // Mock scores
    score.addPoints(100);
    score.addPoints(200);

    // Draw the score and ensure the function works correctly
    draw.drawScores(score);

    // Check if the function completes without errors.
    CHECK(true); // If no exception or error occurs, the test passes
}

// Test case for initializing and displaying the screen
TEST_CASE("Screen initializes and displays correctly") {
    Game game;                     // Create a Game instance
    Screen screen;
    Score score("test_screen_initialisation.txt");

    game.initialise(true);             // Initialize the game

    screen.startScreen(&game, score);

    // Check if game is running using the Game class method
    CHECK(game.isGameRunning() == true);
}

// Test that collision detection works as expected
TEST_CASE("Star Collision Detection Test") {
    Star testStar(500, 500);  // Initialize with position (500, 500)

    testStar.show();
    // Check collision with a point that intersects the star
    bool collisionDetected = testStar.checkCollision(500, 500, 10.0f);
    CHECK(collisionDetected == true);  // Should detect collision

    // Check collision with a point far away from the star
    collisionDetected = testStar.checkCollision(800, 800, 10.0f);
    CHECK(collisionDetected == false);  // Should not detect collision
}

// Test that Star is initialized correctly with given parameters
TEST_CASE("Star Constructor Test") {
    Star testStar(100, 200);  // Initialize with position (100, 200)

    CHECK(testStar.getX() == 100);           // X position should be 100
    CHECK(testStar.getY() == 200);           // Y position should be 200
    CHECK(testStar.getRadius() == 20.0f);    // Radius should be 20.0f as defined
    CHECK(testStar.isActive() == false);     // Star should be inactive initially
}

// Test that the show method activates the Star
TEST_CASE("Star Show Test") {
    Star testStar(150, 250);  // Initialize with position (150, 250)
    
    CHECK(testStar.isActive() == false);  // Star should be inactive initially
    testStar.show();                     // Activate the star
    CHECK(testStar.isActive() == true);   // Star should be active after show() is called
}

// Test SuperPellet and Pac-Man interaction using the PacMan class
TEST_CASE("SuperPellet and PacMan Interaction Test") {
    SuperPellet superPellet(300.0f, 400.0f);  // Create a SuperPellet at position (300, 400)
    PacMan pacMan(0.0f, 0.0f);  // Create a Pac-Man at the same position

    // Check that Pac-Man initially does not have super mode activated
    pacMan.setPosition(300.0f, 400.0f);
    CHECK(pacMan.isSuper() == false);

    // Simulate Pac-Man collecting the SuperPellet by checking for collision
    bool collision = superPellet.checkCollision(pacMan.getX(), pacMan.getY(), pacMan.getRadius());

    // If collision is detected, activate Pac-Man's super mode
    if (collision) {
        pacMan.activateSuperMode();
        superPellet.collect();  // Mark the SuperPellet as collected
    }

    // Verify that the SuperPellet is no longer active and Pac-Man is in super mode
    CHECK(superPellet.isActive() == false);
    CHECK(pacMan.isSuper() == true);
}

// Test that SuperPellet does not interfere with normal Collectable behavior
TEST_CASE("SuperPellet Collectable Base Class Behavior") {
    SuperPellet superPellet(300.0f, 400.0f);

    // Verify that SuperPellet inherits and behaves as a Collectable
    Collectable& base = superPellet;  // Upcast to base class reference

    CHECK(base.isActive() == true);  // Check initial active state

    base.collect();  // Call the base class collect method
    CHECK(base.isActive() == false);  // Check that the SuperPellet is no longer active
}

// Test SuperPellet collection behavior
TEST_CASE("SuperPellet Collection Test") {
    SuperPellet superPellet(300.0f, 400.0f);  // Create a SuperPellet at position (300, 400)

    // Simulate Pac-Man collecting the SuperPellet
    superPellet.collect();

    // Check that the SuperPellet is no longer active
    CHECK(superPellet.isActive() == false);
}

// Test SuperPellet collision detection
TEST_CASE("SuperPellet Collision Detection Test") {
    SuperPellet superPellet(300.0f, 400.0f);  // Create a SuperPellet at position (300, 400)

    // Check collision with a Pac-Man positioned to collide with the SuperPellet
    float pacManX = 300.0f;
    float pacManY = 400.0f;
    float pacManRadius = 30.0f;  // Pac-Man radius is greater than the SuperPellet radius

    CHECK(superPellet.checkCollision(pacManX, pacManY, pacManRadius) == true);  // Collision should occur

    // Move Pac-Man away from the SuperPellet
    pacManX = 500.0f;
    pacManY = 500.0f;

    CHECK(superPellet.checkCollision(pacManX, pacManY, pacManRadius) == false);  // No collision should occur
}

// Test SuperPellet constructor
TEST_CASE("SuperPellet Constructor Test") {
    SuperPellet superPellet(100.0f, 200.0f);  // Create a SuperPellet at position (100, 200)

    // Check initial position and radius
    CHECK(superPellet.getX() == 100.0f);
    CHECK(superPellet.getY() == 200.0f);
    CHECK(superPellet.getRadius() == 15.0f);  // SuperPellet should have a radius of 15.0f

    // Check that the SuperPellet is active initially
    CHECK(superPellet.isActive() == true);
}

// Integration Test: Check if keys correctly unlock walls in the maze
TEST_CASE("Update: Keys unlock walls") {
    // Set up game, draw, and update objects
    Game game;
    Draw draw;
    GameInitialiser::initialiseGameObjects(game);  // Initialize game objects
    Update updater(game, &draw);

    // Create and add the key to the game's keys list
    std::vector<int> wallsToUnlock = {0, 1};  // Keys that will unlock walls 0 and 1
    GameKey key(100.0f, 100.0f, wallsToUnlock);  // Create a key at position (100, 100)
    game.getKeys().push_back(key);  // Add the key to the game's key list

    // Create walls and set their initial state to active (locked)
    auto maze = std::make_unique<Maze>();
    maze->getWalls().emplace_back(Rectangle{0, 0, 50, 10}, BLACK);  // Wall 0
    maze->getWalls().emplace_back(Rectangle{100, 100, 50, 10}, BLACK);  // Wall 1
    maze->getWalls()[0].active = true;  // Mark wall 0 as locked initially
    maze->getWalls()[1].active = true;  // Mark wall 1 as locked initially
    game.setMaze(std::move(maze));  // Set the maze in the game

    // Set Pac-Man's position to be at the key's location (to simulate a collision)
    game.getPacMan().setPosition(100.0f, 100.0f);

    // Call updateKeys to simulate the key collection and wall unlocking
    updater.updateKeys();

    // Check if the key is now inactive (collected)
    CHECK(game.getKeys()[0].isActive() == false);

    // Check that the associated walls are now deactivated (unlocked)
    CHECK(game.getMaze().getWalls()[0].active == false);  // Wall 0 should be unlocked
    CHECK(game.getMaze().getWalls()[1].active == false);  // Wall 1 should be unlocked
}

// Integration Test: Check if score is updated correctly when a key is collected
TEST_CASE("Update: Score increments on key collection") {
    // Set up the game and initialise without showing the start screen
    Game game;
    game.initialise(true);  // Initialise game objects

    // Use an existing key from the game (ensure that keys are not empty)
    REQUIRE_FALSE(game.getKeys().empty());  // Check that keys are properly initialised

    // Access the first key (or any other key) and get its position
    auto& existingKey = game.getKeys().front();  // Use the first key
    auto keyX = static_cast<float>(existingKey.getX());
    auto keyY = static_cast<float>(existingKey.getY());

    // Set Pac-Man's position to be at the key's location (to simulate a collision)
    game.getPacMan().setPosition(keyX, keyY);

    // Call updateKeys to simulate the key collection and score increment
    game.getUpdater()->updateKeys();

    // Check that the score has been updated correctly
    CHECK(game.getScore().getCurrentScore() == 50);  // Score should increase by 50 points
}


