#include "game.h"

int main()
{
    // Game object allocated on the heap
    Game* game = new Game();

    // Use pointer to run the game
    game->run();

    // Clean up memory
    delete game;

    return 0;
}

