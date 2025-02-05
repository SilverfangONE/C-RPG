// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "log.h"
#include "cJSON.h"
#include "game_core.h"
#include "game_render.h"
#include "game_components.h"
#include "game_to_string.h"

// ---- Load and Exit Game. ----
GameState* loadGame()
{
    log_info("Loading game ...");
    // setup SDL3.
    SDL_Init(SDL_INIT_VIDEO);
    // init game state.
    GameState* game = initGameState();
    // load init env.
    pushEnviroment(game, "./res/enviroments/WORLD/OPEN_WORLD/OPEN_WORLD.json");
    log_info("Loading game completed!");
    printGameState(game, LOG_DEBUG);
    return game;
}

void exitGame(GameState* game)
{
    log_info("TERMINATE_GAME");
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
    destroyGameState(game);
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

// ---- SMOKE-TESTS ----
void smokeTestIMGRender(GameState* game) {
    // test 
    SDL_Texture* img = IMG_LoadTexture(game->renderer, "./res/tilesheets/Studio_Logo.png");
    SDL_FRect texture_rect;
    texture_rect.x = 0; //the x coordinate
    texture_rect.y = 0; //the y coordinate
    texture_rect.w = SNES_PIXEL_WIDTH; //the width of the texture
    texture_rect.h = SNES_PIXEL_HEIGHT; //the height of the texture
    SDL_RenderClear(game->renderer); //clears the renderer
    SDL_RenderRect(game->renderer, &texture_rect);
    if(!SDL_RenderTexture(game->renderer, img, NULL, &texture_rect)) {
        log_error("%s", SDL_GetError());
    }
    SDL_RenderPresent(game->renderer); //updates the renderer
    Sleep(2000);
}