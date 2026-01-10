#pragma once

#include <memory>
#include <string>
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

/*
    Tomb2:
    - Another enemy encounter
    - Relic is found in this room
    - Demonstrates same scalable Room interface
*/
class Tomb2 : public Room
{
public:
    Tomb2(int width, int height);
    ~Tomb2() override;

    bool enter(Player& player) override;

private:
    int gridWidth;
    int gridHeight;

    char** grid;

    int playerX;
    int playerY;

    int enemyX;
    int enemyY;

    // Smart pointer ownership (RAII)
    std::unique_ptr<Enemy> enemy;

    // Relic position
    int relicX;
    int relicY;

    std::string statusMessage;

    void allocateGrid();
    void freeGrid();
    void buildRoomLayout();

    void drawRoom(const Player& player) const;
    bool handleMove(char moveCommand, Player& player);
    void onEnemyEncounter(Player& player);
};
