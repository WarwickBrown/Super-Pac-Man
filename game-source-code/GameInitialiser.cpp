/**
 * @file GameInitialiser.cpp
 * @brief Implements the GameInitialiser class, which handles the initialisation of various game objects and collectables.
 */

#include "GameInitialiser.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "Game.h"

/**
 * @brief Initialises the primary game objects such as the maze, Pac-Man, screen, and ghosts.
 * 
 * @param game The Game instance to which the objects are added.
 * 
 * This function sets up the main game objects using `std::make_unique` for memory management.
 */
void GameInitialiser::initialiseGameObjects(Game& game) {
    game.maze = std::make_unique<Maze>();  ///< Initialise the maze object.
    game.pacMan = std::make_unique<PacMan>(game.maze->getStartX(), game.maze->getStartY());  ///< Initialise Pac-Man at the start position.
    game.screen = std::make_unique<Screen>();  ///< Initialise the screen object.
    game.draw = std::make_unique<Draw>();  ///< Initialise the draw object.
    game.updater = std::make_unique<Update>(game, game.draw.get());
    game.pacManManager = std::make_unique<PacManManager>(game);

    game.maze->initialiseCustomWalls();                 // Sets up custom walls for the maze
    game.pacMan->setDirection(PacMan::NONE);            // Sets Pac-Man's initial direction to none
    game.score = std::make_unique<Score>("highscore.txt"); // Initialises the score object
    game.playerLives = std::make_unique<Lives>(3);      // Initialises player lives

    // Initialise the ghosts at specific positions
    game.ghosts.push_back(std::make_unique<Ghost>(685, 445, 250.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(765, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(845, 445, 200.0f));

   initialiseCollectables(game);
}

/**
 * @brief Initialises the collectables at specific positions on the game map.
 * 
 * @param game The Game instance to which the collectables are extracted.
 * 
 * Collectables are special objects that may provide additional points or effects when collected.
 */
void GameInitialiser::initialiseCollectables(Game& game)
{
    Reader reader("../resources/database-textfiles/collectables.txt");  ///< Create a Reader object to read the collectables file.
    reader.readFile();                                                  ///< Read the file content into the `data` vector.
    const auto data = reader.getData();                                 ///< Get the file data.

    for (const auto& line : data) {
        std::istringstream iss(line);
        std::string collectableType;
        iss >> collectableType;

        if (collectableType.empty()) continue;  // Skip empty lines

        // Delegate processing based on collectable type
        if (collectableType == "Fruit") {
            processFruit(game, iss);
        } 
        else if (collectableType == "SuperPellet") {
            processSuperPellet(game, iss);
        } 
        else if (collectableType == "PowerPellet") {
            processPowerPellet(game, iss);
        } 
        else if (collectableType == "Key") {
            processKey(game, iss);
        } 
        else if (collectableType == "Star") {
            processStar(game, iss);
        }
        else {
            std::cerr << "Unknown collectable type: " << collectableType << std::endl;
        }
    }
}

/**
 * @brief Initialises the fruit at specific positions on the game map.
 * 
 * @param game The Game instance to which the fruit are added.
 * @param iss Data line that contains the fruits coordinates.
 * 
 * Fruits are special objects that provide additional points when collected.
 */
void GameInitialiser::processFruit(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.fruits.emplace_back(std::make_unique<Fruit>(x, y));
    } else {
        std::cerr << "Error reading Fruit data." << std::endl;
    }
}

/**
 * @brief Initialises the Super Pellets at specific positions on the game map.
 * 
 * @param game The Game instance to which the Super Pellets are added.
 * @param iss Data line that contains the Super Pellets coordinates.
 * 
 * Super Pellets are special objects that provide additional effects when collected.
 */
void GameInitialiser::processSuperPellet(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.superPellets.emplace_back(std::make_unique<SuperPellet>(x, y));
    } else {
        std::cerr << "Error reading SuperPellet data." << std::endl;
    }
}

/**
 * @brief Initialises the Power Pellets at specific positions on the game map.
 * 
 * @param game The Game instance to which the Power Pellets are added.
 * @param iss Data line that contains the Power Pellets coordinates.
 * 
 * Power Pellets are special objects that provide additional effects when collected.
 */
void GameInitialiser::processPowerPellet(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.powerPellets.emplace_back(std::make_unique<PowerPellet>(x, y));
    } else {
        std::cerr << "Error reading PowerPellet data." << std::endl;
    }
}

/**
 * @brief Initialises the keys at specific positions on the game map.
 * 
 * @param game The Game instance to which the keys are added.
 * @param iss Data line that contains the keys coordinates.
 * 
 * Keys are special objects that unlock doors when collected.
 */
void GameInitialiser::processKey(Game& game, std::istringstream& iss)
{
    int x, y, doorNumber1Overlay, doorNumber1, doorNumber2Overlay, doorNumber2;
    if (iss >> x >> y >> doorNumber1Overlay >> doorNumber1 >> doorNumber2Overlay >> doorNumber2) {
        game.keys.emplace_back(x, y, std::vector<int>{doorNumber1Overlay, doorNumber1, doorNumber2Overlay, doorNumber2});
    } else {
        std::cerr << "Error reading Key data." << std::endl;
    }
}

/**
 * @brief Initialises the star at specific positions on the game map.
 * 
 * @param game The Game instance to which the star is added.
 * @param iss Data line that contains the star coordinates.
 * 
 * Stars are special objects that provide additional points when collected.
 */
void GameInitialiser::processStar(Game& game, std::istringstream& iss) {
    int x, y;
    if (iss >> x >> y) {
        game.stars.emplace_back(std::make_unique<Star>(x, y));
    } else {
        std::cerr << "Error reading Fruit data." << std::endl;
    }
}