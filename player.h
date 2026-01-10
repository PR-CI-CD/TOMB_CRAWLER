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

    // NEW — relic support
    bool hasRelic() const;
    void giveRelic();

private:
    int health;
    bool tomb2Key;

    // NEW — tracks if relic was found
    bool relic;
};
