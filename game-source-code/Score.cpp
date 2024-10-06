/**
 * @file Score.cpp
 * @brief Implements the Score class, which manages the player's score and high score.
 * 
 * This file defines the methods for tracking the player's score, updating the high score,
 * and saving/loading the high score to/from a file.
 */

#include "Score.h"
#include "Reader.h"
#include <sstream>

/**
 * @brief Constructs a Score object and loads the high score from a file.
 * 
 * Initializes the Score object, setting the current score and high score to zero.
 * It then loads the high score from the specified file.
 * 
 * @param filename The name of the file to read/write the high score.
 */
Score::Score(const std::string& filename)
    : currentScore(0), highScore(0), scoreFile("../resources/" + filename) {
    loadHighScore();
}

/**
 * @brief Destructor for the Score class.
 * 
 * The destructor saves the current high score to the file when the Score object is destroyed.
 */
Score::~Score() {
    saveHighScore();
}

/**
 * @brief Adds points to the current score and updates the high score if necessary.
 * 
 * This method increments the current score by the specified number of points.
 * If the new current score exceeds the high score, the high score is updated.
 * 
 * @param points The number of points to add to the current score.
 */
void Score::addPoints(int points) {
    currentScore += points;
    if (currentScore > highScore) {
        highScore = currentScore;
    }
}

/**
 * @brief Loads the high score from the file specified by `scoreFile`.
 * 
 * This method uses the `Reader` class to read the high score from the file.
 * If the file is not found or is empty, the high score is set to zero.
 */
void Score::loadHighScore() {
    Reader reader(scoreFile);    ///< Create a Reader object to read the high score file.
    reader.readFile();           ///< Read the file content into the `data` vector.
    const auto data = reader.getData();

    if (!data.empty()) {
        std::istringstream ss(data[0]);  ///< Assume the high score is in the first line.
        ss >> highScore;                 ///< Parse the high score from the file.
    } else {
        highScore = 0;  ///< No high score found, set to zero.
    }
}

/**
 * @brief Saves the high score to the file specified by `scoreFile`.
 * 
 * This method uses the `Reader` class to write the current high score to the file.
 */
void Score::saveHighScore() {
    Reader writer(scoreFile);                          ///< Create a Reader object to write the high score.
    auto lines = { std::to_string(highScore) };        ///< Convert the high score to a string format.
    writer.writeFile(lines);                           ///< Write the high score to the file.
}
