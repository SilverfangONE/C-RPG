
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
    log_info("LOAD_GAME");
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
    log_info("TERMINATE_GAME");
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
    // TODO 
}

/*
* Game Loop.
*/
void loopGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer)
{
    log_info("START_GAME_LOOP");
    log_info("AFTER_WAIT");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        double start = GetCurrentTime();
        processEvents(gameState, window);
        updateGame(gameState);
        renderGame(gameState, window, renderer);
        Sleep(start + frameDelay - GetCurrentTime());
    }
}

// ---- ROOM SYSTEM ----
Room* loadRoom(char* tilesetJSONPath) {
    log_debug("IMPLEMENT_TODO");
    Room room;
    return &room;
}

// ---- TILES & SPRITE ----
typedef struct {
    int w; // pixel width
    int h; // pixel height
} Dimension;

typedef struct {
    SDL_Texture** tilesset;
    int** tilemap;
    Dimension tileDim;
} Tilesheet;

SDL_Point getsize(SDL_Texture* texture) {
    Dimension dim;
    SDL_QueryTexture(texture, NULL, NULL, &dim.x, &dim.y);
    return dim;
}

/*
* 
*/
Tilesheet* createTilesheet(SDL_Renderer* renderer, char* tilesheetJSON, char* tilesheetIMG) {

}

SDL_Texture** tiles createTileset(SDL_Renderer* renderer, char* path, int dimension)
{
    log_trace("CREATE_TILESET:->%s", path);
    SDL_Texture* tilesheet = IMG_LoadTexture(renderer, path);
    // SDL_Texture* tiles[] = 
    return void**;
}