#include "Game.h"

#include <iostream>

int main()
{
    Game game;

    game.Initialise();
    game.Run();
    game.Shutdown();

    return 0;
}