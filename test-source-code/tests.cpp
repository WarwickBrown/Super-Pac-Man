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

// Tests if direction input changes direction of PacMan
TEST_CASE("PacMan Direction Changes") {
    PacMan pacman(0, 0);

    // Subtest for Pac-Man moving to the right
    SUBCASE("Pac-Man moves right") {
        pacman.setDirection(1);  // Right
        CHECK(pacman.getDX() == 1);
        CHECK(pacman.getDY() == 0);
    }

    // Subtest for Pac-Man moving to the left
    SUBCASE("Pac-Man moves left") {
        pacman.setDirection(2);  // Left
        CHECK(pacman.getDX() == -1);
        CHECK(pacman.getDY() == 0);
    }

    // Subtest for Pac-Man moving down
    SUBCASE("Pac-Man moves down") {
        pacman.setDirection(3);  // Down
        CHECK(pacman.getDX() == 0);
        CHECK(pacman.getDY() == -1);
    }

    // Subtest for Pac-Man moving up
    SUBCASE("Pac-Man moves up") {
        pacman.setDirection(4);  // Up
        CHECK(pacman.getDX() == 0);
        CHECK(pacman.getDY() == 1);
    }
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
        pacman.move(maze, pacman.getFrames(), 1);  // Move right
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for left movement
    SUBCASE("Valid left movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), 2);  // Move left
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for up movement
    SUBCASE("Valid up movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), 3);  // Move up
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }

    // Subtest for down movement
    SUBCASE("Valid down movement") {
        int initialX = pacman.getX();
        int initialY = pacman.getY();
        pacman.move(maze, pacman.getFrames(), 4);  // Move down
        CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
        CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
    }
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

TEST_CASE("Ghost Does Not Collide With PacMan") {
    Ghost ghost(100, 100, 150.0f);
    PacMan pacman(300, 300);  // Pac-Man is close enough to collide
    CHECK(ghost.checkCollisionWithPacMan(pacman) == false);  // No collision should occur
}

// Fruit tests

// Test that the Fruit is initialized correctly
TEST_CASE("Fruit Constructor Test") {
    Fruit fruit(100, 200);  // Create a fruit at position (100, 200)

    CHECK(fruit.getX() == 100);  // Verify initial x position
    CHECK(fruit.getY() == 200);  // Verify initial y position
    CHECK(fruit.isActive() == true);  // Fruit should be active initially
    CHECK(fruit.isEaten() == false);  // Fruit should not be eaten initially
}

// Test that the Fruit is initialized correctly
TEST_CASE("Fruit Constructor Test") {
    Fruit fruit(100, 200);  // Create a fruit at position (100, 200)

    CHECK(fruit.getX() == 100);  // Verify initial x position
    CHECK(fruit.getY() == 200);  // Verify initial y position
    CHECK(fruit.isActive() == true);  // Fruit should be active initially
    CHECK(fruit.isEaten() == false);  // Fruit should not be eaten initially
    CHECK(fruit.getRadius() == 50.0f);  // Verify default radius
}

// Test for state changes when a fruit is collected
TEST_CASE("Active and Eaten State Test") {
    Fruit fruit(150, 250);  // Create a fruit at position (150, 250)

    CHECK(fruit.isActive() == true);  // Fruit should be active initially
    CHECK(fruit.isEaten() == false);  // Fruit should not be eaten initially

    fruit.markAsEaten();  // Mark the fruit as eaten
    CHECK(fruit.isEaten() == true);  // Fruit should now be marked as eaten
    CHECK(fruit.isActive() == false);  // Fruit should no longer be active
}

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

// Test that collecting a fruit increases the score
// TEST_CASE("Score Increment Test") {
//     Fruit fruit(200, 300);
//     Score score;

//     CHECK(score.currentScore == 0);  // Initial score should be 0
//     fruit.collect();  // Simulate collecting the fruit
//     score.addPoints(10);  // Assume collecting the fruit gives 10 points
//     CHECK(score.currentScore == 10);  // Score should now be 10
// }

// // Verify that interactions with ghosts do not affect fruits
// TEST_CASE("No Interaction with Ghosts Test") {
//     Fruit fruit(150, 250);  // Create a fruit
//     Ghost ghost;  // Create a ghost object (assuming a Ghost class is defined)

//     fruit.markAsEaten();  // Simulate Pac-Man collecting the fruit
//     CHECK(fruit.isEaten() == true);  // Verify fruit is marked as eaten
//     CHECK(ghost.getPosition() == /* ghost initial position */);  // Ghost properties should be unchanged
// }

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
    fruit4.markAsEaten();
    CHECK(fruit4.isActive() == false);
    CHECK(fruit5.isActive() == true);  // Fruit5 should remain active
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


TEST_CASE("Game ends when all fruits are collected") {
    Game game;
    game.initialiseGameObjects();  // Initialize game objects like Pac-Man, ghosts, maze, etc.
    game.initialiseFruits();  // Initialize the fruits in the maze

    // Ensure the game is running at the start
    CHECK(game.isGameRunning());

    for (const auto& fruit : game.getFruits()) {
        fruit->collect();  // Mark each fruit as collected
        fruit->markAsEaten();  // Set the fruit as eaten
    }

    game.checkWinCondition();

    CHECK(game.isGameWon() == true);  // Check if the game end flag is triggered
    CHECK(game.isGameRunning() == false);  // The game should stop running
}


// File tests

// Test the Score constructor and initial values
TEST_CASE("Score Constructor Test") {
    Score score("test_highscore.txt");

    CHECK(score.getCurrentScore() == 0);  // Initial current score should be 0
    CHECK(score.getHighScore() == 0);  // Initial high score should be 0 or loaded value if file exists

    // Cleanup: remove test file if created
    std::remove("../resources/test_highscore.txt");
}

// Test adding points and high score update logic
TEST_CASE("Score Addition and High Score Update Test") {
    Score score("test_highscore.txt");

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

    // Cleanup
    std::remove("../resources/test_highscore.txt");
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


// Test file handling and exception safety
TEST_CASE("File Handling Test") {
    const std::string invalidFilePath = "/invalid/path/highscore.txt";
    Score invalidScore(invalidFilePath);  // This should trigger an exception or fail to open

    CHECK(invalidScore.getHighScore() == 0);  // High score should default to 0 if file couldn't be read
    CHECK(invalidScore.getCurrentScore() == 0);  // Current score should remain 0

    // Verify no crash on save attempt (exception should be caught internally)
    invalidScore.saveHighScore();
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


// Test active state manipulation
// TEST_CASE("GameKey Active State Test") {
//     std::vector<int> wallsToUnlock = {1, 2};
//     GameKey key(100.0f, 100.0f, wallsToUnlock);

//     // Ensure key starts as active
//     CHECK(key.isActive() == true);

//     // Deactivate key and check status
//     key.setActive(false);
//     CHECK(key.isActive() == false);

//     // Reactivate key and check status
//     key.setActive(true);
//     CHECK(key.isActive() == true);
// }


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

// Integration Test: Check GameKey integration with other objects (such as maze)
// TEST_CASE("GameKey Integration Test with Maze") {
//     std::vector<int> wallsToUnlock = {1, 2};
//     GameKey key(100.0f, 100.0f, wallsToUnlock);

//     Maze maze;
//     // Mock unlocking logic for walls in maze based on key (assuming Maze has unlockWall method)
//     for (int wallIndex : key.getWallsToUnlock()) {
//         maze.unlockWall(wallIndex);  // Unlock the wall associated with this key
//     }

//     // Check that the walls have been unlocked in the maze (assuming Maze has isWallLocked method)
//     CHECK(maze.isWallLocked(1) == false);  // Wall 1 should be unlocked
//     CHECK(maze.isWallLocked​(2) == false);
// }

// Lives tests

// Test that Lives is initialized correctly
TEST_CASE("Lives Constructor Test") {
    Lives playerLives(3);  // Initialize with 3 lives
    CHECK(playerLives.getLives() == 3);  // Lives should be 3
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


// Test that Star is initialized correctly with given parameters
TEST_CASE("Star Constructor Test") {
    Star testStar(100, 200);  // Initialize with position (100, 200)

    CHECK(testStar.getX() == 100);           // X position should be 100
    CHECK(testStar.getY() == 200);           // Y position should be 200
    CHECK(testStar.getRadius() == 20.0f);    // Radius should be 20.0f as defined
    CHECK(testStar.isActive() == false);     // Star should be inactive initially
    CHECK(testStar.isEaten() == false);      // Star should not be eaten initially
}

// Test that the show method activates the Star
TEST_CASE("Star Show Test") {
    Star testStar(150, 250);  // Initialize with position (150, 250)
    
    CHECK(testStar.isActive() == false);  // Star should be inactive initially
    testStar.show();                     // Activate the star
    CHECK(testStar.isActive() == true);   // Star should be active after show() is called
}


// Test that collision detection works as expected
TEST_CASE("Star Collision Detection Test") {
    Star testStar(500, 500);  // Initialize with position (500, 500)

    // Check collision with a point that intersects the star
    bool collisionDetected = testStar.checkCollision(500, 500, 10.0f);
    CHECK(collisionDetected == true);  // Should detect collision

    // Check collision with a point far away from the star
    collisionDetected = testStar.checkCollision(800, 800, 10.0f);
    CHECK(collisionDetected == false);  // Should not detect collision
}



// Test that Game transitions to the correct state based on input
// TEST_CASE("Game State Transitions Test") {
//     Game game;
//     game.initialise();

//     // Simulate starting the game
//     game.handleInput(KEY_ENTER);  // Simulate ENTER key press
//     CHECK(game.isGameRunning() == true);

//     // Simulate ESCAPE key press to end the game
//     game.handleInput(KEY_ESCAPE);
//     CHECK(game.isGameRunning() == false);
// }

// // Test handleInput for directional controls
// TEST_CASE("Game Input Handling Test") {
//     Game game;
//     game.initialise();

//     game.handleInput(KEY_RIGHT);
//     CHECK(game.getDirection() == 1);  // Right direction

//     game.handleInput(KEY_LEFT);
//     CHECK(game.getDirection() == 2);  // Left direction

//     game.handleInput(KEY_UP);
//     CHECK(game.getDirection() == 3);  // Up direction

//     game.handleInput(KEY_DOWN);
//     CHECK(game.getDirection() == 4);  // Down direction
// }

// Test that Pac-Man can collect fruits correctly and updates score
TEST_CASE("Game Fruit Collection Test") {
    Game game;
    game.initialiseGameObjects();
    game.initialiseFruits();

    // Get initial score
    int initialScore = game.getScore()->getCurrentScore();

    // Simulate Pac-Man collecting the first fruit
    auto& fruits = game.getFruits();
    fruits[0]->collect();  // Directly call collect() on the first fruit
    game.updateFruits();   // Update game state for fruit collection

    CHECK(fruits[0]->isEaten() == true);  // Fruit should be marked as eaten
    CHECK(game.getScore()->getCurrentScore() == initialScore + 10);  // Score should increase by 10 points
}

TEST_CASE("Game correctly handles power pellet interaction") {
    Game game;
    game.initialiseGameObjects();      // Initialize game objects
    game.initialisePowerPellets();     // Initialize power pellets

    // Ensure there are power pellets in the game
    REQUIRE(!game.getPowerPellets().empty());

    // Simulate Pac-Man eating a power pellet
    auto& powerPellet = game.getPowerPellets().front();
    CHECK(powerPellet->isActive() == true);  // Power pellet should be active
    powerPellet->collect();  // Pac-Man collects the power pellet

    game.updatePowerPellets();  // Update the game state with the collected pellet

    // Check if the power pellet interaction caused the desired effect (e.g., ghosts frightened)
    for (auto& ghost : game.getGhosts()) {
        CHECK(ghost->isFrightened() == true);  // Ghosts should be in frightened mode
    }
}

// Test that the game ends when Pac-Man loses all lives
TEST_CASE("Game Over Condition Test") {
    Game game;
    game.initialise();

    auto lives = game.getPlayerLives();

    // Simulate losing all lives
    while (lives->getLives() > 0) {
        lives->loseLife();
    }

    game.update();  // Update game state for lives condition
    CHECK(game.isGameRunning() == false);  // Game should stop running
}

