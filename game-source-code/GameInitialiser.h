#pragma once

#include "Game.h"
#include <memory>

class GameInitialiser {
public:
    static void initialiseGameObjects(Game& game);
    static void initialiseFruits(Game& game);
    static void initialisePowerPellets(Game& game);
    static void initialiseSuperPellets(Game& game);
    static void initialiseKeys(Game& game);
    static void initialiseStars(Game& game);
};