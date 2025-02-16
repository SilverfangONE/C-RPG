#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdlib.h>
#include "log.h"
#include "RPGE_U_vec.h"
#include "RPGE_U_array.h"
#include "RPGE_G_assetsheet.h" 
#include "RPGE_U_array.h"
#include "RPGE_UI_background.h"

/**
 * Lookup for tile compoents of background menu.
 */
static int (*flookupBackgroundTiles_UI_RPGE)(enum MENU_TILE_TYPE) =  &getIndex_Background_MENU_TILE_UI_RPGE;

int lookup_BackgroundTiles_UI_RPGE(enum MENU_TILE_TYPE tile) {
    return flookupBackgroundTiles_UI_RPGE(tile);
}

int set_flookupBackgroundTiles_UI_RPGE(int (*newflookupBackgroundTiles_UI_RPGE)(enum MENU_TILE_TYPE)) {
    if (newflookupBackgroundTiles_UI_RPGE == NULL) return 1;
    flookupBackgroundTiles_UI_RPGE = newflookupBackgroundTiles_UI_RPGE;
    return 0;
}

void set_flookupBackgroundTiles_DEFAULT_UI_RPGE() {
    flookupBackgroundTiles_UI_RPGE = &getIndex_Background_MENU_TILE_UI_RPGE;
}

static int getIndex_Background_MENU_TILE_UI_RPGE(enum MENU_TILE_TYPE tile) {
    switch (tile)
    {
        case MENU_UP_LEFT_CORN:
            return 0;
        case MENU_UP_RIGTH_CORN:
            return 2;
        case MENU_DOWN_LEFT_CORN:
            return 12;
        case MENU_DOWN_RIGTH_CORN:
            return 14;
        case MENU_NORTH_BOARDER_MID:
            return 1;
        case MENU_EAST_BOARDER_MID:
            return 8;
        case MENU_WEST_BOARDER_MID:
            return 6;
        case MENU_SOUTH_BOARRDER_MID:
            return 13;
        case MENU_MID:
            return 7;
        default:
            return -1;
    }
}

int render_Background_UI_RPGE(SDL_Renderer* renderer, Background_UI_RPGE* background) {
    if (background == NULL) {
        errno = EINVAL;
        return 1;
    }
    int xSize = background->vTableSize.x;
    int ySize = background->vTableSize.y;
    for (int yTable = 0; yTable < ySize; yTable++) {
        for (int xTable = 0; xTable < xSize; xTable++) {
            Vec2D cor = {
                .x=background->vCoordinates.x + xTable * background->asset->vPatchSize.x, 
                .y=background->vCoordinates.y + yTable * background->asset->vPatchSize.y
            };
            if(renderTile_Assetsheet_G_RPGE(renderer, background->asset, getCell_ARRAY2D_UTIL(background->m_indices, background->vTableSize, xTable, yTable), cor)) {
                return 1; 
            }
        }
    }
    return 0;
}

Background_UI_RPGE* build_Background_UI_RPGE(Assetsheet_RPGE* asset, Vec2D vCoordinates, Vec2D vTableSize ) {
    Background_UI_RPGE* background = (Background_UI_RPGE*) malloc(sizeof(Background_UI_RPGE));
    if (background == NULL) return NULL;
    if (asset == NULL) {
        log_error("create_Background_UI_RPGE: asset is invalid");
        errno = EINVAL;
        return NULL;
    }
    background->asset = asset;
    background->vCoordinates = vCoordinates;
    if (vTableSize.x == 0 || vTableSize.y == 0) {
        log_error("create_Background_UI_RPGE: vTableSize(.x=%d, .y=%d) is invalid", vTableSize.x, vTableSize.y);
        errno = EINVAL;
        return NULL;
    }
    background->vTableSize = vTableSize;
    background->m_indices = constructBackgroundIndexArr_UI_RPGE(vTableSize);
    if (background->m_indices == NULL) return NULL;
    return background;
}

static int* constructBackgroundIndexArr_UI_RPGE(Vec2D vTableSize) {
    // build.
    int* m_indices = create_ARRAY2D_UTIL(vTableSize, lookup_BackgroundTiles_UI_RPGE(MENU_MID));
    if (m_indices == NULL) return NULL;
    //  set corners.
    setCell_ARRAY2D_UTIL(m_indices, vTableSize, 0, 0, lookup_BackgroundTiles_UI_RPGE(MENU_UP_LEFT_CORN));
    setCell_ARRAY2D_UTIL(m_indices, vTableSize, vTableSize.x - 1, 0, lookup_BackgroundTiles_UI_RPGE(MENU_UP_RIGTH_CORN));
    setCell_ARRAY2D_UTIL(m_indices, vTableSize, 0, vTableSize.y - 1, lookup_BackgroundTiles_UI_RPGE(MENU_DOWN_LEFT_CORN));
    setCell_ARRAY2D_UTIL(m_indices, vTableSize, vTableSize.x - 1, vTableSize.y - 1, lookup_BackgroundTiles_UI_RPGE(MENU_DOWN_RIGTH_CORN));
    // set boarders.
    // sides.
    for (int y = 1; y < vTableSize.y - 1; y++) {
        // left
        setCell_ARRAY2D_UTIL(m_indices, vTableSize, 0, y, lookup_BackgroundTiles_UI_RPGE(MENU_WEST_BOARDER_MID));
        // rigth
        setCell_ARRAY2D_UTIL(m_indices, vTableSize, vTableSize.x - 1, y, lookup_BackgroundTiles_UI_RPGE(MENU_EAST_BOARDER_MID));
    }
    // top and down 
    for (int x = 1; x < vTableSize.x - 1; x++) {
        // top
        setCell_ARRAY2D_UTIL(m_indices, vTableSize, x, 0, lookup_BackgroundTiles_UI_RPGE(MENU_NORTH_BOARDER_MID));
        // down
        setCell_ARRAY2D_UTIL(m_indices, vTableSize, x, vTableSize.y - 1, lookup_BackgroundTiles_UI_RPGE(MENU_SOUTH_BOARRDER_MID));
    }
    return m_indices;
}

void destroy_Background_UI_RPGE(Background_UI_RPGE* background) {
    free(background->m_indices);
    free(background);
}