#include "Star.h"
#include <vector>

// Constructor that accepts position (x, y) and a texture reference
Star::Star(int x, int y, const std::vector<Texture2D> texture) : x(x), y(y), radius(20), active(false), eaten(false) {}

// Destructor
Star::~Star() {}

// Getter for X position
int Star::getX() const {
    return x;
}

// Getter for Y position
int Star::getY() const {
    return y;
}

// Getter for radius
int Star::getRadius() const {
    return radius;
}

// Checks if the Star is active
bool Star::isActive() const {
    return active;
}

void Star::show() {
    active = true;
}

// Collects the Star (deactivates it)
void Star::collect() {
    active = false;
}

// Draws the Star on the screen
void Star::draw(int frame) const {
    if (active) {
        if(frame > 2)
        {
            frame = frame%3;
        }
        Texture2D picture;
        switch(frame){
            case 0:
                picture = star1;
                break;
            case 1:
                picture = star2;
                break;
            case 2:
                picture = star3;
                break;
        }
        Rectangle sourceRec = {
        (float)(picture.width),  // Calculate width of a single frame
        0, 
        (float)(picture.width),          // Width of a single frame
        (float)(picture.height)              // Full height of the texture
    };

    // Draw Ghosts texture at the specified location and frame
    DrawTextureRec(picture, sourceRec, Vector2{(float)getX()-30, (float)getY()-32}, RAYWHITE);
       // DrawTexture(texture, x, y, RAYWHITE); // Draw the Star if it's active
    }
}

void Star::markAsEaten() {
    eaten = true;
}

void Star::markAsNotEaten() {
    eaten = false;
}

bool Star::isEaten() const {
    return eaten;
}
