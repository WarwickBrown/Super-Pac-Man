/**
 * @file Star.h
 * @brief Defines the Star class, which represents a collectible star in the game.
 * 
 * The Star class extends the Collectable class and provides functionality for handling
 * collectible stars in the game. It includes methods for showing the star, determining
 * when the texture should change, and controlling its active state.
 */

#ifndef STAR_H
#define STAR_H

#include "Collectable.h"
#include <vector>
#include <raylib-cpp.hpp>

/**
 * @class Star
 * @brief Represents a collectible star in the game that Pac-Man can interact with.
 * 
 * The Star class inherits from the Collectable class and manages the star's position,
 * state (active or inactive), and texture changes over time. It provides methods for
 * activating the star and determining when its texture should change based on time elapsed.
 */
class Star : public Collectable {
public:
    /**
     * @brief Constructs a Star object with a specified position and initializes it.
     * 
     * This constructor initializes the Star object using the base class Collectable's constructor
     * and sets its position, radius, and active state. The star is initially inactive.
     * 
     * @param x The x-coordinate of the star's position.
     * @param y The y-coordinate of the star's position.
     */
    Star(int x, int y);

    /**
     * @brief Destructor for the Star class.
     * 
     * This destructor does not perform any specific actions as there is no dynamic memory
     * allocation, but it is defined for completeness.
     */
    ~Star();

    /**
     * @brief Activates the star, making it visible and collectible in the game.
     * 
     * This method sets the star's active state to true, making it visible in the game.
     */
    void show();

    /**
     * @brief Determines if the star's texture should change based on elapsed time.
     * 
     * This method uses the elapsed time since the star was created to determine if its texture
     * should change. If the time condition is met, the `change` flag is set to true.
     */
    void determineChange();

    /**
     * @brief Gets the current state of the `change` flag.
     * 
     * The `change` flag indicates whether the star's texture needs to change. This method returns
     * the current value of the `change` flag.
     * 
     * @return true if the texture should change, false otherwise.
     */
    bool getChange() const { return change; }

    /**
     * @brief Resets the `change` flag to false.
     * 
     * This method sets the `change` flag to false, indicating that no texture change is needed.
     */
    void setChange() { change = false; };

private:
    mutable bool change = false;    ///< Tracks if a texture change is needed for the star.
    mutable float startTime = GetTime();  ///< Starting time to control texture changes.
    mutable int multiple = 1;       ///< Controls texture change frequency based on elapsed time.
};

#endif // STAR_H
