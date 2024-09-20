#ifndef SUPERPELLET_H
#define SUPERPELLET_H

#include <raylib-cpp.hpp>

class SuperPellet {
public:
    SuperPellet(float x, float y); // Constructor
    ~SuperPellet();                // Destructor
    
    void draw() const;             // Draw the super pellet on the screen
    bool checkCollision(float pacManX, float pacManY, float pacManRadius) const; // Check for collision with Pac-Man
    void collect();                // Pac-Man collects the super pellet
    bool isActive() const;         // Check if the super pellet is still active
    float getX() const { return x; }
    float getY() const { return y; }

private:
    float x, y;                    // Coordinates of the super pellet
    float radius;                  // Radius of the super pellet
    bool active;                   // Whether the super pellet is active (not yet collected)
    Texture2D texture = LoadTexture("../resources/pacman-images/SuperPellet.png"); // Load super pellet texture
};

#endif