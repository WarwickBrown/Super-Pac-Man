#ifndef STAR_H
#define STAR_H

#include "Collectable.h"
#include <vector>
#include <raylib-cpp.hpp>

class Star : public Collectable {
public:
    // Constructor to initialize the Star with position and textures
    Star(int x, int y);

    // Destructor
    ~Star();

    // Show the star (activate it)
    void show();

    // Override collect method to deactivate the star
    void collect() override;

    // Select and change the current texture of the star
    void setChange() const;

    // Handle marking the star as eaten or not
    void markAsEaten();
    void markAsNotEaten();
    bool isEaten() const;
    bool getChange() const;
    void setChange();

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