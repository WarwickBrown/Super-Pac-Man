#ifndef STAR_H
#define STAR_H

#include <raylib-cpp.hpp>
#include <vector>

class Star {
public:
    // Constructor that accepts position (x, y) and a texture reference
    Star(int x, int y, const std::vector<Texture2D> texture);
    ~Star(); // Destructor

    int getX() const;      // Getter for X position
    int getY() const;      // Getter for Y position
    int getRadius() const; // Getter for radius
    bool isActive() const; // Checks if the Star is active
    void collect();        // Collects the Star (deactivates it)
    void draw(int frame) const;     // Draws the Star on the screen
    void markAsEaten();
    bool isEaten() const;
    void markAsNotEaten();
    void show();

private:
    int x, y;              // Position of the Star
    int radius;            // Radius of the Star
    bool active;           // Whether the Star is still on the screen
    Texture2D texture;     // Texture of the Star
    bool eaten;
    Texture2D star1 = LoadTexture("../resources/pacman-images/star1.png");
    Texture2D star2 = LoadTexture("../resources/pacman-images/star2.png");
    Texture2D star3 = LoadTexture("../resources/pacman-images/star3.png");
};

#endif // STAR_H