#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

using namespace std;

// Constructor: Initializes Pac-Man's starting position (x, y), movement direction (dx, dy), speed, and size (radius).
PacMan::PacMan(int startX, int startY) : x(50), y(50), dx(0), dy(0), speed(250), radius(39) {}

// Destructor: Since there is no dynamic memory allocation, the destructor does not need to clean up any resources.
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on the direction and checks for wall collisions.
// If Pac-Man does not collide with a wall, his position is updated.
void PacMan::move(const Maze& maze, float deltaTime, int dir) {
    // Set the movement direction (based on input direction).
    setDirection(dir);

    // Calculate the new position.
    float newX = x + dx;
    float newY = y + dy;

    // Check if the new position is not colliding with a wall.
    if (!maze.isWall(newX, newY, radius)) {
        // If no collision, update Pac-Man's position.
        x += dx * speed * deltaTime;
        y += dy * speed * deltaTime;
    }
}

// Returns a constant reference to the vector of Pac-Man images (used for rendering animations).
const std::vector<Texture2D>& PacMan::getPacmanImages() const {
    return pacManImages;
}

// Loads the textures for Pac-Man's various directional sprites and stores them in the `pacManImages` vector.
void PacMan::initilisePacManImages() {
    // Load textures for Pac-Man moving in different directions.
    Texture2D manLeft = LoadTexture("../resources/pacman-images/pacmenLeft.png");
    Texture2D manRight = LoadTexture("../resources/pacman-images/pacmenRight.png");
    Texture2D manUp = LoadTexture("../resources/pacman-images/pacmenUp.png");
    Texture2D manDown = LoadTexture("../resources/pacman-images/pacmenDown.png");

    // Add the textures to the vector.
    pacManImages.push_back(manLeft);
    pacManImages.push_back(manRight);
    pacManImages.push_back(manUp);
    pacManImages.push_back(manDown);
}

// Manages Pac-Man's animation frame timing and returns the appropriate frame index for rendering.
// This method controls how quickly Pac-Man's sprite animation changes as he moves.
int PacMan::location(int frame, int dir) const {
    // Timer to control the speed of the frame change.
    static float timer = 0;
    timer += GetFrameTime();  // Add time since the last frame.

    // If the timer exceeds 0.2 seconds, advance to the next frame.
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;  // Cycle through 6 frames (0 to 5).
    }

    // Return the updated frame number.
    return frame;
}

// Sets the movement direction of Pac-Man based on the given direction integer.
// This updates `dx` and `dy`, which represent movement in the x and y directions.
void PacMan::setDirection(int direction) {
    switch (direction) {
        case 1: 
            dx = 1; 
            dy = 0; 
            break;  // Right movement
        case 2: 
            dx = -1; 
            dy = 0; 
            break; // Left movement
        case 3: 
            dx = 0; 
            dy = -1; 
            break; // Down movement
            case 4: 
            dx = 0; 
            dy = 1; 
            break;  // Up movement
        default: 
            dx = 0; 
            dy = 0;        // No movement (None)
    }
}

// Checks for collisions with the maze
// bool PacMan::checkCollision(const Maze& maze) const {
//     return maze.isWall(x / 32, y / 32, radius);
// }
