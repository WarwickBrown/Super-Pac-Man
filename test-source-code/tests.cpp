#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PacMan.h"
#include "Maze.h"

// // Test Pac-Man Movement within the Maze
// TEST_CASE("PacMan Movement") {
//     Maze maze;  // Create a maze instance
//     PacMan pacMan(32, 32);  // Pac-Man starts at (32, 32) pixels, corresponding to grid (1, 1)
    
//     // Set deltaTime to a value that ensures movement happens in the test
//     float deltaTime = 1.0f / 60.0f;  // Equivalent to one frame at 60 FPS

//     SUBCASE("Move Right into Empty Space") {
//        // pacMan.setDirection(1, 0);  // Set direction to right
//      //   pacMan.move(maze, deltaTime);  // Move Pac-Man
//         CHECK(pacMan.getX() == 33);  // Expect Pac-Man to move right, so x = 33
//         CHECK(pacMan.getY() == 32);  // Y should remain the same
//     }

//     SUBCASE("Move Left into Wall") {
//       //  pacMan.setDirection(-1, 0);  // Set direction to left
//      //   pacMan.move(maze, deltaTime);  // Move Pac-Man
//         CHECK(pacMan.getX() == 32);  // Expect Pac-Man to not move into the wall, so x = 32
//         CHECK(pacMan.getY() == 32);  // Y should remain the same
//     }

//     SUBCASE("Move Up into Wall") {
//      //   pacMan.setDirection(0, -1);  // Set direction to up
//      //   pacMan.move(maze, deltaTime);  // Move Pac-Man
//         CHECK(pacMan.getY() == 32);  // Pac-Man should not move into the wall, so y = 32
//         CHECK(pacMan.getX() == 32);  // X should remain the same
//     }

//     SUBCASE("Move Down into Empty Space") {
//     //    pacMan.setDirection(0, 1);  // Set direction to down
//     //    pacMan.move(maze, deltaTime);  // Move Pac-Man
//         CHECK(pacMan.getY() == 33);  // Expect Pac-Man to move down, so y = 33
//         CHECK(pacMan.getX() == 32);  // X should remain the same
//     }
// }

// // Test Maze Collision Detection
// TEST_CASE("Maze Collision Detection") {
//     Maze maze;  // Initialize maze with default layout

//     SUBCASE("Check Wall Collision") {
//         CHECK(maze.isWall(0, 0) == true);  // Expect top-left corner to be a wall
//         CHECK(maze.isWall(5, 5) == false);  // Expect an open path at (5, 5)
//     }

//     SUBCASE("Check Open Path") {
//         CHECK(maze.isWall(1, 1) == false);  // Expect (1, 1) to be an open path
//     }
// }
