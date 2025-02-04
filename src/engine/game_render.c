#include "game_render.h"
#include "game_core.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>


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

