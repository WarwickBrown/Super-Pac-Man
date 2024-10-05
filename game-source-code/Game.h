#ifndef GAME_H
#define GAME_H

#include <vector>
#include <raylib-cpp.hpp>
#include <memory>
#include "Maze.h"
#include "PacMan.h"
#include "Draw.h"
#include "Fruit.h"
#include "GameKey.h"
#include "Star.h"
#include "Score.h"
#include "Lives.h"
#include "Screen.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Update.h"
#include "PacManManager.h"
#include "Ghost.h"  

// Forward declaration of various classes to allow Game class to reference them
class Draw;
class Screen;
class GameInitialiser;
class Update;
class PacManManager;

class Game {
    enum Direction {
        RIGHT = 1,
        LEFT,
        UP,
        DOWN,
        NONE
    };
    friend class GameInitialiser;
    friend class PacManManager;
    friend class Update;
public:
    Game();  // Constructor - Initialises game properties and sets up the game window
    ~Game(); // Destructor - Cleans up dynamically allocated memory

    void initialise();
    void run();
    void handleInput();
    void update();
    void checkWinCondition();

    // Setter functions
    void setUpdater(std::unique_ptr<Update> updater) { this->updater = std::move(updater); }
    void setPacManManager(std::unique_ptr<PacManManager> pacManManager) { this->pacManManager = std::move(pacManManager); }

    // Getter functions
    const std::vector<Texture2D>& getGameImages() const;
    std::vector<Fruit*>& getFruits();
    std::vector<PowerPellet*>& getPowerPellets();
    std::vector<SuperPellet*>& getSuperPellets();
    std::vector<Ghost*>& getGhosts();

    Maze& getMaze() const { return *maze; } 
    PacMan& getPacMan() const { return *pacMan; }
    Screen& getScreen() const { return *screen; }
    Score& getScore() const { return *score; }
    Lives& getPlayerLives() const { return *playerLives; }

    bool isGameWon() const { return gameWon; }
    bool isGameRunning() const { return isRunning; }
    Direction getDirection() const { return pacManDirection; }

    void setMaze(std::unique_ptr<Maze> maze) { this->maze = std::move(maze); }
    void setPacMan(std::unique_ptr<PacMan> pacMan) { this->pacMan = std::move(pacMan); }
    void setScreen(std::unique_ptr<Draw> draw) { this->draw = std::move(draw); }
    void addGhost(std::unique_ptr<Ghost> ghost) { ghosts.push_back(std::move(ghost)); }
    void addFruit(std::unique_ptr<Fruit> fruit) { fruits.push_back(std::move(fruit)); }
    void addPowerPellet(std::unique_ptr<PowerPellet> powerPellet) { powerPellets.push_back(std::move(powerPellet)); }
    void addSuperPellet(std::unique_ptr<SuperPellet> superPellet) { superPellets.push_back(std::move(superPellet)); }
    void addKey(GameKey key) { keys.push_back(std::move(key)); }
    void addStar(std::unique_ptr<Star> star) { stars.push_back(std::move(star)); }

private:
    std::vector<GameKey> keys;

    std::unique_ptr<Maze> maze;
    std::unique_ptr<PacMan> pacMan;
    std::unique_ptr<Screen> screen;
    std::unique_ptr<Draw> draw;
    std::unique_ptr<Score> score;
    std::unique_ptr<Lives> playerLives;
    std::unique_ptr<Update> updater;
    std::unique_ptr<PacManManager> pacManManager;

    std::vector<std::unique_ptr<Ghost>> ghosts;
    std::vector<std::unique_ptr<Fruit>> fruits;
    std::vector<std::unique_ptr<PowerPellet>> powerPellets;
    std::vector<std::unique_ptr<SuperPellet>> superPellets;
    std::vector<std::unique_ptr<Star>> stars;
    
    bool isRunning;
    int totalFrames = 1;
    Direction pacManDirection, ghostDirection, pacManOldDirection = RIGHT;
    raylib::Window window;
    int frame;
    bool gameWon;
    int symbolCounter = 0;
    float timerStart = GetTime();
    int multi = 0, multi2 = 1;
    int num1 = 1, num2 = 1, num3 = 1;
    float powerPelletTimer;
};

#endif // GAME_H
