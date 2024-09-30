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

    // Override collect method to deactivate the star
    void collect() override;

    // Select and change the current texture of the star
    void determineChange();

    bool getChange() const { return change; }
    bool isEaten() const { return eaten; } // Check if the star is eaten

    void markAsNotEaten() { eaten = false; } // Mark the star as not eaten
    void setChange() { change = false; }
    void markAsEaten() { eaten = true; } // Mark the star as eaten

private:
    bool eaten;                     // Whether the star is eaten
    mutable int num = 0;            // Index of the current texture
    mutable bool change = false;    // Tracks if a texture change is needed
    mutable float startTime = GetTime();  // Starting time to control texture changes
    mutable int multiple = 1;       // Multiple used to control texture changes
    std::vector<Texture2D> textures; // Different textures for the star
    mutable Texture2D picture;      // Current picture (texture) to draw
};

#endif // STAR_H