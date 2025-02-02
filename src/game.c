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
    loadRoom(game, WORLD, 0, 0);
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
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(disp.texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    // scaling.
    disp.height = NES_PIXEL_HEIGHT;
    disp.width = NES_PIXEL_WIDTH;
    // quadrtic scale;
    int scaleXInt = WINDOW_WIDTH / NES_PIXEL_WIDTH;
    int scaleYInt = WINDOW_HEIGHT / NES_PIXEL_HEIGHT;
    if(scaleXInt < scaleYInt) {
        scaleYInt = scaleXInt;
    } else {
        scaleXInt = scaleYInt;
    }
    
    disp.scaleX = (float) scaleXInt;
    disp.scaleY = (float) scaleYInt;
    
    // placement from display in window
    SDL_FRect destR;
    destR.w = (float) disp.width * disp.scaleX;
    destR.h = (float) disp.height * disp.scaleY;
    destR.x = (float) (WINDOW_WIDTH - destR.w) / 2;
    destR.y = (float) (WINDOW_HEIGHT - destR.h) / 2;
    disp.destRect = destR;

    game->display=disp;
    printDisplay(&disp);
}

// TODO: später steht das alles in einer json datei. => dan nur pfad zur json datei und zur texture
void loadTileset(GameState* game, char* tilesetTexturePath, int tileSizeX, int tileSizeY, int cols, int rows, unsigned int ID) {
    Tileset** slotPtr = getTilesetSaveSlot(game);
    if(slotPtr == NULL) {  
        log_error("GAME_STATE: Can't load new TILESET:{path=%s;ID=%u}, because no slot is free!", tilesetTexturePath, ID);
    }   
    Tileset* tileset = (Tileset*)malloc(sizeof(Tileset));
    tileset->ID = ID;
    SDL_Texture *texture = IMG_LoadTexture(game->renderer, tilesetTexturePath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    tileset->texture = texture;
    tileset->cols = cols;
    tileset->rows = rows;
    tileset->tileSizeX = tileSizeX;
    tileset->tileSizeY = tileSizeY;
    strncpy(tileset->textPath, tilesetTexturePath, sizeof(tileset->textPath) - 1);
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    *slotPtr = tileset;
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

void destoryDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

void destoryRoom(Room* room) {
    // NOTHING TO DESTROY YET.
}

// ---- GAME SYSTEM ----
Tileset** getTilesetSaveSlot(GameState* game) {
    // checks if a free slot is avaiable 
    for(int i = 0; i < TILESET_SLOT_SIZE; i++) {
        if(game->sets[i] == NULL) {
            return &game->sets[i];
        }
    }
    log_warn("GAME_STATE: NO slot is free for loading new Tilesset!");
    return NULL;
}

Tileset* lookupTileset(GameState* game, unsigned int tilesetID) {
    // currently gamestate can hold for 4 tilesets
    for(int i = 0; i < 4; i++) {
        if(game->sets[i]->ID == tilesetID) {
            return game->sets[i];
        }
    }
    log_error("Tilset with ID=%u not found in GameState!", tilesetID);
    exitGame(game);
}

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
void renderGame(GameState* game) {
    // reset.
    if(!SDL_RenderClear(game->renderer)) {
        log_error("%s", SDL_GetError());
    }
    // set render target to display.
    SDL_SetRenderTarget(game->renderer, game->display.texture);

    // actuall render stuff. 
    for(int y = 0; y < NES_PIXEL_HEIGHT / game->room.tileset->tileSizeY; y++) 
    {
        for(int x = 0; x < NES_PIXEL_WIDTH / game->room.tileset->tileSizeX; x++) 
        {
            renderTileFromRoom(
                game, 
                0, 
                x * game->room.tileset->tileSizeX, 
                y * game->room.tileset->tileSizeY
            );
        }
    }

    SDL_SetRenderTarget(game->renderer, NULL);
    if(!SDL_RenderTexture(game->renderer, game->display.texture, NULL, &game->display.destRect)) {
        log_error("%s", SDL_GetError());
    }
    
    // switch buffer.
    SDL_RenderPresent(game->renderer); //updates the renderer
}

// ---- TILES & SPRITE ----
void renderTileFromRoom(GameState* game, int tileIndex, int x, int y) {
    const int TILE_SIZE_Y = game->room.tileset->tileSizeY;
    const int TILE_SIZE_X = game->room.tileset->tileSizeX;
    
    // calc index.
    // int tileY = tileIndex / game->room.tileset->cols; 
    // int tileX = tileIndex % game->room.tileset->cols;
    
    // render stuff.
    SDL_FRect srcR;
    srcR.w = TILE_SIZE_X;
    srcR.h = TILE_SIZE_Y;
    srcR.x = (tileIndex % game->room.tileset->cols) * TILE_SIZE_X;
    srcR.y = (tileIndex / game->room.tileset->cols) * TILE_SIZE_Y;

    SDL_FRect destR;
    destR.w = TILE_SIZE_X;
    destR.h = TILE_SIZE_Y;
    destR.x = x;
    destR.y = y;

    if(!SDL_RenderTexture(game->renderer, game->room.tileset->texture, &srcR, &destR)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
}

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
        case MENU: return "MENU";
        case WORLD: return "WORLD";
        case COMBAT: return "COMBAT";
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