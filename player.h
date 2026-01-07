#pragma once
#include <string>

class Player
{
public:
    Player();

    int getHealth() const;
    bool isAlive() const;

    void takeDamage(int amount);

    bool hasTomb2Key() const;
    void giveTomb2Key();

private:
    int health;
    bool tomb2Key;
};