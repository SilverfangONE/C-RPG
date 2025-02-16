#include "cJSON.h"
#include "RPGE_U_json.h"
#include "RPGE_U_files.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_DEC_assetsheet.h"

Assetsheet_RPGE* load_Assetsheet_JSON_RPGE(const char* pathJSON) {
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
    strncpy(assetsheet_JSON->ID, ID->valuestring, sizeof(assetsheet_JSON->ID) - 1);
    assetsheet->ID[sizeof(assetsheet_JSON->ID) - 1] = '\0';
    
    // pathIMG:
    pathIMG = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "pathIMG");
    if(isValueInvalidJSON_UTIL(pathIMG)) return NULL;
    if(isValueTypeInvalidJSON_UTIL(pathIMG, cJSON_IsString)) return NULL;
    strncpy(assetsheet_JSON->pathIMG, pathIMG->valuestring, sizeof(assetsheet_JSON->pathIMG) - 1);
    assetsheet->pathIMG[sizeof(assetsheet_JSON->pathIMG) - 1] = '\0';
    
    // vTableSize:
    Vec2D vTableSize = (cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vTableSize"));

    // vPatchSize:
    vPatchSize = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vPatchSize");
    if(isValueInvalidJSON_UTIL(pathIMG)) return NULL;
    if(isValueTypeInvalidJSON_UTIL(pathIMG, cJSON_IsString)) return NULL;
    strncpy(assetsheet_JSON->pathIMG, pathIMG->valuestring, sizeof(assetsheet_JSON->pathIMG) - 1);
    assetsheet->pathIMG[sizeof(assetsheet_JSON->pathIMG) - 1] = '\0';
   
    // load texture.    
    SDL_Texture *texture = IMG_LoadTexture(game->renderer, textureAtlas->textPath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }

    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }

    textureAtlas->texture = texture;
    cJSON_Delete(textureAtlasJSON);
    printTextureAtlas(textureAtlas, LOG_DEBUG);
    return textureAtlas;
}

