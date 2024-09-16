// Ghost.h
#ifndef GHOST_H
#define GHOST_H

#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"

enum class GhostState {
    Escaping, // New state to help ghosts escape the box
    Chase,
    Scatter,
    Frightened
};


class Ghost {
public:
    Ghost(int startX, int startY, float speed);

    void move(const Maze& maze, float deltaTime, const PacMan& pacman, GhostState newState);
    void chooseNewDirection(const Maze& maze);
    bool checkCollisionWithPacMan(const PacMan& pacman);
    void switchState(GhostState newState, const Maze& maze);
    void updateTimers(GhostState newState,float deltaTime, const Maze& maze);
    void escapeBox(const Maze& maze, const PacMan& pacman); // Method to help the ghost escape the box

    // Getters
    int getX() const;
    int getY() const;
    int getRadius() const;
    GhostState getState() const; // Add this getter method

    int getGhostDirection() const;

    void setDirection(int newDirection);
    void setFrightened(bool state);


private:
    float x, y;
    float speed;
    int direction;
    int radius;
    GhostState state;  // Add state to represent the ghost's behavior
    bool inBox;

    // Timers to manage state changes
    float chaseTime;
    float scatterTime;
    float frightenedTime;

    void chase(const Maze& maze, const PacMan& pacman);
    void scatter(const Maze& maze);
    void frightened(const Maze& maze);
    void setRandomDirection(const Maze& maze);
};

#endif // GHOST_H
