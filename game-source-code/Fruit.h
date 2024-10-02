#ifndef FRUIT_H
#define FRUIT_H

#include "Collectable.h"

class Fruit : public Collectable {
public:
    Fruit(float x, float y);
    ~Fruit(); // Destructor

private:
};

#endif // FRUIT_H