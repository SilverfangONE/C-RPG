// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include "game_core.h"
#include "game_render.h"
#include "log.h"
#include <time.h>

// ---- GAME SYSTEM ----
// ---- CONSTANTS ----
const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int NES_PIXEL_WIDTH = 256;
const int NES_PIXEL_HEIGHT = 240;
const int TILE_PIXEL_SIZE_B = 16;
const int TILE_PIXEL_SIZE_S = 8;
const int TARGET_FPS = 60;
const int TILES_X = 6;
const int TILES_Y = 6;
const int TILE_COUNT = 6 * 6;
const int TILE_SIZE = 8;
const int TILESET_SLOT_SIZE = 6;
// KEIN USECASE DAFÜR:
// const int TILE_SIZE_ARR[2] = { 8, 16 }; // mapped to tilesize enums.

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
    loadTileset(game, "./res/tilesheet.png", 8, 8, 6, 6, 0);
    loadRoom(game, R_WORLD, 0, 0);
    log_debug("LOAD: GAME: init GameState");
    return game;
}

void loadRoom(GameState* game, enum RoomType type, unsigned int roomID, unsigned int tilesetID)
{
    Room room;
    room.ID = roomID;
    room.type = type;
    room.tileset = lookupTileset(game, tilesetID);
    game->room=room;
    printRoom(&room);
}


void exitGame(GameState* game)
{
    log_info("TERMINATE_GAME");
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    destoryGameState(game);
    exit(0);
}

void destoryGameState(GameState* game) {
    destoryRoom(&game->room);
    destoryDisplay(&game->display);
    // free SDL_Textures;
    for(int i = 0; i < TILESET_SLOT_SIZE; i++) {
        free(game->sets[i]);
    }
    free(game);
}



void destoryRoom(Room* room) {
    // NOTHING TO DESTROY YET.
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

// ---- GAME RENDER ---- 


// ---- PRINT STRUCTS ----
void printTileset(Tileset* tileset) {
    log_debug("\nTILESET:\n{\n\tID=%u;\n\ttextPath=%s;\n\tcols=%d;\n\trows=%d\n}", 
        tileset->ID,
        tileset->textPath,
        tileset->cols,
        tileset->rows    
    );
}

void printRoom(Room* room) {
    log_debug("\nROOM:\n{\n\tID=%u;\n\ttype=%s;",
        room->ID,
        printRoomType(room->type)
    );
    printTileset(room->tileset);
    log_debug("}");
}

char* printRoomType(enum RoomType type) {
    switch(type) {
        case R_MENU: return "MENU";
        case R_WORLD: return "WORLD";
        case R_COMBAT: return "COMBAT";
        default: return "Unkowne";
    }
}

void printDisplay(Display* disp) {
    log_debug("\nDISPLAY:\n{\n\twidth=%d;\n\theight=%d;\n\tscaleX=%f;\n\tscaleY=%f;\n\tx=%f;\n\ty=%f\n}",
        disp->width, 
        disp->height, 
        disp->scaleX, 
        disp->scaleY,
        disp->destRect.x,
        disp->destRect.y
    );
}

void printGameState(GameState* game) {
    log_debug("\nGAME_STATE:\n{");
    printDisplay(&game->display);
    printRoom(&game->room);
    log_debug("}");
}

// ---- SMOKE-TESTS ----
void smokeTestIMGRender(GameState* game) {
    // test 
    SDL_Texture* img = IMG_LoadTexture(game->renderer, "./res/Bang_Manga_Profile.png");
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
    Sleep(1000);
}