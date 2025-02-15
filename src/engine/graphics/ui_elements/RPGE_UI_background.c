#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdlib.h>
#include "log.h"
#include "RPGE_G_assetsheet.h" 
#include "RPGE_U_array.h"
#include "RPGE_UI_background.h"

int render_Background_UI_RPGE(SDL_Renderer* renderer, BACKGROUND_UI_RPGE* background) {
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

BACKGROUND_UI_RPGE* create_Background_UI_RPGE(Assetsheet_RPGE* asset, int* m_indices, Vec2D vCoordinates, Vec2D vTableSize ) {
    BACKGROUND_UI_RPGE* background = (BACKGROUND_UI_RPGE*) malloc(sizeof(BACKGROUND_UI_RPGE));
    if (background == NULL) return NULL;
    if (asset == NULL) {
        errno = EINVAL;
        return NULL;
    }
    background->asset = asset;
    if(copy_Array_UTIL(background->m_indices, vTableSize.x * vTableSize.y) == NULL) {
        return NULL;
    }
    background->vCoordinates = vCoordinates;
    if (vTableSize.x == 0 || vTableSize.y == 0) {
        log_error("create_Background_UI_RPGE: vTableSize(.x=%d, .y=%d) is invalid", vTableSize.x, vTableSize.y);
        errno = EINVAL;
        return NULL;
    }
    background->vTableSize = vTableSize;
    return background;
}

void destroy_Background_UI_RPGE(BACKGROUND_UI_RPGE* background) {
    free(background->m_indices);
    free(background);
}

int getIndex_Background_MENU_TILE_UI_RPGE(enum MENU_TILE_TYPE tile) {
    switch (tile)
    {
        case UP_LEFT_CORN:
            return;
        case UP_RIGTH_CORN:
            return;
        case DOWN_LEFT_CORN:
            return;
        case DOWN_RIGTH_CORN:
            return;
        case NORTH_MID:
            return;
        case EAST_MID:
            return;
        case WEST_MID:
            return;
        case SOUTH_MID:
            return;
        default:
            return -1;
    default:
        break;
    }
}