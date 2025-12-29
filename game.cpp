#include "game.h"
#include <iostream>

Game::Game()
{
    // Allocate the game title on the heap
    title = new std::string("THE ANCIENT RELIC – TOMB CRAWLER");
}

Game::~Game()
{
    // Free heap memory
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
    std::cout << "\nYour journey into the tombs begins...\n";
}
