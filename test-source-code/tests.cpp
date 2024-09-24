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

// // Test collision detection in a complex maze with doors and walls
// TEST_CASE("Maze collision detection in complex maze with doors") {
//     Maze maze;
//     maze.initialiseCustomWalls();  // Set up the complex maze with doors and walls

//     // Subtest for Pac-Man not colliding with walls in the center of the maze
//     SUBCASE("No collision - Pac-Man in the center of a non-colliding area") {
//         // Simulate Pac-Man's position near the center of the screen (non-colliding)
//         bool collision = maze.isWallRec(765, 525, 34);  // Pac-Man at (765, 525) with radius 34
//         CHECK(collision == false);  // Should not collide if in an open space
//     }

//     // Subtest for Pac-Man colliding with a simple wall
//     SUBCASE("Collision - Pac-Man hitting a basic wall") {
//         // Simulate Pac-Man colliding with a wall
//         bool collision = maze.isWallRec(0, 80, 34);  // Pac-Man at (0, 80) should collide with a wall
//         CHECK(collision == true);  // Should collide with the static wall
//     }

//     // Subtest for Pac-Man colliding with a locked door
//     SUBCASE("Collision - Pac-Man hitting a locked door") {
//         // Simulate a locked door in front of Pac-Man
//         bool collision = maze.isWallRec(90, 160, 34);  // Check collision with the locked door
//         CHECK(collision == true);  // Should collide with the locked door
//     }

//     // Subtest for Pac-Man colliding with a vertical wall
//     SUBCASE("Collision - Pac-Man hitting a vertical wall") {
//         bool collision = maze.isWallRec(80, 160, 34);  // Pac-Man at (80, 160) colliding with a vertical wall
//         CHECK(collision == true);  // Should collide with the vertical wall
//     }

//     // Subtest for Pac-Man colliding with a horizontal wall
//     SUBCASE("Collision - Pac-Man hitting a horizontal wall") {
//         bool collision = maze.isWallRec(560, 800, 34);  // Pac-Man at (560, 800) colliding with a horizontal wall
//         CHECK(collision == true);  // Should collide with the horizontal wall
//     }
// }

// // Tests if direction input changes direction of PacMan
// TEST_CASE("PacMan Direction Changes") {
//     PacMan pacman(0, 0);

//     // Subtest for Pac-Man moving to the right
//     SUBCASE("Pac-Man moves right") {
//         pacman.setDirection(1);  // Right
//         CHECK(pacman.getDX() == 1);
//         CHECK(pacman.getDY() == 0);
//     }

//     // Subtest for Pac-Man moving to the left
//     SUBCASE("Pac-Man moves left") {
//         pacman.setDirection(2);  // Left
//         CHECK(pacman.getDX() == -1);
//         CHECK(pacman.getDY() == 0);
//     }

//     // Subtest for Pac-Man moving down
//     SUBCASE("Pac-Man moves down") {
//         pacman.setDirection(3);  // Down
//         CHECK(pacman.getDX() == 0);
//         CHECK(pacman.getDY() == -1);
//     }

//     // Subtest for Pac-Man moving up
//     SUBCASE("Pac-Man moves up") {
//         pacman.setDirection(4);  // Up
//         CHECK(pacman.getDX() == 0);
//         CHECK(pacman.getDY() == 1);
//     }
// }

// // Tests if Pac-Man has moved correctly
// TEST_CASE("PacMan Movement") {
//     PacMan pacman(100, 100);
//     Maze maze;
//     maze.initialiseCustomWalls();

//     // Subtest for right movement
//     SUBCASE("Valid right movement") {
//         int initialX = pacman.getX();
//         int initialY = pacman.getY();
//         pacman.move(maze, pacman.getFrames(), 1);  // Move right
//         CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
//         CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
//     }

//     // Subtest for left movement
//     SUBCASE("Valid left movement") {
//         int initialX = pacman.getX();
//         int initialY = pacman.getY();
//         pacman.move(maze, pacman.getFrames(), 2);  // Move left
//         CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
//         CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
//     }

//     // Subtest for up movement
//     SUBCASE("Valid up movement") {
//         int initialX = pacman.getX();
//         int initialY = pacman.getY();
//         pacman.move(maze, pacman.getFrames(), 3);  // Move up
//         CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
//         CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
//     }

