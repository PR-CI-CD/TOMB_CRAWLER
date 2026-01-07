#pragma once
#include <string>

class Enemy
{
public:
    Enemy(const std::string& enemyName);

    const std::string& getName() const;
    bool isAlive() const;

    // Returns random damage in range 1-10
    int attack();

    // Your attack kills instantly (as per your spec)
    void kill();

private:
    std::string name;
    bool alive;
};
