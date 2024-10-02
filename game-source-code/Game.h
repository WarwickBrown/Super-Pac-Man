#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib-cpp.hpp>
#include <memory>
#include "Maze.h"
#include "PacMan.h"
#include "Screen.h"
#include "Fruit.h"
#include "Ghost.h"
#include "GameKey.h"
#include "Star.h"
#include "Score.h"
#include "Lives.h"
#include "PowerPellet.h"
#include "SuperPellet.h"

// Forward declaration of the Screen class to allow Game class to reference it
class Screen;
class Ghost;
class GameInitialiser;

class Game {
    friend class GameInitialiser;
public:
    Game();  // Constructor - Initialises game properties and sets up the game window
    ~Game(); // Destructor - Cleans up dynamically allocated memory

    void initialise();   // Initialises the game (calls functions to setup game objects, loads images, etc.)
    void run();          // Main game loop - Handles input, updates the game state, and renders the game
    void handleInput();  // Handles user input (e.g., arrow keys for controlling Pac-Man)
    void update();       // Updates the game state (e.g., moves Pac-Man and updates positions)
    void updatePowerPellets();
    void updateSuperPellets();
    void updateStars();
    void updateInvincibility(float deltaTime);
    void updateKeys();
    void updateFruits();

    void render();       // Renders game objects (maze, Pac-Man, etc.) on the screen
    void endGame();      // Ends the game (shows game over screen or exits)
    void checkWinCondition(); // Add this method to check the win condition
    void inputStar();

    
// Getter functions
    const std::vector<Texture2D>& getGameImages() const;
    std::vector<Fruit*>& getFruits();                 // Return raw pointers to Fruit
    std::vector<PowerPellet*>& getPowerPellets();     // Return raw pointers to PowerPellet
    std::vector<SuperPellet*>& getSuperPellets();     // Return raw pointers to SuperPellet
    std::vector<Ghost*>& getGhosts();                 // Return raw pointers to Ghost
    Maze* getMaze() const;                            // Return raw pointer to Maze
    PacMan* getPacMan() const;                        // Return raw pointer to PacMan
    Screen* getScreen() const;                        // Return raw pointer to Screen
    Score* getScore() const;                          // Return raw pointer to Score
    Lives* getPlayerLives() const;                    // Return raw pointer to Lives

    bool isGameWon() const { return gameWon; }
    bool isGameRunning() const { return isRunning; }
    int getDirection() const { return direction; }

    void setMaze(std::unique_ptr<Maze> maze) { this->maze = std::move(maze); }
    void setPacMan(std::unique_ptr<PacMan> pacMan) { this->pacMan = std::move(pacMan); }
    void setScreen(std::unique_ptr<Screen> screen) { this->screen = std::move(screen); }
    void addGhost(std::unique_ptr<Ghost> ghost) { ghosts.push_back(std::move(ghost)); }
    void addFruit(std::unique_ptr<Fruit> fruit) { fruits.push_back(std::move(fruit)); }
    void addPowerPellet(std::unique_ptr<PowerPellet> powerPellet) { powerPellets.push_back(std::move(powerPellet)); }
    void addSuperPellet(std::unique_ptr<SuperPellet> superPellet) { superPellets.push_back(std::move(superPellet)); }
    void addKey(GameKey key) { keys.push_back(std::move(key));}
    void addStar(std::unique_ptr<Star> star) { stars.push_back(std::move(star)); }

private:
    std::vector<GameKey> keys;
    std::vector<Texture2D> gameImages;  // Vector to hold game-related images (e.g., arrow key instructions)
    std::vector<std::unique_ptr<Ghost>> ghosts;
    std::vector<std::unique_ptr<Fruit>> fruits;
    std::vector<std::unique_ptr<PowerPellet>> powerPellets;
    std::vector<std::unique_ptr<SuperPellet>> superPellets;
    std::vector<std::unique_ptr<Star>> stars;

    // Using smart pointers for game objects
    std::unique_ptr<Maze> maze;
    std::unique_ptr<PacMan> pacMan;
    std::unique_ptr<Screen> screen;
    std::unique_ptr<Score> score;
    std::unique_ptr<Lives> playerLives;
    
    bool isRunning;  // Boolean to track whether the game is running or not
    int totalFrames = 1;
    int direction, ghostDirection;         // Integer representing the direction Pac-Man is moving (right, left, up, down)
    int oldDirection = 2;
    raylib::Window window;  // The game window where the game will be rendered
    int frame;       // Current frame number (used for animation)
    bool gameWon;    // Track if the game is won
    int symbolCounter = 0;
    float timerStart = GetTime();
    int multi = 0, multi2 = 1;
    int num1 = 1, num2 = 1, num3 = 1;
    float powerPelletTimer;
};

#endif // GAME_H