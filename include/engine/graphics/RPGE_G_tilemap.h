#ifndef RPGE_G_TILEMAP 
#define RPGE_G_TILEMAP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_U_matrix.h"
#include "RPGE_G_assetsheet.h"

typedef struct Tilemap_RPGE {
    Assetsheet_RPGE* asset;    
    Vec2D vTableSize;
    char* ID;
} Tilemap_RPGE;

Tilemap_RPGE* create_Tilemap_G_RPGE(Assetsheet_RPGE* asset, Vec2D vTableSize, char* ID);
void destroy_Tilemap_G_RPGE(Tilemap_RPGE*);

#endif