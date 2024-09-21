#include "Star.h"
#include <cstdlib>
#include <iostream> 

// Constructor that initializes the Star with position and textures
Star::Star(int x, int y)
    : Collectable(x, y, 20.0f),  // Call the base class constructor
    eaten(false), change(false) {active = false;}

// Destructor
Star::~Star() {
    // Base class destructor will handle unloading the texture
}

// Show the star by activating it
void Star::show() {
    active = true;
}

// Override the collect method to deactivate the star
void Star::collect() {
    Collectable::collect();  // Call the base class collect method
    active = false;          // Mark as inactive (just for clarity)
}

// Select the texture to display based on time and conditions
void Star::determineChange() {
    float updatedTime = GetTime() - startTime;
    if (updatedTime >= multiple * 0.2) {
        multiple++;
        change = true;
    }
}

bool Star::getChange() const {
    return change;
}

void Star::setChange() {
    change = false;
}

// Mark the star as eaten
void Star::markAsEaten() {
    eaten = true;
}

// Mark the star as not eaten
void Star::markAsNotEaten() {
    eaten = false;
}

// Check if the star is eaten
bool Star::isEaten() const {
    return eaten;
}