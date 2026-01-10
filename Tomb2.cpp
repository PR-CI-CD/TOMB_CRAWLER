#include "Tomb2.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

static void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\x1B[2J\x1B[H" << std::flush;
#endif
}

Tomb2::Tomb2(int width, int height)
{
    gridWidth = width;
    gridHeight = height;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    grid = nullptr;
    statusMessage = "Defeat the guard and claim the relic (R).";

    allocateGrid();
    buildRoomLayout();
}

Tomb2::~Tomb2()
{
    freeGrid();
}

void Tomb2::allocateGrid()
{
    grid = new char*[gridHeight];
    for (int y = 0; y < gridHeight; y++)
    {
        grid[y] = new char[gridWidth];
    }
}

void Tomb2::freeGrid()
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

void Tomb2::buildRoomLayout()
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            grid[y][x] = '.';
        }
    }

    // Player start
    playerX = 1;
    playerY = 1;

    // Enemy start (right of player, same style as Tomb1)
    enemyX = playerX + 1;
    enemyY = playerY;

    enemy = std::make_unique<Enemy>("Goblin Guard");

    // Relic in far corner
    relicX = gridWidth - 2;
    relicY = gridHeight - 2;
}

void Tomb2::drawRoom(const Player& player) const
{
    std::cout << "--- TOMB 2: The Relic Chamber ---\n";
    std::cout << "Health: " << player.getHealth()
              << " | Key: " << (player.hasTomb2Key() ? "YES" : "NO")
              << " | Relic: " << (player.hasRelic() ? "YES" : "NO") << "\n\n";

    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            if (x == playerX && y == playerY) std::cout << 'P';
            else if (enemy && enemy->isAlive() && x == enemyX && y == enemyY) std::cout << 'E';
            else if (x == relicX && y == relicY) std::cout << 'R';
            else std::cout << grid[y][x];
        }
        std::cout << "\n";
    }

    std::cout << "\nControls: F=Forward  B=Back  L=Left  R=Right  A=Attack  Q=Quit\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << statusMessage << "\n";
}

void Tomb2::onEnemyEncounter(Player& player)
{
    if (!enemy) return;

    int damage = enemy->attack();
    player.takeDamage(damage);

    if (!player.isAlive())
    {
        statusMessage = enemy->getName() + " strikes you down...";
        return;
    }

    statusMessage = "You bump into " + enemy->getName() + "! It hits for " +
                    std::to_string(damage) + ". Press A to kill it.";
}

bool Tomb2::handleMove(char moveCommand, Player& player)
{
    int nextX = playerX;
    int nextY = playerY;

    if (moveCommand == 'F') nextY -= 1;
    else if (moveCommand == 'B') nextY += 1;
    else if (moveCommand == 'L') nextX -= 1;
    else if (moveCommand == 'R') nextX += 1;

    if (nextX < 0 || nextX >= gridWidth || nextY < 0 || nextY >= gridHeight)
    {
        statusMessage = "You hit a wall of carved stone.";
        return true;
    }

    playerX = nextX;
    playerY = nextY;

    if (enemy && enemy->isAlive() && playerX == enemyX && playerY == enemyY)
    {
        onEnemyEncounter(player);
        return true;
    }

    if (playerX == relicX && playerY == relicY)
    {
        player.giveRelic();
        statusMessage = "You found the ANCIENT RELIC! You win!";
        return false; // leave Tomb2
    }

    statusMessage = "You move cautiously through the chamber...";
    return true;
}

bool Tomb2::enter(Player& player)
{
    bool stillInTomb2 = true;

    while (stillInTomb2)
    {
        if (!player.isAlive())
            return false;

        clearScreen();
        drawRoom(player);

        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            statusMessage = "Enter a command (F/B/L/R/A/Q).";
            continue;
        }

        char command = static_cast<char>(std::toupper(input[0]));

        if (command == 'Q')
        {
            statusMessage = "You turn back... the relic remains lost.";
            clearScreen();
            drawRoom(player);
            return false;
        }

        if (command == 'A')
        {
            if (enemy && enemy->isAlive() && playerX == enemyX && playerY == enemyY)
            {
                enemy->kill();
                statusMessage = "You destroy the " + enemy->getName() + " in one strike!";
            }
            else
            {
                statusMessage = "You swing at the air.";
            }
            continue;
        }

        if (command == 'F' || command == 'B' || command == 'L' || command == 'R')
        {
            stillInTomb2 = handleMove(command, player);
        }
        else
        {
            statusMessage = "Unknown command. Use F, B, L, R, A or Q.";
        }
    }

    return true;
}
