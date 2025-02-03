#include "game_render.h"
#include "game_core.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

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

void destoryDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

void destoryUIElement(struct UIElement* uiEl) {
    // TODO
    free(uiEl);
}