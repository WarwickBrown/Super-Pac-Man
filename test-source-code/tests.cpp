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