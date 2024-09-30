#include "Fruit.h"

Fruit::Fruit(float x, float y)
    : Collectable(x, y, 50.0f), eaten(false) {}

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