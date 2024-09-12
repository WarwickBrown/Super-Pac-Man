#include "PacMan.h"
#include "PacManScreen.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <tuple>

using namespace std;

// Constructor
PacMan::PacMan(int startX, int startY) : x(100), y(100), dx(0), dy(0), speed(250), radius(37) {}

// Destructor
PacMan::~PacMan() {
    // No dynamic memory to clean up in this class
}

// Moves Pac-Man based on direction and checks for collisions
// This needs to be over-hauled
void PacMan::move(const Maze& maze, float deltaTime, int dir) {
    setDirection(dir);
    float newX = x + dx;
    float newY = y + dy;

    if (!maze.isWall(newX, newY, radius)) {
        x += dx*0.5;
        y += dy*0.5;
    }
}

int PacMan::location(int frame, int dir) const {
    // Update the timer and frame
    static float timer = 0;
    timer += GetFrameTime();
    
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame = (frame + 1) % 6;
    }

    // Convert tile coordinates to pixel coordinates
    double pixelX = x - 43;
    double pixelY = y - 50;
    
    //screen->draw(frame, pixelX, pixelY, dir);
    if(dir == 2){
        DrawTextureRec(
        manLeft, 
        Rectangle{(float)(manLeft.width / 6) * frame, 0, (float)(manLeft.width / 6), (float)(manLeft.height)}, 
        Vector2{(float)pixelX, (float)pixelY}, 
        RAYWHITE
        );
    }
    else if(dir == 1){
        DrawTextureRec(
        manRight, 
        Rectangle{(float)(manRight.width / 6) * frame, 0, (float)(manRight.width / 6), (float)(manRight.height)}, 
        Vector2{(float)pixelX, (float)pixelY}, 
        RAYWHITE
        );
    }
    else if(dir == 3){
        DrawTextureRec(
        manUp, 
        Rectangle{(float)(manUp.width / 6) * frame, 0, (float)(manUp.width / 6), (float)(manUp.height)}, 
        Vector2{(float)pixelX, (float)pixelY}, 
        RAYWHITE
        );
    }
    else if(dir == 4){
        DrawTextureRec(
        manDown, 
        Rectangle{(float)(manDown.width / 6) * frame, 0, (float)(manDown.width / 6), (float)(manDown.height)}, 
        Vector2{(float)pixelX, (float)pixelY}, 
        RAYWHITE
        );
    }
    // Return the updated frame
    return frame;
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

