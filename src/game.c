
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "log.h"
#include <time.h>

// ---- GAME SYSTEM ----
// ---- CONSTANTS ----
const int NES_PIXEL_WIDTH = 256;
const int NES_PIXEL_HEIGHT = 240;
const int TILE_PIXEL_SIZE_B = 16;
const int TILE_PIXEL_SIZE_S = 8;
const int TARGET_FPS = 60;
const int TILES_X = 6;
const int TILES_Y = 6;
const int TILE_COUNT = 6 * 6;
const int TILE_SIZE = 8;

// temp
int roomIDCounter = 0;

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
    Room room = loadRoom(renderer, "res/tilesheet.png");
    game->currentRoom = &room;
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
    // log_trace("Render:");
    SDL_RenderClear(renderer);
    for(int y = 0; y < 30; y++ ) {
        for(int x = 0; x < 32; x++) {
            renderTile(renderer, gameState->currentRoom->tilesheet, 0, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
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
        // double start = GetCurrentTime();
        processEvents(gameState, window);
        updateGame(gameState);
        renderGame(gameState, window, renderer);
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

// ---- ROOM SYSTEM ----
Room loadRoom(SDL_Renderer* renderer, char* imgPath)
{
    log_debug("LOAD->ROOM:Tilesheet->%s", imgPath);
    Room room;
    room.id = roomIDCounter++;
    SDL_Texture * lol = IMG_LoadTexture(renderer, imgPath);
    room.tilesheet = lol;
    room.type = MENU;
    return room;
}

void DestoryRoom(Room* room) {
    SDL_DestroyTexture(room->tilesheet);
}

// ---- TILES & SPRITE ----
void renderTile(SDL_Renderer* renderer, SDL_Texture* tilesheet, int tileIndex, int x, int y) {
    SDL_FRect  srcRect = { (tileIndex % TILES_X) * TILE_SIZE, (tileIndex / TILES_X) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_FRect  destRect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderTexture(renderer, tilesheet, &srcRect, &destRect);
}