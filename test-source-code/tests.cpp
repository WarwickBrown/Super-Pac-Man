#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PacMan.h"
#include "Maze.h"

// Test collision detection with custom walls
TEST_CASE("Maze collision detection") {
    Maze maze;
    maze.initialiseCustomWalls();

    // Subtest for Pac-Man not colliding with walls
    SUBCASE("No collision - Pac-Man in the center of the screen") {
        // Simulate Pac-Man position near the center of the screen (non-colliding)
        bool collision = maze.isWall(800, 450, 37);  // Pac-Man at (800, 450) with radius 37
        CHECK(collision == false);  // Should not collide
    }

    // Subtest for Pac-Man colliding with the left wall
    SUBCASE("Collision - Pac-Man hitting the left wall") {
        // Simulate Pac-Man hitting a wall
        bool collision = maze.isWall(5, 450, 37);  // Pac-Man at (5, 450) should hit the left wall
        CHECK(collision == true);  // Should collide
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


