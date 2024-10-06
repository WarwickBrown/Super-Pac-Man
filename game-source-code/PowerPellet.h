/**
 * @file PowerPellet.h
 * @brief Defines the PowerPellet class, which represents a power-up that Pac-Man can collect.
 * 
 * The PowerPellet class inherits from the Collectable class and provides methods to handle interactions
 * with Pac-Man, such as collision detection and collection.
 */

#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "Collectable.h"
#include "PacMan.h"
#include <raylib-cpp.hpp>

/**
 * @class PowerPellet
 * @brief Represents a power-up pellet that Pac-Man can collect to gain special abilities.
 * 
 * The PowerPellet class extends the Collectable class and implements functionality to check if Pac-Man
 * collides with the pellet. Upon collision, the pellet is marked as collected.
 */
class PowerPellet : public Collectable {
public:
    /**
     * @brief Constructs a PowerPellet object with a specified position.
     * 
     * This constructor initializes the PowerPellet using the Collectable class's constructor
     * and sets its position and radius.
     * 
     * @param x The x-coordinate of the power pellet.
     * @param y The y-coordinate of the power pellet.
     */
    PowerPellet(float x, float y);

    /**
     * @brief Destructor for the PowerPellet class.
     * 
     * This destructor does not perform any specific actions but is defined for completeness.
     */
    ~PowerPellet();

    /**
     * @brief Checks if Pac-Man collides with the power pellet.
     * 
     * If Pac-Man collides with the power pellet, the pellet is marked as collected, and the method
     * returns true. Otherwise, it returns false.
     * 
     * @param pacman The Pac-Man object to check for collisions.
     * @return true if Pac-Man collides with the pellet, false otherwise.
     */
    bool checkCollisionWithPacMan(const PacMan& pacman);
};

#endif // POWERPELLET_H
