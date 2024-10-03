#include "GameInitialiser.h"
#include "Game.h"

void GameInitialiser::initialiseGameObjects(Game& game) {
    game.maze = std::make_unique<Maze>();  // initialise using make_unique
    game.pacMan = std::make_unique<PacMan>(game.maze->getStartX(), game.maze->getStartY());
    game.screen = std::make_unique<Screen>();  // initialise the screen
    game.draw = std::make_unique<Draw>();  // initialise the screen

    game.ghosts.push_back(std::make_unique<Ghost>(685, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(765, 445, 150.0f));
    game.ghosts.push_back(std::make_unique<Ghost>(845, 445, 150.0f));
}

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
    game.fruits.emplace_back(std::make_unique<Fruit>(520, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 680));

    //Bottom Right Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(1000, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(1160, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 600));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 680));

    //Bottom Left Big L
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 360));
    game.fruits.emplace_back(std::make_unique<Fruit>(280, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(360, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(520, 440));

    //Bottom Right Big L
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 360));
    game.fruits.emplace_back(std::make_unique<Fruit>(1240, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(1000, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 440));
    game.fruits.emplace_back(std::make_unique<Fruit>(1160, 440));

    //Top Left Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(440, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(520, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(680, 280));

    //Top Right Small L
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 200));
    game.fruits.emplace_back(std::make_unique<Fruit>(1080, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(840, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(920, 280));
    game.fruits.emplace_back(std::make_unique<Fruit>(1000, 280));

    //Upper Symbol
    game.fruits.emplace_back(std::make_unique<Fruit>(600, 120));
    game.fruits.emplace_back(std::make_unique<Fruit>(680, 120));
    game.fruits.emplace_back(std::make_unique<Fruit>(760, 120));
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
}

void GameInitialiser::initialisePowerPellets(Game& game) {
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 760)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 760)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(120, 200)); 
    game.powerPellets.emplace_back(std::make_unique<PowerPellet>(1400, 200)); 
}

void GameInitialiser::initialiseSuperPellets(Game& game) {
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(600, 600));
    game.superPellets.emplace_back(std::make_unique<SuperPellet>(920, 600));
}

void GameInitialiser::initialiseKeys(Game& game) {
    // Top Left Box
    game.keys.emplace_back(40, 120, std::vector<int>{0, 1, 2, 3});
    // Top Right Box
    game.keys.emplace_back(1480, 120, std::vector<int>{4, 5, 6, 7});
    // Bottom Left
    game.keys.emplace_back(40, 840, std::vector<int>{8, 9, 10 , 11});
    // Bottom Right Box
    game.keys.emplace_back(1480, 840, std::vector<int>{12, 13, 14, 15});
    //Left Long Wall
    game.keys.emplace_back(40, 440, std::vector<int>{16, 17 , 18, 19});
    //Right Long Wall
    game.keys.emplace_back(1480, 440, std::vector<int>{20, 21, 22, 23});
    // Big L Left
    game.keys.emplace_back(360, 360, std::vector<int>{24, 25, 26, 27});
    // Big L Right
    game.keys.emplace_back(1160, 360, std::vector<int>{28, 29, 30, 31});
    // Left Top Small L
    game.keys.emplace_back(520, 200, std::vector<int>{32, 33, 34, 35});
    // Right Top Small L
    game.keys.emplace_back(1000, 200, std::vector<int>{36, 37, 38, 39});
    // Upper Symbol
    game.keys.emplace_back(760, 280, std::vector<int>{40, 41, 42, 43});
    // Left Bottom Small L 
    game.keys.emplace_back(280, 520, std::vector<int>{44, 45, 48, 49});
    // Right Bottom Small L 
    game.keys.emplace_back(1240, 520, std::vector<int>{50, 51, 54, 55});
    // Bottom Left Short 
    game.keys.emplace_back(360, 680, std::vector<int>{56, 57, 58, 59});
    // Bottom Right Short
    game.keys.emplace_back(1160, 680, std::vector<int>{60, 61, 62, 63});
    // Bottom T-Shaped 
    game.keys.emplace_back(760, 680, std::vector<int>{64, 65, 66, 67});
    game.keys.emplace_back(680, 760, std::vector<int>{46, 47, 68, 69});
    game.keys.emplace_back(840, 760, std::vector<int>{52, 53, 70, 71});
}

void GameInitialiser::initialiseStars(Game& game) {
    game.stars.emplace_back(std::make_unique<Star>(760, 600));
}