#include "Player.h"

Player::Player()
{
    // Initialise player starting state
    health = 100;
    tomb2Key = false;

    // NEW
    relic = false;
}

int Player::getHealth() const
{
    return health;
}

bool Player::isAlive() const
{
    // Player is alive if health is greater than zero
    return health > 0;
}

void Player::takeDamage(int amount)
{
    // Reduce health by the damage amount
    health -= amount;

    // Prevent health from going below zero
    if (health < 0)
    {
        health = 0;
    }
}

bool Player::hasTomb2Key() const
{
    return tomb2Key;
}

void Player::giveTomb2Key()
{
    // Player now owns the key to Tomb 2
    tomb2Key = true;
}

bool Player::hasRelic() const
{
    return relic;
}

void Player::giveRelic()
{
    relic = true;
}

