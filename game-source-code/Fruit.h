/**
 * @file Fruit.h
 * @brief Defines the Fruit class, derived from the Collectable class, used to represent fruit collectables in the game.
 */

#ifndef FRUIT_H
#define FRUIT_H

#include "Collectable.h"

/**
 * @class Fruit
 * @brief A class representing a fruit collectable item in the game.
 * 
 * The Fruit class inherits from the Collectable class and represents fruit objects
 * that Pac-Man can collect to earn points or trigger events in the game.
 */
class Fruit : public Collectable {
public:
    /**
     * @brief Constructs a Fruit object with a specified position.
     * 
     * @param x The x-coordinate of the fruit.
     * @param y The y-coordinate of the fruit.
     */
    Fruit(float x, float y);

    /**
     * @brief Destructor for the Fruit class.
     * 
     * Cleans up any resources associated with the Fruit object.
     */
    ~Fruit();

private:
    // No additional private members or methods for now.
};

#endif // FRUIT_H