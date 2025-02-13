#include <errno.h>
#include <string.h>
#include "log.h"
#include "RPGE_G_assetsheet.h"

Assetsheet_RPGE* create_Assetsheet_G_RPGE(SDL_Renderer* renderer, Vec2D vTableSize, Vec2D vPatchSize, char* ID, char* pathIMG) {
    Assetsheet_RPGE* asset = (Assetsheet_RPGE*) malloc(sizeof(Assetsheet_RPGE));
    if (asset == NULL) {
        return NULL;
    }
    if (pathIMG == NULL || strlen(pathIMG) < 1) {
        log_error("create_Assetsheet_RPGE: pathIMG is invalid");
        errno = EINVAL;
        return NULL;
    }
    asset->pathIMG = (char*) malloc(sizeof(pathIMG));
    strncpy(asset->pathIMG, pathIMG, sizeof(asset->pathIMG));
    // load texture.    
    SDL_Texture *texture = IMG_LoadTexture(renderer, pathIMG);
    if(!texture) {
        log_error("%s", SDL_GetError());
        errno = ENOENT;
        return NULL;
    }
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung).
    if(!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        errno = ENOMSG;
        return NULL;
    }
    asset->imgText = texture;
    
    if (ID == NULL || strlen(ID) < 1) {
        log_error("create_Assetsheet_RPGE: ID is invalid");
        errno = EINVAL;
        return NULL;
    }
    asset->ID = (char*) malloc(sizeof(ID));
    strncpy(asset->ID, ID, sizeof(asset->ID));

    if (vTableSize.x == 0 || vTableSize.y == 0) {
        log_error("create_Assetsheet_RPGE: vTableSize is invalid");
        errno = EINVAL;
        return NULL;
    }
    asset->vTableSize = vTableSize;

    if (vPatchSize.x == 0 || vPatchSize.y == 0) {
        log_error("create_Assetsheet_RPGE: vPatchSize is invalid");
        errno = EINVAL;
        return NULL;
    }
    asset->vPatchSize = vPatchSize;
    return asset;
}

void destory_Assetsheet_G_RPGE(Assetsheet_RPGE* asset) {
    free(asset->ID);
    free(asset->pathIMG);
    free(asset->imgText);
    free(asset);
}
