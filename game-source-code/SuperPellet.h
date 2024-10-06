/**
 * @file SuperPellet.h
 * @brief Defines the SuperPellet class, a special type of collectible in the game.
 * 
 * The SuperPellet class represents a super pellet collectible that, when collected by Pac-Man,
 * grants special abilities such as faster movement and the ability to pass through locked walls.
 * It inherits from the Collectable class and provides collision detection functionality.
 */

#ifndef SUPERPELLET_H
#define SUPERPELLET_H

#include "Collectable.h"
#include <raylib-cpp.hpp>

/**
 * @class SuperPellet
 * @brief Represents a super pellet collectible in the game.
 * 
 * The SuperPellet class extends the Collectable class and provides functionality specific
 * to the super pellet, including collision detection with Pac-Man. When collected, the
 * super pellet grants Pac-Man special abilities such as faster movement and the ability
 * to pass through locked walls.
 */
class SuperPellet : public Collectable {
public:
    /**
     * @brief Constructs a SuperPellet object with a specified position.
     * 
     * Initializes the SuperPellet object using the base class Collectable's constructor,
     * setting its position and radius. The super pellet is initially active.
     * 
     * @param x The x-coordinate of the super pellet's position.
     * @param y The y-coordinate of the super pellet's position.
     */
    SuperPellet(float x, float y); // Constructor

    /**
     * @brief Destructor for the SuperPellet class.
     * 
     * Cleans up resources if necessary. Since no dynamic memory allocation is used,
     * this destructor does not perform any specific actions but is defined for completeness.
     */
    ~SuperPellet(); // Destructor

    /**
     * @brief Checks if Pac-Man collides with the super pellet.
     * 
     * This method checks if the bounding circle of Pac-Man intersects with the bounding
     * circle of the super pellet. If a collision is detected and the super pellet is active,
     * it returns true; otherwise, it returns false.
     * 
     * @param pacManX The x-coordinate of Pac-Man's position.
     * @param pacManY The y-coordinate of Pac-Man's position.
     * @param pacManRadius The radius of Pac-Man (for collision detection).
     * @return true if Pac-Man collides with the super pellet and it is active, false otherwise.
     */
    bool checkCollision(float pacManX, float pacManY, float pacManRadius) const;
};

#endif // SUPERPELLET_H
