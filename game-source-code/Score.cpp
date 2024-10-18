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


Score::Score(const std::string& filename)
    : currentScore(0), highScore(0), scoreFile("../resources/database-textfiles/" + filename) {
    loadHighScore();
}

Score::~Score() {
    saveHighScore();
}

void Score::addPoints(int points) {
    currentScore += points;
    if (currentScore > highScore) {
        highScore = currentScore;
    }
}

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

void Score::saveHighScore() {
    Reader writer(scoreFile);                          ///< Create a Reader object to write the high score.
    auto lines = { std::to_string(highScore) };        ///< Convert the high score to a string format.
    writer.writeFile(lines);                           ///< Write the high score to the file.
}