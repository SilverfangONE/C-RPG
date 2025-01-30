#include <SDL3/SDL.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "log.h"

int main(int argc, char *argv[]) 
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameState* gameState;

    loadGame(window, renderer, gameState);
    
    exitGame(window, gameState);
    return 0;
}
