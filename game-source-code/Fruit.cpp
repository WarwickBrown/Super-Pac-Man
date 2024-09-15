#include "Fruit.h"

// Constructor that accepts position (x, y) and a texture reference
Fruit::Fruit(int x, int y, const Texture2D& texture) : x(x), y(y), radius(20), active(true), texture(texture), eaten(false) {}

// Destructor
Fruit::~Fruit() {}

// Getter for X position
int Fruit::getX() const {
    return x;
}

// Getter for Y position
int Fruit::getY() const {
    return y;
}

// Getter for radius
int Fruit::getRadius() const {
    return radius;
}

// Checks if the fruit is active
bool Fruit::isActive() const {
    return active;
}

// Collects the fruit (deactivates it)
void Fruit::collect() {
    active = false;
}

// Draws the fruit on the screen
void Fruit::draw() const {
    if (active) {
        DrawTexture(texture, x, y, RAYWHITE); // Draw the fruit if it's active
    }
}

void Fruit::markAsEaten() {
    eaten = true;
}

bool Fruit::isEaten() const {
    return eaten;
}
