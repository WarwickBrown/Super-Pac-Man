/**
 * @file Fruit.cpp
 * @brief Implements the Fruit class.
 */

#include "Fruit.h"

Fruit::Fruit(float x, float y)
    : Collectable(x, y, 50.0f) {}

Fruit::~Fruit() {}