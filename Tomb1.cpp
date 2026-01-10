#include "Tomb1.h"
#include <iostream>
#include <string>
#include <cctype>   // std::toupper
#include <cstdlib>  // rand, srand
#include <ctime>    // time

static void clearScreen()
{
    // ANSI escape codes: clear screen + move cursor to top-left
    std::cout << "\x1B[2J\x1B[H" << std::flush;
}

Tomb1::Tomb1(int width, int height)
{
    gridWidth = width;
    gridHeight = height;

    // Seed random number generator for enemy damage (simple approach)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    grid = nullptr;
    statusMessage = "Find the key, then reach the door (D).";

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
    std::cout << "--- TOMB 1: The Entrance Chamber ---\n";
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
    std::cout << "------------------------------------------------------------\n";
    std::cout << statusMessage << "\n";
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
        statusMessage = "You bump into a cold stone wall.";
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
            statusMessage = "You unlock the door to Tomb 2 and step through...";
            return false; // leaving Tomb 1
        }

        statusMessage = "The door is locked. You need a key.";
    }
    else
    {
        // Only update movement feedback if we didn't trigger something else
        if (statusMessage.empty())
        {
            statusMessage = "You move deeper into the tomb...";
        }
    }

    return true;
}

void Tomb1::onEnemyEncounter(Player& player)
{
    if (!enemy) return;

    const int damage = enemy->attack();
    player.takeDamage(damage);

    if (!player.isAlive())
    {
        statusMessage = "Goblek attacks and you collapse in the darkness...";
        return;
    }

    statusMessage = "You bump into Goblek! It attacks for " + std::to_string(damage) +
                    " damage. Press A to attack back.";
}

bool Tomb1::enter(Player& player)
{
    /*
        Polymorphic entry point.
        Game can call this through a Room* or std::unique_ptr<Room>.
    */
    bool stillInTomb1 = true;
    statusMessage = "Find the key, then reach the door (D).";

    while (stillInTomb1)
    {
        if (!player.isAlive())
        {
            return false; // player died
        }

        clearScreen();
        drawRoom(player);

        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            statusMessage = "Enter a command: F, B, L, R, A, or Q.";
            continue;
        }

        char command = static_cast<char>(std::toupper(input[0]));

        if (command == 'Q')
        {
            statusMessage = "You retreat to the surface...";
            clearScreen();
            drawRoom(player);
            return false;
        }

        // Player attack: kills enemy instantly (your spec)
        if (command == 'A')
        {
            if (enemy && enemy->isAlive() && playerX == enemyX && playerY == enemyY)
            {
                enemy->kill();
                player.giveTomb2Key();
                statusMessage = "You strike down Goblek! It drops a key to Tomb 2.";
            }
            else
            {
                statusMessage = "You swing at the air.";
            }

            continue;
        }

        // Movement
        if (command == 'F' || command == 'B' || command == 'L' || command == 'R')
        {
            // handleMove returns false only when player exits through door with key
            statusMessage.clear(); // allow move to set a relevant message
            stillInTomb1 = handleMove(command, player);
        }
        else
        {
            statusMessage = "Unknown command. Use F, B, L, R, A or Q.";
        }
    }

    // Exited Tomb 1 successfully
    return true;
}


