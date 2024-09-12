#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PacMan.h"
#include "Maze.h"

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


