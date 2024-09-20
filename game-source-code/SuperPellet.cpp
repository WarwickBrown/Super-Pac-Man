#include "SuperPellet.h"

SuperPellet::SuperPellet(float x, float y) 
    : x(x), y(y), radius(15.0f), active(true) {
   
}

SuperPellet::~SuperPellet() {
}

void SuperPellet::draw() const {
    if (active) {
        Rectangle sourceRec = {
        (float)(texture.width) ,  // Calculate width of a single frame
        0, 
        (float)(texture.width),          // Width of a single frame
        (float)(texture.height)              // Full height of the texture
    };

    DrawTextureRec(texture, sourceRec, Vector2{(float)getX()-28, (float)getY()-28}, RAYWHITE);
    }
}
bool SuperPellet::checkCollision(float pacManX, float pacManY, float pacManRadius) const {
    // Check if Pac-Man's circle intersects with the super pellet's circle
    return active && CheckCollisionCircles({ pacManX, pacManY }, pacManRadius, { x, y }, radius);
}

void SuperPellet::collect() {
    active = false; // Mark as collected
}

bool SuperPellet::isActive() const {
    return active;
}