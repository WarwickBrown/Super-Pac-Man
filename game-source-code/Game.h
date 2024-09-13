#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Screen.h"

// Forward declaration of the Screen class
class Screen;
class Game {
public:
    Game();  // Constructor
    ~Game(); // Destructor

    void initialize();   // Initializes the game
    void initiliseGameImages();
    void run();          // Main game loop
    void handleInput();  // Handles user input
    void update();       // Updates game state
    void render();       // Renders game objects
    //void checkCollisions(); // Checks for collisions between objects
    void endGame();      // Ends the game
    const std::vector<Texture2D>& getGameImages() const;

private:
    std::vector<Texture2D> gameImages;
    Maze* maze;  // Pointer to the maze
    PacMan* pacMan;  // Pointer to Pac-Man
    Screen* screen;
    bool isRunning;  // Game running state
    int dir;
    raylib::Window window;  // Game window
    int frame;
    Texture2D arrowKeyImage;

    void initializeGameObjects(); // Initializes game objects
};

#endif // GAME_H
