/**
 * @file Lives.cpp
 * @brief Implements the Lives class, which manages the player's remaining lives in the game.
 */

#include "Lives.h"

/**
 * @brief Constructs a Lives object with a specified initial number of lives.
 * 
 * @param initialLives The initial number of lives the player starts with.
 * 
 * Initializes the lives attribute with the given initial number of lives.
 */
Lives::Lives(int initialLives) : lives(initialLives) {}

/**
 * @brief Destructor for the Lives class.
 * 
 * This destructor does not perform any specific actions but is defined for completeness.
 */
Lives::~Lives() {}

/**
 * @brief Decreases the player's lives by one.
 * 
 * If the player has at least one life remaining, this method will decrease the number of lives by one.
 */
void Lives::loseLife() {
    if (lives > 0) {
        lives--;
    }
}

/**
 * @brief Increases the player's lives by one.
 * 
 * This method adds one to the current number of lives, representing an extra life gained by the player.
 */
void Lives::gainLife() {
    lives++;
}

/**
 * @brief Gets the current number of lives remaining.
 * 
 * @return The number of lives remaining as an integer.
 */
int Lives::getLives() const {
    return lives;
}

/**
 * @brief Checks if the player is still alive.
 * 
 * @return true if the player has at least one life remaining, false otherwise.
 */
bool Lives::isAlive() const {
    return lives > 0;
}
