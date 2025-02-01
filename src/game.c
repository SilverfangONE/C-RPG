// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "log.h"
#include <time.h>

// ---- GAME SYSTEM ----
// ---- CONSTANTS ----
const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;
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
                exitGame(gameState, window);
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
void loadGame(GameState** gamePtr, SDL_Window** window, SDL_Renderer** renderer)
{
    log_info("LOAD: GAME");
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_CreateWindowAndRenderer(
        "C-RPG",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        window,
        renderer
    )) {
        log_error("%s", SDL_GetError());
        exitGame(&gamePtr, *window);
    }

    // init game state.
    // scalling.
    int scaleHeight = WINDOW_HEIGHT / NES_PIXEL_HEIGHT; 
    int scaleWidth = WINDOW_WIDTH / NES_PIXEL_WIDTH;
    log_trace("scaleH:%d | scaleW:%d", scaleHeight, scaleWidth);
    log_trace("DisplayDim: width:%d | height:%d", NES_PIXEL_HEIGHT * scaleHeight, NES_PIXEL_WIDTH * scaleWidth);
    SDL_SetRenderScale(&renderer, (float)scaleWidth, (float)scaleHeight);

    GameState game;
    game.display = SDL_CreateTexture(
        &renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        NES_PIXEL_WIDTH * scaleWidth, 
        NES_PIXEL_HEIGHT * scaleHeight
    );
    
}

/*
* Destroys Windows, Terminates SDL, closes GameState
*/
void exitGame(GameState* gameState, SDL_Window* window)
{
    log_info("TERMINATE_GAME");
    destoryGameState(gameState);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
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
    // test 
    SDL_Texture* img = IMG_LoadTexture(renderer, "./res/tilesheet.png");
    // start.
    log_info("START:GAME_LOOP");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        SDL_RenderClear(renderer);
        
        // double start = GetCurrentTime();
        processEvents(gameState, window);
        updateGame(gameState);
        // renderGame(gameState, window, renderer);
        
        SDL_FRect srcRect;
        srcRect.x = 0; //the x coordinate
        srcRect.y = 0; //the y coordinate
        srcRect.w = TILE_SIZE; //the width of the texture
        srcRect.h = TILE_SIZE; //the height of the texture

        SDL_FRect destRect;
        destRect.x = 0; //the x coordinate
        destRect.y = 0; //the y coordinate
        destRect.w = TILE_SIZE; //the width of the texture
        destRect.h = TILE_SIZE; //the height of the texture

        renderTile(renderer, img, 6, 0, 0);
        
        SDL_RenderPresent(renderer); //updates the renderer
        
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

// ---- ROOM SYSTEM ----
void loadRoom(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer, char* tilesetTexturePath, enum RoomType type)
{
    log_debug("LOAD:ROOM:Tilesheet->%s", tilesetTexturePath);
    Room room;
    SDL_Texture *texture = IMG_LoadTexture(renderer, tilesetTexturePath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(gameState, window);
    }
    room.tilesetTexture = texture;
    room.type = type;
    gameState->room=room;
}

void destoryRoom(Room* room) {
    SDL_DestroyTexture(room->tilesetTexture);
}

void destoryGameState(GameState* gameState) {
    destoryRoom(&gameState->room);
    SDL_DestroyTexture(gameState->display);
}


// 

// .... RENDER_SYSTEM ....
// ---- SCREEN ----
/*
* by sccuess returns 1; 
*/
int renderGame(SDL_Renderer* renderer, SDL_Texture* tilesetTexture) {


}

// ---- TILES & SPRITE ----
void renderTile(SDL_Renderer* renderer, SDL_Texture* tilesetTexture, int tileIndex, int x, int y) {
    // calc index.
    int tileY = tileIndex / TILES_X; 
    int tileX = tileIndex % TILES_X;
    log_debug("tileY=%d | tileX=%d", tileY, tileX);
    
    // render stuff.
    SDL_FRect srcR;
    srcR.w = TILE_SIZE;
    srcR.h = TILE_SIZE;
    srcR.x = tileX * TILE_SIZE;
    srcR.y = tileY * TILE_SIZE;

    SDL_FRect destR;
    destR.w = TILE_SIZE;
    destR.h = TILE_SIZE;
    destR.x = x;
    destR.y = y;

    if(!SDL_RenderTexture(renderer, tilesetTexture, &srcR, &destR)) {
        log_error("%s", SDL_GetError());
    }
}
