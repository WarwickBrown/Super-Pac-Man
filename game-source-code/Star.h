#ifndef STAR_H
#define STAR_H

#include "Collectable.h"
#include <vector>
#include <raylib-cpp.hpp>

class Star : public Collectable {
public:
    // Constructor to initialise the Star with position and textures
    Star(int x, int y);

    // Destructor
    ~Star();

    // Show the star (activate it)
    void show();

    // Select and change the current texture of the star
    void determineChange();

    bool getChange() const { return change; }

    void setChange() { change = false; }

private:
    mutable bool change = false;    // Tracks if a texture change is needed
    mutable float startTime = GetTime();  // Starting time to control texture changes
    mutable int multiple = 1;       // Multiple used to control texture changes
};

#endif // STAR_H