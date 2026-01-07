#pragma once

#include <memory>      // std::unique_ptr, std::make_unique
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

/*
    Tomb1 inherits from Room to demonstrate polymorphism.

    Key assessment features present here:
    - Polymorphism: Tomb1 : Room, overrides enter(Player&)
    - Dynamic arrays: char** grid created with new[] and freed with delete[]
    - Pointers: grid uses raw pointers (manual memory management), enemy uses smart pointer
    - Smart pointers (rewarded): std::unique_ptr<Enemy> for exclusive ownership (RAII)
*/
class Tomb1 : public Room
{
public:
    Tomb1(int width, int height);
    ~Tomb1() override;

    // Polymorphic room entry point
    bool enter(Player& player) override;

private:
    int gridWidth;
    int gridHeight;

    // Dynamic 2D grid stored on the heap (manual memory management)
    char** grid;

    // Player position inside the grid
    int playerX;
    int playerY;

    // Enemy position (to the right of player start)
    int enemyX;
    int enemyY;

    // Smart pointer: Tomb1 owns the enemy and releases it automatically (RAII)
    std::unique_ptr<Enemy> enemy;

    // Door position (locked unless player has key)
    int doorX;
    int doorY;

    void allocateGrid();
    void freeGrid();
    void buildRoomLayout();

    void drawRoom(const Player& player) const;

    bool handleMove(char moveCommand, Player& player);
    void onEnemyEncounter(Player& player);
};

