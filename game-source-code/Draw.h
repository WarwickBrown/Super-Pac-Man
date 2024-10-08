/**
 * @file Draw.h
 * @brief Defines the Draw class used for handling all drawing-related functionality for the game.
 */

#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <memory>
#include <raylib-cpp.hpp>
#include "Maze.h"
#include "PacMan.h"
#include "Game.h"
#include "Ghost.h"
#include "Fruit.h"
#include "GameKey.h"
#include "Score.h"
#include "PowerPellet.h"
#include "SuperPellet.h"
#include "Star.h"

// Forward declaration of classes
class Game;
class Ghost;

/**
 * @class Draw
 * @brief A class responsible for rendering various game objects on the screen, such as Pac-Man, ghosts, the maze, and other collectables.
 */
class Draw {
public:
    /**
     * @enum Direction
     * @brief Defines the possible movement directions for Pac-Man and other game elements.
     */
    enum Direction {
        RIGHT = 1, ///< Moving right
        LEFT,      ///< Moving left
        UP,        ///< Moving up
        DOWN       ///< Moving down
    };

    /**
     * @brief Constructor: Initialises the Draw class and associated resources.
     */
    Draw();

    /**
     * @brief Destructor: Releases resources associated with the Draw class.
     */
    ~Draw();

    /**
     * @brief Draws the fruits on the screen.
     * 
     * @param fruits A vector of unique pointers to Fruit objects representing fruits to be drawn.
     * @param num An integer representing the type of fruit texture to be used.
     */
    void drawFruits(const std::vector<std::unique_ptr<Fruit>>& fruits, int num);

    /**
     * @brief Draws a ghost at its specified position.
     * 
     * @param ghost The Ghost object to be drawn.
     * @param pacman The Pac-Man object used to determine if the ghost should be drawn in a frightened state.
     */
    void drawGhost(const Ghost& ghost, const PacMan& pacman, int ghostNumber);

    /**
     * @brief Draws keys at their specified positions.
     * 
     * @param keys A vector of GameKey objects representing keys to be drawn.
     */
    void drawKeys(const std::vector<GameKey>& keys);

    /**
     * @brief Draws the remaining lives on the screen.
     * 
     * @param lives The number of lives left to be drawn.
     */
    void drawLives(int lives);

    /**
     * @brief Draws the maze based on its walls.
     * 
     * @param maze The Maze object containing the walls to be drawn.
     */
    void drawMaze(const Maze& maze);

    /**
     * @brief Draws Pac-Man at a specified location and frame based on his current direction.
     * 
     * @param pacman The Pac-Man object to be drawn.
     * @param frame The current animation frame of Pac-Man.
     * @param pacManDirection The direction Pac-Man is currently moving.
     */
    void drawPacMan(const PacMan& pacman, int frame, Direction pacManDirection);

    /**
     * @brief Draws power pellets at their specified positions.
     * 
     * @param powerPellets A vector of unique pointers to PowerPellet objects representing power pellets to be drawn.
     */
    void drawPowerPellets(const std::vector<std::unique_ptr<PowerPellet>>& powerPellets);

    /**
     * @brief Draws the current score and high score on the screen.
     * 
     * @param score The Score object containing the current and high scores.
     */
    void drawScores(const Score& score);

    /**
     * @brief Draws stars at their specified positions.
     * 
     * @param star A vector of unique pointers to Star objects representing stars to be drawn.
     */
    void drawStars(std::vector<std::unique_ptr<Star>>& star);

    /**
     * @brief Draws Super Pac-Man at a specified location and frame based on his current direction.
     * 
     * @param pacman The Pac-Man object to be drawn.
     * @param frame The current animation frame of Pac-Man.
     * @param pacManDirection The direction Super Pac-Man is currently moving.
     */
    void drawSuperPacMan(const PacMan& pacman, int frame, Direction pacManDirection);

    /**
     * @brief Draws the super pellets on the screen.
     * 
     * @param superPellets A vector of unique pointers to SuperPellet objects representing super pellets to be drawn.
     */
    void drawSuperPellets(const std::vector<std::unique_ptr<SuperPellet>>& superPellets);

    /**
     * @brief Draws symbols on the screen based on the provided texture numbers.
     * 
     * @param num1 The first symbol texture number.
     * @param num2 The second symbol texture number.
     */
    void drawSymbols(int num1, int num2);

    /**
     * @brief Retrieves the texture corresponding to the given number.
     * 
     * @param num The number representing the texture to be retrieved.
     * @return The Texture2D object corresponding to the given number.
     */
    Texture2D getTexture(int num);

