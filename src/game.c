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
void loadGame(GameState** gamePtr)
{
    log_info("LOAD: GAME");

    // setup SDL3.
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_CreateWindowAndRenderer(
        "C-RPG",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        &window,
        &renderer
    )) {
        log_error("%s", SDL_GetError());
        exitGame(*gamePtr);
    }
    log_debug("LOAD: GAME: init SDL3");
    // init game state.
    GameState game;
    game.renderer = renderer;
    game.window = window;
    loadDisplay(&game);
    loadRoom(&game, "./res/tilesheet.png", WORLD);
    *gamePtr = &game;

    log_debug("LOAD: GAME: init GameState");
}

void loadRoom(GameState* game, char* tilesetTexturePath, enum RoomType type)
{
    log_debug("LOAD:ROOM:Tilesheet->%s", tilesetTexturePath);
    Room room;
    SDL_Texture *texture = IMG_LoadTexture(game->renderer, tilesetTexturePath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    room.tileset = texture;
    room.tilesetPath = tilesetTexturePath;
    room.type = type;
    game->room=room;
    printRoom(&room);
}

void loadDisplay(GameState* game) 
{
    Display disp;
    disp.texture = SDL_CreateTexture(
        game->renderer, 
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

    game->display=disp;
    printDisplay(&disp);
}

void exitGame(GameState* game)
{
    log_info("TERMINATE_GAME");
    destoryGameState(game);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(0);
}

void destoryGameState(GameState* game) {
    destoryRoom(&game->room);
    destoryDisplay(&game->display);
}

void destoryDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

void destoryRoom(Room* room) {
    SDL_DestroyTexture(room->tileset);
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

void loopGame(GameState* game)
{
    // start.
    log_info("START:GAME_LOOP");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        SDL_RenderClear(game->renderer);
        
        // double start = GetCurrentTime();
        processEventsSDL(game);
        updateGame(game);
        renderGame(game);
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

void updateGame(GameState* game) 
{
    // TODO
}

// ---- GAME RENDER ---- 
void renderGame(GameState* game) {
        SDL_RenderClear(game->renderer);
        SDL_SetRenderScale(game->renderer, 0, 0);
    
        // set render target to display.
        SDL_SetRenderTarget(game->renderer, game->display.texture);

        // actuall render stuff. 
        renderTile(game, game->room.tileset, 6, 0, 0);
        renderTile(game, game->room.tileset, 7, 8, 0);
        renderTile(game, game->room.tileset, 0, 16, 0);

        // set render target to window.
        SDL_SetRenderTarget(game->renderer, NULL);
        SDL_SetRenderScale(game->renderer, (float)game->display.scaleX, (float)game->display.scaleY);
        
        if(!SDL_RenderTexture(game->renderer, game->display.texture, NULL, &game->display.destRect)) {
            log_error("%s", SDL_GetError());
        }
        
        // switch buffer.
        SDL_RenderPresent(game->renderer); //updates the renderer
}

// ---- TILES & SPRITE ----
void renderTile(GameState* game, SDL_Texture* tilesetTexture, int tileIndex, int x, int y) {
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

    if(!SDL_RenderTexture(game->renderer, tilesetTexture, &srcR, &destR)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
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

void printGameState(GameState* game) {
    log_debug("GAME_STATE:{");
    printDisplay(&game->display);
    printRoom(&game->room);
    log_debug("}");
}