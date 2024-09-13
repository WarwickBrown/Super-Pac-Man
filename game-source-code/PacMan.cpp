#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

using namespace std;

// Constructor
PacMan::PacMan(int startX, int startY) : x(100), y(100), dx(0), dy(0), speed(250), radius(39) {
    initilisePacManImages();
}

// Destructor
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on direction and checks for collisions
void PacMan::move(const Maze& maze, float deltaTime, int dir) {
    setDirection(dir);
    float newX = x + dx;
    float newY = y + dy;

    if (!maze.isWall(newX, newY, radius)) {
        x += dx*0.1;
        y += dy*0.1;
    }
}

const std::vector<Texture2D>& PacMan::getPacmanImages() const {
    return pacManImages;
}

void PacMan::initilisePacManImages() {
    pacManImages.push_back(manLeft);
    pacManImages.push_back(manRight);
    pacManImages.push_back(manUp);
    pacManImages.push_back(manDown);
}


int PacMan::location(int frame, int dir) const {
    // Update the timer and frame
    static float timer = 0;
    timer += GetFrameTime();

    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;  // Cycle through frames
    }

    return frame;  // Return the updated frame number
}

// Sets the movement direction of Pac-Man
void PacMan::setDirection(int dir) {
    if(dir == 0){
        dx = 0;
        dy = 0;
    }
    else if(dir == 1){
        dx = 1;
        dy = 0;
    }
    else if(dir == 2){
        dx = -1;
        dy = 0;
    }
    else if(dir == 3){
        dx = 0;
        dy = -1;
    }
    else if(dir == 4){
        dx = 0;
        dy = 1;
    }
}

// Checks for collisions with the maze
bool PacMan::checkCollision(const Maze& maze) const {
    return maze.isWall(x / 32, y / 32, radius);
}
