#include <SDL3/SDL.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"

int main() 
{
    printf("Hello");

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
