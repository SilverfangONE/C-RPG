#include "game_core.h"
#include "log.h"

int main() 
{
    log_info("SETUP: GAME");
    // game.
    loopGame(loadGame());
    return 0;
}
