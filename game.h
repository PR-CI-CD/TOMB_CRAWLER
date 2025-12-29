#pragma once
#include <string>

/*
    The Game class controls the flow of the program.
    It is responsible for starting the game, showing the intro,
    and later will manage the tombs and player.
*/
class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    // Dynamically allocated title string
    std::string* title;

    void showIntro();
    void startGame();
};
