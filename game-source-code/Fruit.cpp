#include "Fruit.h"

// Constructor using Collectable's constructor to initialize position, radius, and texture
Fruit::Fruit(float x, float y)
    : Collectable(x, y, 20.0f), eaten(false) {} // Assuming a fixed radius of 20 for Fruit

// Destructor
Fruit::~Fruit() {}

// Marks the fruit as eaten
void Fruit::markAsEaten() {
    eaten = true;
}

// Returns whether the fruit has been eaten
bool Fruit::isEaten() const {
    return eaten;
}