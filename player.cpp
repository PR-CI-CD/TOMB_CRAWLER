#include "Player.h"

Player::Player()
{
    health = 100;
    tomb2Key = false;
}

int Player::getHealth() const
{
    return health;
}

bool Player::isAlive() const
{
    return health > 0;
}

void Player::takeDamage(int amount)
{
    health -= amount;
    if (health < 0) health = 0;
}

bool Player::hasTomb2Key() const
{
    return tomb2Key;
}

void Player::giveTomb2Key()
{
    tomb2Key = true;
}
