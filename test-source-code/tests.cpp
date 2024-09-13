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

// Tests if direction input changes direction of PacMan
TEST_CASE("PacMan Direction Options Not Working") {
    PacMan pacman(0, 0);

    // Simulates for when PacMan is moving Right
    pacman.setDirection(1);
    CHECK(pacman.getDX() == 1);
    CHECK(pacman.getDY() == 0);

    // Simulates for when PacMan is moving Left
    pacman.setDirection(2);
    CHECK(pacman.getDX() == -1);
    CHECK(pacman.getDY() == 0);

    // Simulates for when PacMan is moving Down
    pacman.setDirection(3);
    CHECK(pacman.getDX() == 0);
    CHECK(pacman.getDY() == -1);

    // Simulates for when PacMan is moving Up
    pacman.setDirection(4);
    CHECK(pacman.getDX() == 0);
    CHECK(pacman.getDY() == 1);
}


// Tests if the PacMan mas moved
TEST_CASE("PacMan Movement Options Testing"){
    PacMan pacman(100, 100);
    Maze maze;
    maze.initialiseCustomWalls();

    // Checks for valid right movement
    int initialX = pacman.getX();
    int initialY = pacman.getY();
    pacman.move(maze, pacman.getFrames(), 1);
    CHECK((initialX + pacman.getDX()*pacman.getFrames()*pacman.getSpeed()) == pacman.getX());
    CHECK((initialY + pacman.getDY()*pacman.getFrames()*pacman.getSpeed()) == pacman.getY());

    // Checks for valid left movement
    initialX = pacman.getX();
    initialY = pacman.getY();
    pacman.move(maze, pacman.getFrames(), 2);
    CHECK((initialX + pacman.getDX()*pacman.getFrames()*pacman.getSpeed()) == pacman.getX());
    CHECK((initialY + pacman.getDY()*pacman.getFrames()*pacman.getSpeed()) == pacman.getY());

    // Checks for valid up movement
    initialX = pacman.getX();
    initialY = pacman.getY();
    pacman.move(maze, pacman.getFrames(), 3);
    CHECK((initialX + pacman.getDX()*pacman.getFrames()*pacman.getSpeed()) == pacman.getX());
    CHECK((initialY + pacman.getDY()*pacman.getFrames()*pacman.getSpeed()) == pacman.getY());

    // Checks for valid down movement
    initialX = pacman.getX();
    initialY = pacman.getY();
    pacman.move(maze, pacman.getFrames(), 4);
    CHECK((initialX + pacman.getDX()*pacman.getFrames()*pacman.getSpeed()) == pacman.getX());
    CHECK((initialY + pacman.getDY()*pacman.getFrames()*pacman.getSpeed()) == pacman.getY());
}


