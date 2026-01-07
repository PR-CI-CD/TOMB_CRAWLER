#include "Enemy.h"
#include <cstdlib>  // rand()

Enemy::Enemy(const std::string& enemyName)
{
    name = enemyName;
    alive = true;
}

const std::string& Enemy::getName() const
{
    return name;
}

bool Enemy::isAlive() const
{
    return alive;
}

int Enemy::attack()
{
    // Random damage between 1 and 10 (inclusive)
    return (std::rand() % 10) + 1;
}

void Enemy::kill()
{
    alive = false;
}

