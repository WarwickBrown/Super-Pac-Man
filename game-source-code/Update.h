#ifndef UPDATE_H
#define UPDATE_H

#include "Game.h"
#include "Draw.h"
#include <memory>

class Draw;

class Update {
public:
    // Constructor that takes a reference to the game instance
    explicit Update(Game& game, Draw* drawInstance);

    // Public methods for updating different components
    void updateGame(float deltaTime);
    void updatePowerPellets();
    void updateSuperPellets();
    void updateFruits();
    void updateStars();
    void updateKeys();
    void updateInvincibility(float deltaTime);

private:
    Game& game; // Reference to the Game instance for accessing its members
    Draw* draw;
};

#endif // UPDATE_H