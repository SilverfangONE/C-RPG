#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "cJSON.h"
#include "RPGE_U_json.h"
#include "RPGE_U_files.h"
#include "RPGE_G_assetsheet.h"

Assetsheet_RPGE* load_Assetsheet_JSON_RPGE(SDL_Renderer* renderer, char* pathJSON) {
    struct Assetsheet_RPGE* assetsheet = malloc(sizeof(Assetsheet_RPGE));
    // load TextureAtlas from json.
    char* jsonString = readFile_UTIL(pathJSON);
    if (jsonString == NULL) return NULL;
    cJSON *assetsheet_JSON = cJSON_Parse(jsonString);
    free(jsonString);

    if(isValueInvalidJSON_UTIL(assetsheet_JSON)) return NULL;
    
    const cJSON *ID = NULL;
    const cJSON *pathIMG = NULL;
    const cJSON *vTableSize = NULL;
    const cJSON *vPatchSize = NULL;
    
    // ID:
    ID = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "ID");
    if(isValueInvalidJSON_UTIL(ID)) return NULL;
    if(isValueTypeInvalidJSON_UTIL(ID, cJSON_IsString)) return NULL;
    strncpy(assetsheet->ID, ID->valuestring, sizeof(assetsheet->ID) - 1);
    assetsheet->ID[sizeof(assetsheet->ID) - 1] = '\0';
    
    // pathIMG:
    pathIMG = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "pathIMG");
    if(isValueInvalidJSON_UTIL(pathIMG)) return NULL;
    if(isValueTypeInvalidJSON_UTIL(pathIMG, cJSON_IsString)) return NULL;
    strncpy(assetsheet->pathIMG, pathIMG->valuestring, sizeof(assetsheet->pathIMG) - 1);
    assetsheet->pathIMG[sizeof(assetsheet->pathIMG) - 1] = '\0';
    
    // load texture.    
    SDL_Texture *imgText = IMG_LoadTexture(renderer, assetsheet->pathIMG);
    if(!imgText) {
        log_error("%s", SDL_GetError());
        errno = ENOMSG;
        return NULL;
    }
    
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(imgText, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        errno = ENOMSG;
        return NULL;
    }
    
    // vTableSize:
    Vec2D vecSize = jsonToVec2D_UTIL_RPGE(cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vTableSize"));
    if (vecSize.x == -1 || vecSize.y == -1) return NULL;
    assetsheet->vTableSize = vecSize;

    // vPatchSize:
    Vec2D vPSize = jsonToVec2D_UTIL_RPGE(cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vPatchSize"));
    if (vPSize.x == -1 || vPSize.y == -1) return NULL;
    assetsheet->vPatchSize = vPSize;

    cJSON_Delete(assetsheet_JSON);
    return assetsheet;
}