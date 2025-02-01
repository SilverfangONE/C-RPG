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

// ---- LOAD/DESTROY SYSTEMS ----
void loadGame(GameState** gamePtr, SDL_Window** window, SDL_Renderer** renderer)
{
    // setup SDL3.
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
        exitGame(*gamePtr, *window);
    }
    
    // init game state.
    GameState game;
    loadDisplay(&game, *renderer);
    loadRoom(&game, *window, *renderer, "./res/tilesheet.png", WORLD);
    *gamePtr = &game;
}

void loadRoom(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer, char* tilesetTexturePath, enum RoomType type)
{
    log_debug("LOAD:ROOM:Tilesheet->%s", tilesetTexturePath);
    Room room;
    SDL_Texture *texture = IMG_LoadTexture(renderer, tilesetTexturePath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(gameState, window);
    }
    room.tileset = texture;
    room.tilesetPath = tilesetTexturePath;
    room.type = type;
    gameState->room=room;
    printRoom(&room);
}

void loadDisplay(GameState* gameState, SDL_Renderer* renderer) 
{
    Display disp;
    disp.texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        NES_PIXEL_WIDTH, 
        NES_PIXEL_HEIGHT
    );
    // scaling.
    disp.height = NES_PIXEL_HEIGHT;
    disp.width = NES_PIXEL_WIDTH;
    disp.scaleX = WINDOW_WIDTH / NES_PIXEL_WIDTH;
    disp.scaleY = WINDOW_HEIGHT / NES_PIXEL_HEIGHT;
    
    // placement from display in window
    SDL_FRect destR;
    destR.w = disp.width;
    destR.h = disp.height;
    destR.x = WINDOW_WIDTH / 2 - (disp.width / 2);
    destR.y = WINDOW_HEIGHT / 2 - (disp.height / 2);
    disp.destRect = destR;

    gameState->display=disp;
    printDisplay(&disp);
}

void exitGame(GameState* gameState, SDL_Window* window)
{
    log_info("TERMINATE_GAME");
    destoryGameState(gameState);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

void destoryGameState(GameState* gameState) {
    destoryRoom(&gameState->room);
    destoryDisplay(&gameState->display);
}

void destoryDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

void destoryRoom(Room* room) {
    SDL_DestroyTexture(room->tileset);
}

// ---- GAME SYSTEM ----
void processEventsSDL(GameState* gameState, SDL_Window* window) 
{
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

void loopGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer)
{
    // start.
    log_info("START:GAME_LOOP");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        SDL_RenderClear(renderer);
        
        // double start = GetCurrentTime();
        processEventsSDL(gameState, window);
        updateGame(gameState);
        renderGame(gameState, window, renderer);
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

void updateGame(GameState* gameState) 
{
    // TODO
}

// ---- GAME RENDER ---- 
void renderGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer) {
        SDL_RenderClear(renderer);
        SDL_SetRenderScale(renderer, 0, 0);
    
        // set render target to display.
        SDL_SetRenderTarget(renderer, gameState->display.texture);

        // actuall render stuff. 
        renderTile(renderer, gameState->room.tileset, 6, 0, 0);
        renderTile(renderer, gameState->room.tileset, 7, 8, 0);
        renderTile(renderer, gameState->room.tileset, 0, 16, 0);

        // set render target to window.
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderScale(renderer, (float)gameState->display.scaleX, (float)gameState->display.scaleY);
        
        if(!SDL_RenderTexture(renderer, gameState->display.texture, NULL, &gameState->display.destRect)) {
            log_error("%s", SDL_GetError());
        }
        
        // switch buffer.
        SDL_RenderPresent(renderer); //updates the renderer
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

// ---- PRINT STRUCTS ----
void printRoom(Room* room) {
     log_debug("ROOM:{type=%s;tilesetPath=%d}",
        printRoomType(room->type),
        room->tilesetPath
    );
}

char* printRoomType(enum RoomType type) {
    switch(type) {
        case MENU: return "MENU";
        case WORLD: return "WORLD";
        case COMBAT: return "COMBAT";
        default: return "Unkowne";
    }
}

void printDisplay(Display* disp) {
    log_debug("DISPLAY:{width=%d;height=%d;scaleX=%d;scaleY=%d;x=%d;y=%d}",
        disp->width, 
        disp->height, 
        disp->scaleX, 
        disp->scaleY,
        disp->destRect.x,
        disp->destRect.y
    );
}

void printGameState(GameState* gameState) {
    log_debug("GAME_STATE:{");
    printDisplay(&gameState->display);
    printRoom(&gameState->room);
    log_debug("}");
}