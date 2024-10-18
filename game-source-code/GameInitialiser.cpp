/**
 * @file GameInitialiser.cpp
 * @brief Implements the GameInitialiser class, which handles the initialisation of various game objects and collectables.
 */

#include "GameInitialiser.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "Game.h"

void GameInitialiser::initialiseGameObjects(Game& game) {
    game.maze = std::make_unique<Maze>();  ///< Initialise the maze object.
    game.pacMan = std::make_unique<PacMan>(game.maze->getStartX(), game.maze->getStartY());  ///< Initialise Pac-Man at the start position.
    game.screen = std::make_unique<Screen>();  ///< Initialise the screen object.
    game.draw = std::make_unique<Draw>();  ///< Initialise the draw object.
    game.updater = std::make_unique<Update>(game, game.draw.get());
    game.pacManManager = std::make_unique<PacManManager>(game);
    game.soundManager = std::make_unique<SoundManager>();

    game.maze->initialiseCustomWalls();                 // Sets up custom walls for the maze
    game.pacMan->setDirection(PacMan::NONE);            // Sets Pac-Man's initial direction to none
    game.score = std::make_unique<Score>("highscore.txt"); // Initialises the score object
    game.playerLives = std::make_unique<Lives>(3);      // Initialises player lives

    // Initialise the ghosts at specific positions
    game.ghosts.push_back(std::make_unique<Ghost>(685, 445, 250.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(765, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(845, 445, 200.0f));

    initialiseCollectables(game);
    SetTargetFPS(480);
}

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
    }
}

void GameInitialiser::processFruit(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.fruits.emplace_back(std::make_unique<Fruit>(x, y));
    } else {
        std::cerr << "Error reading Fruit data." << std::endl;
    }
}

void GameInitialiser::processSuperPellet(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.superPellets.emplace_back(std::make_unique<SuperPellet>(x, y));
    } else {
        std::cerr << "Error reading SuperPellet data." << std::endl;
    }
}

void GameInitialiser::processPowerPellet(Game& game, std::istringstream& iss)
{
    int x, y;
    if (iss >> x >> y) {
        game.powerPellets.emplace_back(std::make_unique<PowerPellet>(x, y));
    } else {
        std::cerr << "Error reading PowerPellet data." << std::endl;
    }
}

void GameInitialiser::processKey(Game& game, std::istringstream& iss)
{
    int x, y, doorNumber1Overlay, doorNumber1, doorNumber2Overlay, doorNumber2;
    if (iss >> x >> y >> doorNumber1Overlay >> doorNumber1 >> doorNumber2Overlay >> doorNumber2) {
        game.keys.emplace_back(x, y, std::vector<int>{doorNumber1Overlay, doorNumber1, doorNumber2Overlay, doorNumber2});
    } else {
        std::cerr << "Error reading Key data." << std::endl;
    }
}

void GameInitialiser::processStar(Game& game, std::istringstream& iss) {
    int x, y;
    if (iss >> x >> y) {
        game.stars.emplace_back(std::make_unique<Star>(x, y));
    } else {
        std::cerr << "Error reading Fruit data." << std::endl;
    }
}