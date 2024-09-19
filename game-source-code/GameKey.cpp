// GameKey.cpp
#include "GameKey.h"

GameKey::GameKey(int x, int y, const std::vector<int>& wallsToUnlock)
    : x(x), y(y), radius(20), active(true), wallsToUnlock(wallsToUnlock) {}

GameKey::~GameKey() {}

int GameKey::getX() const { return x; }
int GameKey::getY() const { return y; }
int GameKey::getRadius() const { return radius; }
bool GameKey::isActive() const { return active; }
void GameKey::collect() { active = false; }
const std::vector<int>& GameKey::getWallsToUnlock() const { return wallsToUnlock; }

void GameKey::draw() const {
    if (active) {
        DrawTexture(texture, x - texture.width / 2 + 7, y - texture.height / 2 + 7, WHITE);
    }
}