//     // Subtest for down movement
//     SUBCASE("Valid down movement") {
//         int initialX = pacman.getX();
//         int initialY = pacman.getY();
//         pacman.move(maze, pacman.getFrames(), 4);  // Move down
//         CHECK((initialX + pacman.getDX() * pacman.getFrames() * pacman.getSpeed()) == pacman.getX());
//         CHECK((initialY + pacman.getDY() * pacman.getFrames() * pacman.getSpeed()) == pacman.getY());
//     }
// }

// // Test ghost initialization
// TEST_CASE("Ghost Initialization") {
//     Ghost ghost(100, 100, 150.0f);

//     // Check if ghost is initialized at the correct position
//     CHECK(ghost.getX() == 100);
//     CHECK(ghost.getY() == 100);
    
//     // Check if ghost is not eaten or frightened at start
//     CHECK(ghost.isEaten() == false);
//     CHECK(ghost.isFrightened() == false);
// }

// // Test ghost movement without walls
// TEST_CASE("Ghost Movement Without Walls") {
//     Maze maze;  // Empty maze with no walls
//     Ghost ghost(100, 100, 150.0f);
    
//     // Simulate movement in all four directions without walls
//     float deltaTime = 1.0f;  // Assume 1 second has passed

//     // Right movement
//     ghost.setDirection(1);
//     ghost.move(maze, deltaTime);
//     CHECK(ghost.getX() > 100);  // Ghost should move right
//     CHECK(ghost.getY() == 100);  // Y should stay the same

//     // Left movement
//     ghost.setDirection(2);
//     ghost.move(maze, deltaTime);
//     CHECK(ghost.getX() < 100);  // Ghost should move left
//     CHECK(ghost.getY() == 100);  // Y should stay the same

//     // Up movement
//     ghost.setDirection(3);
//     ghost.move(maze, deltaTime);
//     CHECK(ghost.getX() == 100);  // X should stay the same
//     CHECK(ghost.getY() < 100);  // Ghost should move up

//     // Down movement
//     ghost.setDirection(4);
//     ghost.move(maze, deltaTime);
//     CHECK(ghost.getX() == 100);  // X should stay the same
//     CHECK(ghost.getY() > 100);  // Ghost should move down
// }

// // Test ghost collision with walls
// TEST_CASE("Ghost Collision With Walls") {
//     Maze maze;
//     maze.initialiseCustomWalls();  // Initialize maze with custom walls
//     Ghost ghost(100, 100, 150.0f);

//     // Test collision when ghost hits a wall
//     float deltaTime = 1.0f;

//     // Mock a wall in front of the ghost moving right
//     ghost.setDirection(1);  // Move right
//     ghost.move(maze, deltaTime);
//     CHECK(ghost.getX() == 100);  // Should not move if it hits a wall

//     // Test for ghost choosing a new direction
//     ghost.chooseNewDirection(maze);
//     CHECK(ghost.getDirection() != 1);  // Direction should not still be right
// }

// // Test ghost frightened mode
// TEST_CASE("Ghost Frightened Mode") {
//     Ghost ghost(100, 100, 150.0f);

//     // Set ghost to frightened mode
//     ghost.setFrightened(true);
//     CHECK(ghost.isFrightened() == true);

//     // Reset to normal mode
//     ghost.setFrightened(false);
//     CHECK(ghost.isFrightened() == false);
// }

// // Test ghost respawn behavior
// TEST_CASE("Ghost Respawn") {
//     Ghost ghost(100, 100, 150.0f);

//     // Mark the ghost as eaten and move it
//     ghost.setEaten(true);
//     ghost.setDirection(1);  // Set direction to right
//     float deltaTime = 1.0f;
//     ghost.move(Maze(), deltaTime);  // Move ghost before respawn

//     // Respawn the ghost
//     ghost.respawn();
//     CHECK(ghost.getX() == 100);  // Should reset to the starting position
//     CHECK(ghost.getY() == 100);  // Should reset to the starting position
//     CHECK(ghost.isEaten() == false);  // Ghost should no longer be eaten
// }

// // Test ghost collision with Pac-Man
// TEST_CASE("Ghost Collides With PacMan") {
//     Ghost ghost(100, 100, 150.0f);
//     PacMan pacman(100, 100);  // Pac-Man is close enough to collide

//     CHECK(ghost.checkCollisionWithPacMan(pacman) == true);  // Collision should occur
// }

// TEST_CASE("Ghost Does Not Collide With PacMan") {
//     Ghost ghost(100, 100, 150.0f);
//     PacMan pacman(300, 300);  // Pac-Man is close enough to collide
//     CHECK(ghost.checkCollisionWithPacMan(pacman) == false);  // No collision should occur
// }
