#pragma once

#include <string>
#include "Player.h"

/*
    Game controls the flow of the program (intro -> rooms).
*/
class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    // Demonstrates manual memory management (raw pointer)
    std::string* title;

    // Player state persists across rooms
    Player player;

    void showIntro();
    void startGame();
};
