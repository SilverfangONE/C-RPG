// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "game_core.h"
#include "game_render.h"
#include "game_util.h"
#include "log.h"
#include "cJSON.h"

// temp
int roomIDCounter = 0;

// ---- LOAD/DESTROY SYSTEMS ----
GameState* loadGame()
{
    GameState* game = (GameState*)malloc(sizeof(GameState));
    // set sets to NULL default
    for(int i = 0; i < TILESET_SLOT_SIZE; i++)
    {
        game->sets[i] = NULL;
    }
 
    log_info("LOAD: GAME");
    // setup SDL3.
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_CreateWindowAndRenderer(
        "C-RPG",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        &game->window,
        &game->renderer
    )) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    log_debug("LOAD: GAME: init SDL3");
    // init game state.
    loadDisplay(game);
    loadTileset(game, "./res/tilesheets/tilesheet.8..png", 8, 8, 6, 6, 0);
    loadRoom(game, R_WORLD, 0, 0);
    log_debug("LOAD: GAME: init GameState");
    return game;
}

void exitGame(GameState* game)
{
    log_info("TERMINATE_GAME");
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    destoryGameState(game);
    exit(0);
}



// ---- GAME SYSTEM ----
void processEventsSDL(GameState* game) 
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                exitGame(game);
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

void updateGame(GameState* game) 
{
    // TODO
}

void loopGame(GameState* game)
{
    smokeTestIMGRender(game);
    // start.
    log_info("GAME_LOOP:START");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        // double start = GetCurrentTime();
        processEventsSDL(game);
        updateGame(game);
        renderGame(game);
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

// ---- ENV SYSTEM ----







struct EnviromentStackItem* createEnviromentStackItem(
    struct EnviromentStackItem* prev,  
    struct EnviromentStackItem* next,
    struct Enviroment* env
) {
    struct EnviromentStackItem *item = malloc(sizeof(struct EnviromentStackItem));   
    item->env = env;
    item->prev = prev;
    item->next = next;
    return item;
}



// ---- SMOKE-TESTS ----
void smokeTestIMGRender(GameState* game) {
    // test 
    SDL_Texture* img = IMG_LoadTexture(game->renderer, "./res/tilesheets/Studio_Logo.png");
    SDL_FRect texture_rect;
    texture_rect.x = 0; //the x coordinate
    texture_rect.y = 0; //the y coordinate
    texture_rect.w = NES_PIXEL_WIDTH; //the width of the texture
    texture_rect.h = NES_PIXEL_HEIGHT; //the height of the texture
    SDL_RenderClear(game->renderer); //clears the renderer
    SDL_RenderRect(game->renderer, &texture_rect);
    if(!SDL_RenderTexture(game->renderer, img, NULL, &texture_rect)) {
        log_error("%s", SDL_GetError());
    }
    SDL_RenderPresent(game->renderer); //updates the renderer
    Sleep(2000);
}