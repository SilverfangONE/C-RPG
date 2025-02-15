#ifndef RPGE_G_TILEMAP 
#define RPGE_G_TILEMAP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_U_matrix.h"
#include "RPGE_G_assetsheet.h"

typedef struct Tilemap_RPGE {
    char* ID;
    Assetsheet_RPGE* asset;    
    Vec2D vTableSize;
    int* m_indices;
    bool* m_solid;
} Tilemap_RPGE;

Tilemap_RPGE* create_Tilemap_G_RPGE(Assetsheet_RPGE* asset, Vec2D vTableSize, char* ID);
void destroy_Tilemap_G_RPGE(Tilemap_RPGE*);
int getIndex_Tilemap_G_RPGE(Tilemap_RPGE* map, int x, int y);
bool getSolid_Tilemap_G_RPGE(int x, int y);
void setIndices_Tilemap_G_RPGE(Tilemap_RPGE* map, int* m_indices, int indicesLength );
void setSolids_Tilemap_G_RPGE(Tilemap_RPGE* map, bool* m_solid, int solidLength );
#endif