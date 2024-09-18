#ifndef LIVES_H
#define LIVES_H

class Lives {
public:
    Lives(int initialLives);
    ~Lives();

    void loseLife();
    void gainLife();
    int getLives() const;
    bool isAlive() const;

private:
    int lives;
};

#endif // LIVES_H
