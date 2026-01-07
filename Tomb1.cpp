#include "Tomb1.h"
#include <iostream>
#include <string>
#include <cctype>   // std::toupper
#include <cstdlib>  // rand, srand
#include <ctime>    // time

Tomb1::Tomb1(int width, int height)
{
    gridWidth = width;
    gridHeight = height;

    // Seed random number generator for enemy damage (simple approach)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    grid = nullptr;

    allocateGrid();
    buildRoomLayout();
}

Tomb1::~Tomb1()
{
    /*
        enemy is a std::unique_ptr, so it automatically frees its owned Enemy
        when Tomb1 is destroyed (RAII). That means we do NOT call delete on it.

        We still manually free the dynamic grid because it was allocated using new[].
    */
    freeGrid();
}

void Tomb1::allocateGrid()
{
    // Allocate an array of row pointers (dynamic array)
    grid = new char*[gridHeight];

    // Allocate each row (dynamic array)
    for (int y = 0; y < gridHeight; y++)
    {
        grid[y] = new char[gridWidth];
    }
}

void Tomb1::freeGrid()
{
    if (!grid) return;

    for (int y = 0; y < gridHeight; y++)
    {
        delete[] grid[y];
        grid[y] = nullptr;
    }

    delete[] grid;
    grid = nullptr;
}

void Tomb1::buildRoomLayout()
{
    // Fill the room with floor tiles
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            grid[y][x] = '.';
        }
    }

    // Player starts near top-left
    playerX = 1;
    playerY = 1;

    // Enemy starts immediately to the right of player (your spec)
    enemyX = playerX + 1;
    enemyY = playerY;

    // Smart pointer allocation: Enemy is created on the heap and owned by Tomb1
    enemy = std::make_unique<Enemy>("Goblek");

    // Door to progress to the next tomb
    doorX = gridWidth - 2;
    doorY = gridHeight - 2;
}

void Tomb1::drawRoom(const Player& player) const
{
    std::cout << "\n--- TOMB 1: The Entrance Chamber ---\n";
    std::cout << "Health: " << player.getHealth()
              << " | Key: " << (player.hasTomb2Key() ? "YES" : "NO") << "\n\n";

    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            if (x == playerX && y == playerY)
            {
                std::cout << 'P';
            }
            else if (enemy && enemy->isAlive() && x == enemyX && y == enemyY)
            {
                std::cout << 'E';
            }
            else if (x == doorX && y == doorY)
            {
                std::cout << 'D';
            }
            else
            {
                std::cout << grid[y][x];
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nControls: F=Forward  B=Back  L=Left  R=Right  A=Attack  Q=Quit\n";
}

bool Tomb1::handleMove(char moveCommand, Player& player)
{
    int nextX = playerX;
    int nextY = playerY;

    if (moveCommand == 'F') nextY -= 1;
    else if (moveCommand == 'B') nextY += 1;
    else if (moveCommand == 'L') nextX -= 1;
    else if (moveCommand == 'R') nextX += 1;

    // Keep the player inside the grid
    if (nextX < 0 || nextX >= gridWidth || nextY < 0 || nextY >= gridHeight)
    {
        std::cout << "You bump into a cold stone wall.\n";
        return true; // still inside Tomb 1
    }

    // Apply movement
    playerX = nextX;
    playerY = nextY;

    // If the player moves onto the enemy tile, the enemy attacks immediately
    if (enemy && enemy->isAlive() && playerX == enemyX && playerY == enemyY)
    {
        onEnemyEncounter(player);
    }

    // Door: player can only leave if they have the key
    if (playerX == doorX && playerY == doorY)
    {
        if (player.hasTomb2Key())
        {
            std::cout << "You unlock the door to Tomb 2 and step through...\n";
            return false; // leaving Tomb 1
        }

        std::cout << "The door is locked. You need a key.\n";
    }

    return true;
}

void Tomb1::onEnemyEncounter(Player& player)
{
    if (!enemy) return;

    std::cout << "\nYou bump into " << enemy->getName() << "!\n";

    int damage = enemy->attack();
    std::cout << enemy->getName() << " attacks first and deals " << damage << " damage!\n";

    player.takeDamage(damage);

    if (!player.isAlive())
    {
        std::cout << "You collapse in the darkness...\n";
        return;
    }

    std::cout << "Press A to attack back...\n";
}

bool Tomb1::enter(Player& player)
{
    /*
        Polymorphic entry point.
        Game can call this through a Room* pointer later, e.g. rooms[i]->enter(player).
    */
    bool stillInTomb1 = true;

    while (stillInTomb1)
    {
        if (!player.isAlive())
        {
            return false; // player died
        }

        drawRoom(player);

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            continue;
        }

        char command = static_cast<char>(std::toupper(input[0]));

        if (command == 'Q')
        {
            std::cout << "You retreat to the surface...\n";
            return false;
        }

        // Player attack: kills enemy instantly (your spec)
        if (command == 'A')
        {
            if (enemy && enemy->isAlive() && playerX == enemyX && playerY == enemyY)
            {
                std::cout << "You strike with your blade — " << enemy->getName() << " is defeated!\n";
                enemy->kill();

                std::cout << enemy->getName() << " drops a key to Tomb 2.\n";
                player.giveTomb2Key();
            }
            else
            {
                std::cout << "You swing at the air.\n";
            }

            continue;
        }

        // Movement
        if (command == 'F' || command == 'B' || command == 'L' || command == 'R')
        {
            // handleMove returns false only when player exits through door with key
            stillInTomb1 = handleMove(command, player);
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }

    // Exited Tomb 1 successfully
    return true;
}


