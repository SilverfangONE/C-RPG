#include <SDL3/SDL.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "log.h"

const int NES_PIXEL_WIDTH = 256;
const int NES_PIXEL_HEIGHT = 240;
const int TILE_PIXEL_SIZE_B = 16;
const int TILE_PIXEL_SIZE_S = 8;

/*
* Handels SDL Events and Key inputs
*/
int processEvents(SDL_Window *window, GameState *gameState) {
    SDL_Event event;
    int done = 0;
    while(SDL_PollEvent(&event))
    {
        switch(event.type) 
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                if(window) {
                    exitGame(window, gameState);
                }
            }
            break;
            case SDL_EVENT_KEY_DOWN:
            {
                switch (event.key.scancode) 
                {
                    case SDL_SCANCODE_UP:
                        log_trace("KEY:UP");
                        break;
                    case SDL_SCANCODE_DOWN:
                        log_trace("KEY:DOWN");
                        break;
                    case SDL_SCANCODE_LEFT:
                        log_trace("KEY:LEFT");
                        break;
                    case SDL_SCANCODE_RIGHT:
                        log_trace("KEY:RIGHT");
                }
            }
        }
    }
}

/*
* Inits: SDL Lib, SDL Window, SDL Renderer, GameState
*/
void loadGame(SDL_Window *window, SDL_Renderer *renderer, GameState* game) 
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "RPG",
        NES_PIXEL_WIDTH,
        NES_PIXEL_HEIGHT,
        0
    );
    renderer = SDL_CreateRenderer(window, NULL);
    GameState gameTemp;
}

/*
* Destroys Windows, Terminates SDL, closes GameState
*/
void exitGame(SDL_Window* window, GameState* gameState) 
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

int main(int argc, char *argv[]) 
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameState* gameState;

    loadGame(window, renderer, gameState);
    
    exitGame(window, gameState);
    return 0;
}
