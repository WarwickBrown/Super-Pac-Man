#include "Score.h"
#include "Reader.h"
#include <sstream>

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
    // Use WallReader to read the high score
    Reader reader(scoreFile);
    reader.readFile();
    const auto data = reader.getData();

    if (!data.empty()) {
        std::istringstream ss(data[0]);  // Assume the high score is in the first line
        ss >> highScore;
    } else {
        highScore = 0;  // No high score found
    }
}

void Score::saveHighScore() {
    // Use WallReader to write the high score
    Reader writer(scoreFile);
    auto lines = { std::to_string(highScore) };
    writer.writeFile(lines);
}
