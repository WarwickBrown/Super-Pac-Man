#ifndef FRUIT_H
#define FRUIT_H

#include "Collectable.h"

class Fruit : public Collectable {
public:
    // Constructor that accepts position (x, y), a radius, and a texture reference
    Fruit(float x, float y);
    ~Fruit(); // Destructor

    void markAsEaten(); // Mark the fruit as eaten
    bool isEaten() const; // Check if the fruit is eaten

private:
    bool eaten; // Track whether the fruit has been eaten
};

#endif // FRUIT_H