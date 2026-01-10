#include "game.h"
#include "Room.h"
#include "Tomb1.h"
#include "Tomb2.h"
#include <iostream>
#include <memory>

Game::Game()
{
    title = new std::string("THE ANCIENT RELIC – TOMB CRAWLER");
}

Game::~Game()
{
    delete title;
    title = nullptr;
}

void Game::run()
{
    showIntro();
    startGame();
}

void Game::showIntro()
{
    std::cout << "=========================================\n";
    std::cout << *title << "\n";
    std::cout << "=========================================\n\n";

    std::cout << "The ancient relic that keeps the land alive has been stolen.\n";
    std::cout << "Crops are dying. Rivers are drying.\n";
    std::cout << "The Goblin King has taken it into the underground tombs.\n\n";

    std::cout << "You are the last warrior.\n";
    std::cout << "Retrieve the relic...\n\n";

    std::cout << "Press ENTER to begin...";
    std::string input;
    std::getline(std::cin, input);
}

void Game::startGame()
{
    std::cout << "\nEntering Tomb 1...\n";

    // Use polymorphism + smart pointers (rewarded)
    std::unique_ptr<Room> room1 = std::make_unique<Tomb1>(10, 6);
    bool tomb1Cleared = room1->enter(player);

    if (!tomb1Cleared)
    {
        std::cout << "\nGame Over.\n";
        return;
    }

    std::cout << "\nTomb 1 complete. Entering Tomb 2...\n";

    std::unique_ptr<Room> room2 = std::make_unique<Tomb2>(10, 6);
    bool tomb2Cleared = room2->enter(player);

    if (tomb2Cleared && player.hasRelic())
    {
        std::cout << "\nYOU ESCAPED WITH THE RELIC!\n";
        std::cout << "The land begins to heal. Rivers flow again.\n";
        std::cout << "Victory!\n";
    }
    else
    {
        std::cout << "\nGame Over.\n";
    }
}



