#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include "log.h"
#include "game_render.h"
#include "game_core.h"
#include "game_util.h"
#include "game_to_string.h"

void renderGame(GameState* game) {
    // reset.
    if(!SDL_RenderClear(game->renderer)) {
        log_error("%s", SDL_GetError());
    }

    // render on display. 
    SDL_SetRenderTarget(game->renderer, game->display.texture);
    renderEnviromentStack(game, game->envStack.top);

    /*
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
    */

    // render on window.
    SDL_SetRenderTarget(game->renderer, NULL);
    if(!SDL_RenderTexture(game->renderer, game->display.texture, NULL, &game->display.destRect)) {
        log_error("%s", SDL_GetError());
    }
    
    // switch buffer.
    SDL_RenderPresent(game->renderer); //updates the renderer
}

// ---- TILES & SPRITE ----
void renderMatrixMap(GameState* game, Matrix* matrix, TextureAtlas* atlas) {
    for(int row = 0; row < matrix->rows; row++) {
        for(int col = 0; col < matrix->cols; col++) {
            if(getMatrixCell(matrix, col, row) == 0){
                continue;
            }
            renderTextureFromAtlas(game, atlas, getMatrixCell(matrix, col, row) - 1, col*atlas->tileSizeX, row*atlas->tileSizeY);
        }
    }
}

void renderTextureFromAtlas(GameState* game, TextureAtlas* atlas, int tileIndex, int x, int y) {
    const int TILE_SIZE_Y = atlas->tileSizeY;
    const int TILE_SIZE_X = atlas->tileSizeX;
    
    // calc index.
    // int tileY = tileIndex / game->room.tileset->cols; 
    // int tileX = tileIndex % game->room.tileset->cols;
    
    // render stuff.
    SDL_FRect srcR;
    srcR.w = TILE_SIZE_X;
    srcR.h = TILE_SIZE_Y;
    srcR.x = (tileIndex % atlas->cols) * TILE_SIZE_X;
    srcR.y = (tileIndex / atlas->cols) * TILE_SIZE_Y;

    SDL_FRect destR;
    destR.w = TILE_SIZE_X;
    destR.h = TILE_SIZE_Y;
    destR.x = x;
    destR.y = y;

    if(!SDL_RenderTexture(game->renderer, atlas->texture, &srcR, &destR)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
}

void renderPlayer(GameState* game, TextureAtlas* atlas) {
    renderTextureFromAtlas(game, atlas, game->player->textureAtlasIndex ,game->player->x, game->player->y);
}

void renderEnviromentStack(GameState* game, struct EnviromentStackItem* item) {
    if(item->next !=NULL) {
        return renderEnviromentStack(game, item->next);
    }
    struct Enviroment* env = item->env;
    // TODO: implment Render local UI.
    if(env->toRender) {
        // render background Map;
        renderMatrixMap(game, env->sub->map->backgroundMap, env->tilesheet);
        
        // render middelground Map;
        renderMatrixMap(game, env->sub->map->middelgroudMap, env->tilesheet);
        
        // render sprites;
        renderMatrixMap(game, env->sub->map->spriteMap, env->spritesheet);

        // render player;
        renderPlayer(game, env->spritesheet);
        // env->sub->map->backgroundMap; 
    }
    return;
}