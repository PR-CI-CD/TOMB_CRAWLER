#pragma once

class Player;

/*
    Room is an abstract base class (interface).

    Each tomb or area in the game inherits from Room and provides
    its own implementation of enter().

    This enables polymorphism:
    - Game can store rooms using Room* or std::unique_ptr<Room>
    - The correct enter() implementation is called at runtime
*/
class Room
{
public:
    // Virtual destructor ensures correct cleanup when deleting via a base-class pointer
    virtual ~Room() noexcept = default;

    // Run this room and return true if the player progresses, false if the game should end
    virtual bool enter(Player& player) = 0;
};

