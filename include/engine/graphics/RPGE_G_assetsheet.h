#ifndef RPGE_G_TILESHEET
#define RPGE_G_TILESHEET

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"

typedef struct Assetsheet_RPGE {
    char* ID;
    char* pathIMG;
    SDL_Texture* imgText;
    /**
     * cols and rows of Assetsheet.
     */
    Vec2D vTableSize;
    /**
     * height and width of one patch/tile.
     */
    Vec2D vPatchSize;
} Assetsheet_RPGE;

Assetsheet_RPGE* create_Assetsheet_G_RPGE(SDL_Renderer* render, Vec2D vTableSize, Vec2D vPatchSize, char* ID, char* pathIMG);
void destory_Assetsheet_G_RPGE(Assetsheet_RPGE* assetsheet);
#endif