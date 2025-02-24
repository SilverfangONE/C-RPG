#ifndef RPGE_G_TILEMAP
#define RPGE_G_TILEMAP

#include <stdbool.h>
#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

typedef struct Tile_G_RPGE {
    bool solid;
    int index;
} Tile_G_RPGE;

typedef struct Tilemap_G_RPGE {
    Vec2D vCoordinates;
    Vec2D vTableSize;
    Tile_G_RPGE* tiles;
    Assetsheet_RPGE* asset;
} Tilemap_G_RPGE;
#endif