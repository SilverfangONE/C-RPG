#include <SDL3/SDL.h>
#include <windows.h>
#include "game.h"
#include "log.h"

int main() 
{
    log_set_level(LOG_TRACE);
    log_debug("LOLOL");
    log_info("LAUNCH_GAME");
    // setup.
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameState gameState;

    // game.
    loadGame(&gameState, window, renderer);
    loopGame(&gameState, window, renderer);
    exitGame(&gameState, window);

    return 0;
}
