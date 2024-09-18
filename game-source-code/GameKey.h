// GameKey.h
#ifndef GAMEKEY_H
#define GAMEKEY_H

#include <raylib-cpp.hpp>
#include <vector>

class GameKey {
public:
    GameKey(int x, int y, const std::vector<int>& wallsToUnlock);
    ~GameKey();

    int getX() const;
    int getY() const;
    int getRadius() const;
    bool isActive() const;
    void collect();
    void draw() const;
    const std::vector<int>& getWallsToUnlock() const;

private:
    int x, y;
    int radius;
    bool active;
    // Texture2D texture;
    std::vector<int> wallsToUnlock;
    Texture2D texture = LoadTexture("../resources/pacman-images/key.png");
};

#endif // GAMEKEY_H
