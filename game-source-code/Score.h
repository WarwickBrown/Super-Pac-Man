/**
 * @file Score.h
 * @brief Defines the Score class, which manages the player's score and high score.
 * 
 * The Score class is responsible for keeping track of the player's current score, comparing it
 * to the high score, and saving/loading the high score to/from a file.
 */

#ifndef SCORE_H
#define SCORE_H

#include <string>

/**
 * @class Score
 * @brief Manages the player's score and high score, including saving and loading from a file.
 * 
 * The Score class provides functionality to track the current score during gameplay,
 * update the high score if the current score exceeds it, and persist the high score by
 * saving it to a file and loading it when needed.
 */
class Score {
public:
    /**
     * @brief Constructs a Score object and loads the high score from a file.
     * 
     * This constructor initialises the Score object with the given filename, sets
     * the current and high scores to zero, and loads the high score from the specified
     * file.
     * 
     * @param filename The name of the file to read/write the high score.
     */
    Score(const std::string& filename);

    /**
     * @brief Destructor for the Score class.
     * 
     * The destructor saves the current high score to the file when the Score object
     * is destroyed.
     */
    ~Score();

    /**
     * @brief Adds points to the current score and updates the high score if necessary.
     * 
     * This method increments the current score by the specified number of points.
     * If the new current score exceeds the high score, the high score is updated.
     * 
     * @param points The number of points to add to the current score.
     */
    void addPoints(int points);

    /**
     * @brief Gets the current score of the player.
     * 
     * @return The current score as an integer.
     */
    int getCurrentScore() const { return currentScore; }

    /**
     * @brief Gets the current high score.
     * 
     * @return The high score as an integer.
     */
    int getHighScore() const { return highScore; }

    /**
     * @brief Loads the high score from the file specified by scoreFile.
     * 
     * This method reads the high score from the file and sets the highScore member variable.
     * If the file is empty or not found, the high score is set to zero.
     */
    void loadHighScore();

    /**
     * @brief Saves the high score to the file specified by scoreFile.
     * 
     * This method writes the current high score to the file, ensuring that the high score
     * persists across game sessions.
     */
    void saveHighScore();

private:
    int currentScore;         ///< The player's current score during gameplay.
    int highScore;            ///< The highest score achieved in the game.
    std::string scoreFile;    ///< The file used to read/write the high score.
};

#endif // SCORE_H