    /**
     * @brief Sets the symbol's active status.
     * 
     * @param status A boolean value to set the symbol's active state.
     */
    void setSymbolActive(bool status);

private:
    std::unique_ptr<Maze> maze; ///< Pointer to the Maze object used for drawing.
    raylib::Window window;      ///< Window object used for rendering the game.
    int num = 0;                ///< Index for cycling through textures.
    bool eaten;                 ///< Flag indicating if a collectable has been eaten.
    bool symbolActive = false;  ///< Flag indicating if the symbol should be active.
    Texture2D picture;          ///< Texture for drawing various symbols.

    // Pac-Man Textures
    std::vector<Texture2D> pacManTextures = {
        LoadTexture("../resources/pacman-images/pacmenLeft.png"),  ///< Texture for Pac-Man moving left.
        LoadTexture("../resources/pacman-images/pacmenRight.png"), ///< Texture for Pac-Man moving right.
        LoadTexture("../resources/pacman-images/pacmenUp.png"),    ///< Texture for Pac-Man moving up.
        LoadTexture("../resources/pacman-images/pacmenDown.png")   ///< Texture for Pac-Man moving down.
    };

    std::vector<Texture2D> pacManTexturesBig = {
        LoadTexture("../resources/pacman-images/pacmenLeftBig.png"),  ///< Texture for Super Pac-Man moving left.
        LoadTexture("../resources/pacman-images/pacmenRightBig.png"), ///< Texture for Super Pac-Man moving right.
        LoadTexture("../resources/pacman-images/pacmenUpBig.png"),    ///< Texture for Super Pac-Man moving up.
        LoadTexture("../resources/pacman-images/pacmenDownBig.png")   ///< Texture for Super Pac-Man moving down.
    };

    // Ghost Textures
    Texture2D ghostPicRed = LoadTexture("../resources/pacman-images/ghostyRed.png"); ///< Texture for red ghost.
    Texture2D ghostPicGreen = LoadTexture("../resources/pacman-images/ghostyGreen.png"); ///< Texture for green ghost.
    Texture2D ghostPicOrange = LoadTexture("../resources/pacman-images/ghostyOrange.png"); ///< Texture for orange ghost.
    Texture2D ghostFrightenedRight = LoadTexture("../resources/pacman-images/ghostyScared.png"); ///< Texture for frightened ghost.
    Texture2D ghostFlattenedTexture = LoadTexture("../resources/pacman-images/ghostyStreched.png"); ///< Texture for flattened ghost.

    // Symbol textures
    Texture2D symbol1 = LoadTexture("../resources/pacman-images/symbol1.png"); ///< Symbol texture 1.
    Texture2D symbol2 = LoadTexture("../resources/pacman-images/symbol2.png"); ///< Symbol texture 2.
    Texture2D symbol3 = LoadTexture("../resources/pacman-images/symbol3.png"); ///< Symbol texture 3.
    Texture2D symbol4 = LoadTexture("../resources/pacman-images/symbol4.png"); ///< Symbol texture 4.
    Texture2D symbol5 = LoadTexture("../resources/pacman-images/symbol5.png"); ///< Symbol texture 5.
    Texture2D symbol6 = LoadTexture("../resources/pacman-images/symbol6.png"); ///< Symbol texture 6.
    Texture2D symbolLives = LoadTexture("../resources/pacman-images/livesSymbol.png"); ///< Texture for life symbol.

    // Key Texture
    Texture2D keyTexture = LoadTexture("../resources/pacman-images/key.png"); ///< Texture for game key.

    // Fruit Texture
    Texture2D fruitPic = LoadTexture("../resources/pacman-images/strawberry.png"); ///< Texture for fruit.

    // Power Pellet Texture
    Texture2D powerPelletTexture = LoadTexture("../resources/pacman-images/PowerPellet.png"); ///< Texture for power pellet.

    // Super Pellet Texture
    Texture2D superPelletTexture = LoadTexture("../resources/pacman-images/SuperPellet.png"); ///< Texture for super pellet.

    // Star Textures
    std::vector<Texture2D> starTextures = {
        LoadTexture("../resources/pacman-images/star1.png"), ///< Star texture 1.
        LoadTexture("../resources/pacman-images/star2.png"), ///< Star texture 2.
        LoadTexture("../resources/pacman-images/star3.png")  ///< Star texture 3.
    };
};

#endif // DRAW_H
