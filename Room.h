#pragma once

class Player;

/*
    Room is an abstract base class (interface).
    Each tomb/room inherits from Room and provides its own enter() behaviour.

    This enables polymorphism:
    - Game can store rooms as Room*
    - call rooms[i]->enter(player) without knowing the derived type
*/
class Room
{
public:
    virtual ~Room() {}
    virtual bool enter(Player& player) = 0;
};
