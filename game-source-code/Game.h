/**
 * @file Game.h
 * @brief Defines the Game class, which manages the overall game logic and controls the flow of the game.
 */

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
#include "SoundManager.h"

/**
 * @class Game
 * @brief Manages the entire game flow, state, and rendering of various elements in the Pac-Man game.
 * 
 * This class is responsible for initialising, updating, and running the game loop. It handles
 * user inputs, updates game objects, checks win conditions, and renders the game elements on the screen.
 */

// Forward declaration of various classes to allow Game class to reference them
class Draw;
class Screen;
class GameInitialiser;
class Update;
class PacManManager;

class Game {

    friend class GameInitialiser;
    friend class PacManManager;
    friend class Update;

public:
    /**
     * @brief Constructs a Game object, initialising the game window and other variables.
     */
    Game();

    /**
     * @brief Destructor for the Game class, releasing dynamically allocated resources.
     */
    ~Game();

    /**
     * @brief Initialises game objects, such as Pac-Man, ghosts, maze, and collectables.
     * 
     * @param skipStartScreen Allows for the skipping of the start screen when set to true.
     */
    void initialise(bool skipStartScreen = false);

    /**
     * @brief Runs the main game loop, handling input, updating, and rendering game elements.
     */
    void run();

    /**
     * @brief Handles user input for controlling Pac-Man's movement.
     * 
     * @param inputKey The key input for controlling movement (optional).
     */
    void handleInput(int inputKey);

    /**
     * @brief Updates the state of the game and its elements.
     */
    void update();

    /**
     * @brief Checks if the win condition has been met (i.e., all fruits collected).
     */
    void checkWinCondition();

    /**
     * @brief Retrieves a list of fruit pointers for accessing and modifying fruit objects.
     * 
     * @return A vector of pointers to Fruit objects.
     */
    std::vector<Fruit*>& getFruits();

        /**
     * @brief Retrieves a reference to the internal vector of power pellet unique pointers.
     * 
     * @return A reference to the vector of unique pointers to PowerPellet objects.
     */
    const std::vector<std::unique_ptr<PowerPellet>>& getPowerPellets() const { return powerPellets; }

    /**
     * @brief Retrieves a reference to the internal vector of super pellet unique pointers.
     * 
     * @return A reference to the vector of unique pointers to SuperPellet objects.
     */
    const std::vector<std::unique_ptr<SuperPellet>>& getSuperPellets() const { return superPellets; }

    /**
     * @brief Retrieves a reference to the internal vector of ghost unique pointers.
     * 
     * @return A reference to the vector of unique pointers to Ghost objects.
     */
    const std::vector<std::unique_ptr<Ghost>>& getGhosts() const { return ghosts; }

    /**
     * @brief Retrieves a list of game keys for accessing and modifying key objects.
     * 
     * @return A vector of GameKey objects.
     */
    std::vector<GameKey>& getKeys() { return keys; }

    /**
     * @brief Gets a reference to the Maze object used in the game.
     * 
     * @return A reference to the Maze object.
     */
    Maze& getMaze() const { return *maze; }

    /**
     * @brief Gets a reference to the Pac-Man object used in the game.
     * 
     * @return A reference to the Pac-Man object.
     */
    PacMan& getPacMan() const { return *pacMan; }

    /**
     * @brief Gets a reference to the Screen object used for rendering screens.
     * 
     * @return A reference to the Screen object.
     */
    Screen& getScreen() const { return *screen; }

    /**
     * @brief Gets a reference to the Score object used for tracking scores.
     * 
     * @return A reference to the Score object.
     */
    Score& getScore() const { return *score; }

    /**
     * @brief Gets a reference to the Lives object used for tracking remaining lives.
     * 
     * @return A reference to the Lives object.
     */
    Lives& getPlayerLives() const { return *playerLives; }

    /**
     * @brief Checks if the game has been won.
     * 
     * @return true if the game has been won, false otherwise.
     */
    bool isGameWon() const { return gameWon; }

    /**
     * @brief Checks if the game is currently running.
     * 
     * @return true if the game is running, false otherwise.
     */
    bool isGameRunning() const { return isRunning; }

    /**
     * @brief Gets the current movement direction of Pac-Man.
     * 
     * @return The current Direction enum value.
     */
    PacMan::Direction getDirection() const { return pacManDirection; }

    /**
     * @brief Sets the maze object for the game.
     * 
     * @param maze A unique pointer to the Maze object to be set.
     */
    void setMaze(std::unique_ptr<Maze> maze) { this->maze = std::move(maze); }

