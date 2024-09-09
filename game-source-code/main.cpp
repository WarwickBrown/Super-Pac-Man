#include <raylib-cpp.hpp>
#include <iostream>
#include "Game.h"
using namespace raylib; // import the raylib-cpp namespace into the global namespace


// Predefined raylib-cpp colours can be found here:
// https://robloach.github.io/raylib-cpp/classraylib_1_1_color.html#a3c177f10d10851fdf20d09fae83c8e19

int main()
{
    Game game;
    game.initialize();
    game.run();
    return 0;
}