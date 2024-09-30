#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
public:
    Score(const std::string& filename);
    ~Score();

    void addPoints(int points);
    int getCurrentScore() const { return currentScore; }
    int getHighScore() const { return highScore; }

    void loadHighScore();
    void saveHighScore();

private:
    int currentScore;
    int highScore;
    std::string scoreFile;
};

#endif // SCORE_H