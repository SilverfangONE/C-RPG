// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "log.h"
#include "cJSON.h"
#include "game_core.h"
#include "game_logic.h"
#include "game_render.h"
#include "game_components.h"
#include "game_to_string.h"

#ifdef _WIN32
    #include <windows.h>
#else 
    #include <unistd.h>
#endif

void sleep_ms(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

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

void loopGame(GameState* game)
{   
    // smokeTestIMGRender(game);
    // start.
    loadPlayer(game, 0, 0, 16, 16, 2, 0);
    log_info("START: Game Loop ... ");
    int run = 1;
    int FRAME_TIME = 1000 / TARGET_FPS;
    while (run) {
        clock_t start_time = clock();
        processEventsSDL(game);
        updateGame(game);
        renderGame(game);
        clock_t end_time = clock();
        double elapsed_ms = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC; 
        if(elapsed_ms < FRAME_TIME) {
            sleep_ms(FRAME_TIME - (int)elapsed_ms);
        }   
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