/**
 * @file GameInitialiser.cpp
 * @brief Implements the GameInitialiser class, which handles the initialisation of various game objects and collectables.
 */

#include "GameInitialiser.h"
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
    game.ghosts.push_back(std::make_unique<Ghost>(685, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(765, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(845, 445, 150.0f));

    initialiseFruits(game);       // Initialises fruit collectables
    initialiseKeys(game);         // Initialises keys
    initialiseStars(game);        // Initialises stars
    initialisePowerPellets(game); // Initialises power pellets
    initialiseSuperPellets(game); // Initialises super pellets
}

/**
 * @brief Initialises the fruits at specific positions on the game map.
 * 
 * @param game The Game instance to which the fruits are added.
 * 
 * This function places fruits at various locations in a structured manner to form patterns or paths.
 */
void GameInitialiser::initialiseFruits(Game& game) {
    //Left Long Wall
    game.fruits.emplace_back(std::make_unique<Fruit>(120, 360));
    game.fruits.emplace_back(std::make_unique<Fruit>(120, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(120, 520));
    game.fruits.emplace_back(std::make_unique<Fruit>(120, 600));

    //Right Long Wall
    game.fruits.emplace_back(std::make_unique<Fruit>(1400, 360));
    game.fruits.emplace_back(std::make_unique<Fruit>(1400, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(1400, 520));
    game.fruits.emplace_back(std::make_unique<Fruit>(1400, 600));

    //Bottom Left Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(360, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 680));

    //Bottom Right Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(1160, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 680));

    //Bottom Left Big L
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(520, 440));

    //Bottom Right Big L
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(1000, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 440));

    //Top Left Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(680, 280));

    //Top Right Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(840, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 280));

    //Upper Symbol
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 120));
    game.fruits.emplace_back(std::make_unique<Fruit>(680, 120));
    game.fruits.emplace_back(std::make_unique<Fruit>(840, 120));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 120));

    //Bottom Left Small 
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 760));
    game.fruits.emplace_back(std::make_unique<Fruit>(360, 760));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 760));

    //Bottom Right Small 
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 760));
    game.fruits.emplace_back(std::make_unique<Fruit>(1160, 760));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 760));

    // Bottom T
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 840));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 840));
    game.fruits.emplace_back(std::make_unique<Fruit>(840, 840));
    game.fruits.emplace_back(std::make_unique<Fruit>(760, 840));
    game.fruits.emplace_back(std::make_unique<Fruit>(680, 840));
    game.fruits.emplace_back(std::make_unique<Fruit>(760, 760));
}

/**
 * @brief Initialises the power pellets at specific positions on the game map.
 * 
 * @param game The Game instance to which the power pellets are added.
 * 
 * Power pellets provide special abilities or effects when collected by Pac-Man.
 */
void GameInitialiser::initialisePowerPellets(Game& game) {
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 760)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 760)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 200)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 200)); 
}

/**
 * @brief Initialises the super pellets at specific positions on the game map.
 * 
 * @param game The Game instance to which the super pellets are added.
 * 
 * Super pellets grant Pac-Man additional abilities such as invincibility or enhanced speed.
 */
void GameInitialiser::initialiseSuperPellets(Game& game) {
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(600, 600));
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(920, 600));
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(280, 440));
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(1240, 440));
}

/**
 * @brief Initialises the game keys at specific positions on the game map.
 * 
 * @param game The Game instance to which the keys are added.
 * 
 * Keys can be used to unlock certain sections of the maze, providing new pathways or access to collectables.
 */
void GameInitialiser::initialiseKeys(Game& game) {
    // Top Left Box
    game.keys.emplace_back(40, 120, std::vector<int>{0, 1, 2, 3}); //
    // Top Right Box
    game.keys.emplace_back(1480, 120, std::vector<int>{4, 5, 6, 7}); //
    // Bottom Left
    game.keys.emplace_back(40, 840, std::vector<int>{8, 9, 10 , 11}); //
    // Bottom Right Box
    game.keys.emplace_back(1480, 840, std::vector<int>{12, 13, 14, 15}); //
    //Left Long Wall 
    game.keys.emplace_back(40, 440, std::vector<int>{16, 17 , 18, 19}); //
    //Right Long Wall
    game.keys.emplace_back(1480, 440, std::vector<int>{20, 21, 22, 23}); //

    game.keys.emplace_back(360, 200, std::vector<int>{48, 49, 50, 51}); //

    game.keys.emplace_back(1160, 200, std::vector<int>{56, 57, 58, 59}); //

    game.keys.emplace_back(600, 200, std::vector<int>{64, 65, 66, 67}); //

    game.keys.emplace_back(920, 200, std::vector<int>{68, 69, 70, 71}); //

    game.keys.emplace_back(600, 360, std::vector<int>{52, 53, 54, 55}); //

    game.keys.emplace_back(920, 360, std::vector<int>{60, 61, 62, 63}); //

    game.keys.emplace_back(1320, 520, std::vector<int>{40, 41, 42, 43}); //

    game.keys.emplace_back(360, 680, std::vector<int>{72, 73, 74, 75}); //

    game.keys.emplace_back(1160, 680, std::vector<int>{80, 81, 82, 83}); //

    game.keys.emplace_back(680, 680, std::vector<int>{76, 77, 78, 79}); //

    game.keys.emplace_back(600, 760, std::vector<int>{96, 97, 100, 101}); //

    game.keys.emplace_back(920, 760, std::vector<int>{98, 99, 102, 103}); //

    game.keys.emplace_back(1320, 280, std::vector<int>{36, 37, 38, 39}); //

    game.keys.emplace_back(200, 280, std::vector<int>{24, 25, 26, 27}); //

    game.keys.emplace_back(520, 520, std::vector<int>{32, 33, 34, 35}); //

    game.keys.emplace_back(1000, 520, std::vector<int>{44, 45, 46, 47}); //

    game.keys.emplace_back(840, 680, std::vector<int>{84, 85, 86, 87}); //

    game.keys.emplace_back(200, 520, std::vector<int>{28, 29, 30, 31}); //

    game.keys.emplace_back(360, 840, std::vector<int>{88, 89, 90, 91}); //

    game.keys.emplace_back(1160, 840, std::vector<int>{92, 93, 94, 95}); //
}

/**
 * @brief Initialises the stars at specific positions on the game map.
 * 
 * @param game The Game instance to which the stars are added.
 * 
 * Stars are special objects that may provide additional points or effects when collected.
 */
void GameInitialiser::initialiseStars(Game& game) {
    game.stars.emplace_back(std::make_unique<Star>(760, 600));
}