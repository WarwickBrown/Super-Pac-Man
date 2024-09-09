#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Maze.h"

// Test Pac-Man Movement within the Maze
TEST_CASE("PacMan Movement") {
    Maze maze;  // Create a maze instance
    PacMan pacMan(32, 32);  // Pac-Man starts at (32, 32) pixels, corresponding to grid (1, 1)
    
    SUBCASE("Move Right into Empty Space") {
        pacMan.setDirection(1, 0);  // Set direction to right
        pacMan.move(maze);  // Move Pac-Man
        CHECK(pacMan.getX() == 33);  // Expect Pac-Man to move right (2,1), so x = 64
        CHECK(pacMan.getY() == 32);  // Y should remain the same
    }

    SUBCASE("Move Left into Wall") {
        pacMan.setDirection(-1, 0);  // Set direction to left
        pacMan.move(maze);  // Move Pac-Man
        CHECK(pacMan.getX() == 32);  // Expect Pac-Man to not move into the wall at (0,1), so x = 32
        CHECK(pacMan.getY() == 32);  // Y should remain the same
    }

    SUBCASE("Move Up into Wall") {
        pacMan.setDirection(0, -1);  // Set direction to up
        pacMan.move(maze);  // Move Pac-Man
        CHECK(pacMan.getY() == 32);  // Pac-Man should not move into the wall at (1,0), so y = 32
        CHECK(pacMan.getX() == 32);  // X should remain the same
    }

    SUBCASE("Move Down into Empty Space") {
        pacMan.setDirection(0, 1);  // Set direction to down
        pacMan.move(maze);  // Move Pac-Man
        CHECK(pacMan.getY() == 33);  // Expect Pac-Man to move down to (1,2), so y = 64
        CHECK(pacMan.getX() == 32);  // X should remain the same
    }
}


// Test Ghost Movement and Collision with Maze
TEST_CASE("Ghost Movement") {
    Maze maze;  // Create a maze instance
    Ghost ghost(32, 32);  // Ghost starts at (64, 64) pixels, corresponding to grid (2, 2)
    PacMan pacMan(64, 64);  // Pac-Man starts at (32, 32) pixels, corresponding to grid (1, 1)

    SUBCASE("Move Right into Empty Space") {
        ghost.setDirection(1, 0);  // Set direction to right
        ghost.move(maze, pacMan);  // Move ghost
        CHECK(ghost.getX() == 96);  // Ghost should move to the right (3, 2), so x = 96
        CHECK(ghost.getY() == 64);  // Y should remain the same
    }

    SUBCASE("Move Left into Wall") {
        ghost.setDirection(-1, 0);  // Set direction to left
        ghost.move(maze, pacMan);  // Move ghost
        CHECK(ghost.getX() == 64);  // Ghost should not move into the wall at (1, 2), so x = 64
        CHECK(ghost.getY() == 64);  // Y should remain the same
    }

    SUBCASE("Move Down into Empty Space") {
        ghost.setDirection(0, 1);  // Set direction to down
        ghost.move(maze, pacMan);  // Move ghost
        CHECK(ghost.getY() == 96);  // Ghost should move down to (2, 3), so y = 96
        CHECK(ghost.getX() == 64);  // X should remain the same
    }

    SUBCASE("Move Up into Wall") {
        ghost.setDirection(0, -1);  // Set direction to up
        ghost.move(maze, pacMan);  // Move ghost
        CHECK(ghost.getY() == 64);  // Ghost should not move into the wall at (2, 1), so y = 64
        CHECK(ghost.getX() == 64);  // X should remain the same
    }
}


// Test Maze Collision Detection
TEST_CASE("Maze Collision Detection") {
    Maze maze;  // Initialize maze with default layout

    SUBCASE("Check Wall Collision") {
        CHECK(maze.isWall(0, 0) == true);  // Expect top-left corner to be a wall
        CHECK(maze.isWall(5, 5) == false);  // Expect an open path at (5, 5)
    }

    SUBCASE("Check Open Path") {
        CHECK(maze.isWall(1, 1) == false);  // Expect (1, 1) to be an open path
    }
}
