#include "cJSON.h"
#include "RPGE_U_json.h"
#include "RPGE_U_files.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_DEC_assetsheet.h"

Assetsheet_RPGE* load_Assetsheet_JSON(const char* pathJSON) {
    struct Assetsheet_RPGE* assetsheet = malloc(sizeof(Assetsheet_RPGE));
    // load TextureAtlas from json.
    char* jsonString = readFile_UTIL(pathJSON);
    if (jsonString == NULL) return NULL;
    cJSON *assetsheet_JSON = cJSON_Parse(jsonString);
    free(jsonString);

    if(!isValueInvalidJSON_UTIL(assetsheet_JSON)) return NULL;
    
    const cJSON *ID = NULL;
    const cJSON *cols = NULL;
    const cJSON *rows = NULL;
    const cJSON *tileSizeX = NULL;
    const cJSON *tileSizeY= NULL;
    const cJSON *texturePath = NULL;
    const cJSON *textureType = NULL;
    
    // ID:
    ID = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "ID");
    if(!isValueInvalidJSON_UTIL(game, ID, "ID", pathJSON);
    isValueValidJSON_UTIL(game, ID, cJSON_IsString);
    strncpy(textureAtlas->ID, ID->valuestring, sizeof(textureAtlas->ID) - 1);
    textureAtlas->ID[sizeof(textureAtlas->ID) - 1] = '\0';
    
    texturePath = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "texturePath");
    validateValueConstJSON(game, texturePath, "texturePath", pathJSON);
    validateTypeValueJSON(game, texturePath, cJSON_IsString);
    strncpy(textureAtlas->textPath, texturePath->valuestring, sizeof(textureAtlas->textPath) - 1);
    textureAtlas->textPath[sizeof(textureAtlas->textPath) - 1] = '\0';
    
    textureType = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "textureType");
    validateValueConstJSON(game, textureType, "textureType", pathJSON);
    validateTypeValueJSON(game, textureType, cJSON_IsString);
    log_debug("TextureType: %s", textureType->valuestring);
    textureAtlas->textureType = toTextureType(game, textureType->valuestring);

    cols = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "cols");
    validateValueConstJSON(game, cols, "cols", pathJSON);
    textureAtlas->cols = cols->valueint;

    rows = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "rows");
    validateValueConstJSON(game, rows, "rows", pathJSON);
    textureAtlas->rows = rows->valueint;

    tileSizeX = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "tileSizeX");
    validateValueConstJSON(game, tileSizeX, "tileSizeX", pathJSON);
    textureAtlas->tileSizeX = tileSizeX->valueint;

    tileSizeY = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "tileSizeY");
    validateValueConstJSON(game, tileSizeY, "tileSizeY", pathJSON);
    textureAtlas->tileSizeY = tileSizeY->valueint;

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

