#include "game.h"

int main()
{
    // Dynamically allocate the Game controller on the heap
    Game* gameInstance = new Game();   // clearer variable name

    // Start the main game loop
    gameInstance->run();

    // Release allocated memory to prevent leaks
    delete gameInstance;

    return 0;
}

