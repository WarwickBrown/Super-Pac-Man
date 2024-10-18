/**
 * @file Lives.h
 * @brief Defines the Lives class, which manages the player's remaining lives in the game.
 */

#ifndef LIVES_H
#define LIVES_H

/**
 * @class Lives
 * @brief Represents and manages the player's lives in the game.
 * 
 * The Lives class keeps track of the number of lives the player has left. It provides methods to 
 * decrease or increase the number of lives and to check if the player is still alive.
 */
class Lives {
public:
    /**
     * @brief Constructs a Lives object with a specified initial number of lives.
     * 
     * @param initialLives The initial number of lives the player starts with.
     */
    Lives(int initialLives);

    /**
     * @brief Destructor for the Lives class.
     */
    ~Lives();

    /**
     * @brief Decreases the player's lives by one.
     * 
     * If the player has at least one life remaining, this method will decrease the number of lives.
     */
    void loseLife();

    /**
     * @brief Increases the player's lives by one.
     * 
     * This method adds one to the current number of lives, representing an extra life gained by the player.
     */
    void gainLife();

    /**
     * @brief Gets the current number of lives remaining.
     * 
     * @return The number of lives remaining as an integer.
     */
    int getLives() const;

    /**
     * @brief Checks if the player is still alive.
     * 
     * @return true if the player has at least one life remaining, false otherwise.
     */
    bool isAlive() const;

private:
    int lives; ///< The number of lives remaining for the player.
};

#endif // LIVES_H