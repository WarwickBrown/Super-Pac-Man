/**
 * @file Fruit.cpp
 * @brief Implements the Fruit class.
 */

#include "Fruit.h"

/**
 * @brief Constructs a Fruit object at the specified position with a default radius of 50.0f.
 * 
 * @param x The x-coordinate of the fruit.
 * @param y The y-coordinate of the fruit.
 */
Fruit::Fruit(float x, float y)
    : Collectable(x, y, 50.0f) {}

/**
 * @brief Destructor for the Fruit class.
 */
Fruit::~Fruit() {}
