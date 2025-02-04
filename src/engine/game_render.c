#include "game_render.h"
#include "game_core.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

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