    /**
     * @brief Sets the Pac-Man object for the game.
     * 
     * @param pacMan A unique pointer to the Pac-Man object to be set.
     */
    void setPacMan(std::unique_ptr<PacMan> pacMan) { this->pacMan = std::move(pacMan); }

    /**
     * @brief Sets the screen object for rendering screens.
     * 
     * @param draw A unique pointer to the Draw object to be set.
     */
    void setScreen(std::unique_ptr<Draw> draw) { this->draw = std::move(draw); }

    /**
     * @brief Sets the updater object for handling game updates.
     * 
     * @param updater A unique pointer to the Update object to be set.
     */
    void setUpdater(std::unique_ptr<Update> updater) { this->updater = std::move(updater); }

    /**
     * @brief Sets the Pac-Man manager object for managing Pac-Man-specific updates.
     * 
     * @param pacManManager A unique pointer to the PacManManager object to be set.
     */
    void setPacManManager(std::unique_ptr<PacManManager> pacManManager) { this->pacManManager = std::move(pacManManager); }

    /**
     * @brief Retrieves the updater object for the game.
     * 
     * @return A pointer to the `Update` class instance managing game updates.
     */
    Update* getUpdater() const { return updater.get(); }

    /**
     * @brief Sets the Pac-Man manager object for managing Pac-Man-specific updates.
     * 
     * @param powerPelletTimer A unique pointer to the PacManManager object to be set.
     */
    void setPowerPelletTimer(float powerPelletTimerNew) { this->powerPelletTimer = powerPelletTimerNew; }

    /**
     * @brief Retrieves the draw object for the game.
     * 
     * @return A reference to the `Draw` class instance managing game drawing.
     */
    Draw& getDraw() const { return *draw; } ///< Getter for the Draw object
    /**
     * @brief Retrieves a reference to the original vector of Star objects.
     * 
     * @return A reference to the vector of std::unique_ptr<Star> objects.
     */
    std::vector<std::unique_ptr<Star>>& getStarObjects();

    /**
     * @brief Retrieves a reference to the original vector of Fruit objects.
     * 
     * @return A reference to the vector of std::unique_ptr<Fruit> objects.
     */
    std::vector<std::unique_ptr<Fruit>>& getFruitObjects();

private:
    std::vector<GameKey> keys; ///< A vector of GameKey objects representing keys in the game.
    std::unique_ptr<Maze> maze; ///< Unique pointer to the Maze object.
    std::unique_ptr<PacMan> pacMan; ///< Unique pointer to the Pac-Man object.
    std::unique_ptr<Screen> screen; ///< Unique pointer to the Screen object.
    std::unique_ptr<Draw> draw; ///< Unique pointer to the Draw object.
    std::unique_ptr<Score> score; ///< Unique pointer to the Score object.
    std::unique_ptr<Lives> playerLives; ///< Unique pointer to the Lives object.
    std::unique_ptr<Update> updater; ///< Unique pointer to the Update object.
    std::unique_ptr<PacManManager> pacManManager; ///< Unique pointer to the PacManManager object.
    std::unique_ptr<SoundManager> soundManager; ///< Unique pointer to the SoundManager object.
    std::vector<std::unique_ptr<Ghost>> ghosts; ///< Vector of unique pointers to Ghost objects.
    std::vector<std::unique_ptr<Fruit>> fruits; ///< Vector of unique pointers to Fruit objects.
    std::vector<std::unique_ptr<PowerPellet>> powerPellets; ///< Vector of unique pointers to PowerPellet objects.
    std::vector<std::unique_ptr<SuperPellet>> superPellets; ///< Vector of unique pointers to SuperPellet objects.
    std::vector<std::unique_ptr<Star>> stars; ///< Vector of unique pointers to Star objects.

    PacMan::Direction pacManDirection; ///< Current direction of Pac-Man's movement.
    PacMan::Direction ghostDirection; ///< Current direction of ghost movement.
    PacMan::Direction pacManOldDirection = PacMan::RIGHT; ///< Previous direction of Pac-Man's movement.
    raylib::Window window; ///< Window object for rendering the game.
    bool isRunning; ///< Indicates if the game is currently running.
    int frame; ///< Current animation frame.
    int totalFrames = 1; ///< Total number of frames rendered.
    int symbolCounter = 0; ///< Counter for symbol animations.
    int multi = 0, multi2 = 1; ///< Multipliers for game mechanics.
    int fruitSymbolOne = 1, fruitSymbolTwo = 1, fruitSymbolInMaze = 1; ///< Numbers for texture selection.
    bool gameWon; ///< Indicates if the game has been won.
    float timerStart = GetTime(); ///< Start time of the game.
    float powerPelletTimer; ///< Timer for tracking power pellet effects.
};

#endif // GAME_H