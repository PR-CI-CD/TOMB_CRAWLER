#include "game.h"
#include "Tomb1.h"
#include "Room.h"
#include <iostream>
#include <memory>

Game::Game()
{
    title = new std::string("THE ANCIENT RELIC – TOMB CRAWLER");
}

Game::~Game()
{
    delete title;
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
    std::cout << "Your mission is to retrieve the relic and save the world.\n\n";

    std::cout << "Press ENTER to begin...";
    std::string input;
    std::getline(std::cin, input);
}

void Game::startGame()
{
    std::cout << "\nEntering Tomb 1...\n";

    /*
        Create the room using a smart pointer to the base class.
        This demonstrates polymorphism and scalable design:
        Game does not need to know which specific room it is running.
    */
    std::unique_ptr<Room> room = std::make_unique<Tomb1>(10, 6);

    bool tomb1Cleared = room->enter(player);

    if (tomb1Cleared)
    {
        std::cout << "\nTomb 1 complete. Tomb 2 will be added next.\n";
    }
    else
    {
        std::cout << "\nGame Over.\n";
    }
}


