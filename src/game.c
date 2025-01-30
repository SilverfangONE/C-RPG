#include <SDL3/SDL.h>
#include <stdio.h>
#include<windows.h>
#include "game.h"
#include "log.h"
#include <time.h>

// ---- GAME SYSTEM ----
const int NES_PIXEL_WIDTH = 256;
const int NES_PIXEL_HEIGHT = 240;
const int TILE_PIXEL_SIZE_B = 16;
const int TILE_PIXEL_SIZE_S = 8;
const int TARGET_FPS = 60;
/*
* Handels SDL Events and Key inputs
*/
void processEvents(GameState* gameState, SDL_Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                if (window) {
                    exitGame(gameState, window);
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
void loadGame(GameState* game, SDL_Window* window, SDL_Renderer* renderer)
{
    printf("LOAD_GAME");
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "RPG",
        NES_PIXEL_WIDTH,
        NES_PIXEL_HEIGHT,
        0
    );
    renderer = SDL_CreateRenderer(window, NULL);
}

/*
* Destroys Windows, Terminates SDL, closes GameState
*/
void exitGame(GameState* gameState, SDL_Window* window)
{
    printf("EXIT_GAME");
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

/*
* Render Graphics from room with postion.
*/
void renderGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer)
{ 
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

/*
* Update GameState logic.
*/
void updateGame(GameState* gameState) 
{
    printf("IMPLEMENT_TODO");
    //log_debug("IMPLEMENT_TODO");
}

/*
* Game Loop.
*/
void loopGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer)
{
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        processEvents(gameState, window);
        updateGame(gameState);
        renderGame(gameState, window, renderer);
    }
}

// ---- ROOM SYSTEM ----
Room* loadRoom(char* tilesetJSONPath) {
    log_debug("IMPLEMENT_TODO");
}