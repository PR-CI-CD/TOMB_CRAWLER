#pragma once
#include <string>
#include "Player.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    std::string* title;
    Player player;

    void showIntro();
    void startGame();
};
