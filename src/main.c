#include <SDL3/SDL.h>
#include <windows.h>
#include "game.h"
#include "log.h"

int main() 
{
    log_info("SETUP: GAME");
    // setup.
    GameState* game;

    // game.
    loadGame(&game);
    loopGame(game);
    exitGame(game);

    return 0;
}
