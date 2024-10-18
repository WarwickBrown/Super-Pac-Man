/**
 * @file Lives.cpp
 * @brief Implements the Lives class, which manages the player's remaining lives in the game.
 */

#include "Lives.h"

Lives::Lives(int initialLives) : lives(initialLives) {}

Lives::~Lives() {}

void Lives::loseLife() {
    if (lives > 0) {
        lives--;
    }
}

void Lives::gainLife() {
    lives++;
}

int Lives::getLives() const {
    return lives;
}

bool Lives::isAlive() const {
    return lives > 0;
}