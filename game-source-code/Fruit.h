#ifndef FRUIT_H
#define FRUIT_H

#include <raylib-cpp.hpp>

class Fruit {
public:
    // Constructor that accepts position (x, y) and a texture reference
    Fruit(int x, int y, const Texture2D& texture);

    ~Fruit(); // Destructor

    int getX() const;      // Getter for X position
    int getY() const;      // Getter for Y position
    int getRadius() const; // Getter for radius
    bool isActive() const; // Checks if the fruit is active
    void collect();        // Collects the fruit (deactivates it)
    void draw() const;     // Draws the fruit on the screen

private:
    int x, y;              // Position of the fruit
    int radius;            // Radius of the fruit
    bool active;           // Whether the fruit is still on the screen
    Texture2D texture;     // Texture of the fruit
};

#endif // FRUIT_H
