#include "Score.h"
#include <fstream>
#include <iostream>

Score::Score(const std::string& filename)
    : currentScore(0), highScore(0), scoreFile("../resources/" + filename) {
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
    try {
        std::ifstream inFile(scoreFile);
        if (inFile.is_open()) {
            inFile >> highScore;
            inFile.close();
        } else {
            highScore = 0; // No high score file exists
        }
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading high score file: " << e.what() << '\n';
        highScore = 0;
    }
}

void Score::saveHighScore() {
    try {
        std::ofstream outFile(scoreFile);
        if (outFile.is_open()) {
            outFile << highScore;
            outFile.close();
        } else {
            std::cerr << "Unable to open file for saving high score: " << scoreFile << std::endl;
        }
    } catch (const std::ofstream::failure& e) {
        std::cerr << "Exception opening/writing high score file: " << e.what() << '\n';
    }
}

