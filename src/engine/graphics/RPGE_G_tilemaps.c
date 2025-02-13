#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "RPGE_G_tilemap.h"

Tilemap_RPGE* create_Tilemap_G_RPGE(Assetsheet_RPGE* asset, Vec2D vTableSize, char* ID) {
    Tilemap_RPGE* tilemap = (Tilemap_RPGE*) malloc(sizeof(Tilemap_RPGE));
    if (tilemap == NULL) {
        return NULL;
    }
    if (ID == NULL || strlen(ID) == 0) {
        log_error("create_Tilemap_G_RPGE: ID is invalid");
        errno = EINVAL;
        return NULL;
    }
    tilemap->ID = (char*) malloc(sizeof(tilemap));
    strncpy(tilemap->ID, ID, sizeof(tilemap->ID));

    if (vTableSize.x == 0 || vTableSize.x == 0) {
        log_error("create_Tilemap_G_RPGE: vTableSize is invalid");
        errno = EINVAL;
        return NULL;
    }
    tilemap->vTableSize = vTableSize;

    if (asset == NULL) {
        log_error("create_Tilemap_G_RPGE: asset is invalid");
        errno = EINVAL;
        return NULL;
    }
    tilemap->asset = asset;
    return asset;
}

void destroy_Tilemap_G_RPGE(Tilemap_RPGE* tilemap) {
    free(tilemap->asset);
    free(tilemap->ID);
    free(tilemap);
}