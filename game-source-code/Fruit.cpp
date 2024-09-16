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
        Rectangle sourceRec = {
        (float)(fruitPic.width) ,  // Calculate width of a single frame
        0, 
        (float)(fruitPic.width),          // Width of a single frame
        (float)(fruitPic.height)              // Full height of the texture
    };

    // Draw Ghosts texture at the specified location and frame
    DrawTextureRec(fruitPic, sourceRec, Vector2{(float)getX()-28, (float)getY()-28}, RAYWHITE);
       // DrawTexture(texture, x, y, RAYWHITE); // Draw the fruit if it's active
    }
}

void Fruit::markAsEaten() {
    eaten = true;
}

bool Fruit::isEaten() const {
    return eaten;
}
