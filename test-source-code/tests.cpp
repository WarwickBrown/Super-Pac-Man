#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PacMan.h"
#include "Maze.h"

#include <raylib-cpp.hpp>

// Test collision detection with custom walls
TEST_CASE("Maze collision detection") {
    Maze maze;
    maze.initialiseCustomWalls();

    // Simulate Pac-Man position near the center of the screen (non-colliding)
    bool collision = maze.isWall(800, 450, 37);  // Pac-Man at (800, 450) with radius 37
    CHECK(collision == false);

    // Simulate Pac-Man hitting a wall
    collision = maze.isWall(5, 450, 37);  // Pac-Man at (5, 450) should hit the left wall
    CHECK(collision == true);
}

// Tests if direction input changes direction of PacMan
TEST_CASE("Direction Options Not Working"){
    PacMan pacman(1, 3);

    // Simulates for when the PacMan is moving Right
    int dir = 1;
    pacman.setDirection(dir);
    CHECK(pacman.getDX() != 1 && pacman.getDY() != 0);

    // Simulates for when the PacMan is moving Left
    dir = 2;
    pacman.setDirection(dir);
    CHECK(pacman.getDX() != -1 && pacman.getDY() != 0);

    // Simulates for when the PacMan is moving Down
    dir = 3;
    pacman.setDirection(dir);
    CHECK(pacman.getDX() != 0 && pacman.getDY() != -1);

    // Simulates for when the PacMan is moving Up
    dir = 4;
    pacman.setDirection(dir);
    CHECK(pacman.getDX() != 0 && pacman.getDY() != 1);
}

// Tests if the PacMan mas moved
TEST_CASE("Movement Options Not Working"){
    PacMan pacman(1, 3);
    Maze maze;

    // Simulates for a PacMan movement 
    pacman.setDirection(1);
    float initialX = pacman.getX();
    float initialY = pacman.getY();
    pacman.move(maze, pacman.getFrames(), 1);
    CHECK((initialX + pacman.getDX()*0.1) == pacman.getX() && (initialY + pacman.getDY()*0.1) == pacman.getY());
}


