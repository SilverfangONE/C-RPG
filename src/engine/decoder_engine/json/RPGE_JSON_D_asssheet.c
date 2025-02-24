#include "RPGE_G_assetsheet.h"
#include "RPGE_JSON_D_assetsheet.h"
#include "RPGE_U_files.h"
#include "RPGE_U_json.h"
#include "cJSON.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Assetsheet_RPGE *load_JSON_Assetsheet_G_RPGE(SDL_Renderer *renderer, const char *pathJSON)
{
    if (pathJSON == NULL)
    {
        log_error("load_JSON_Assetsheet_G_RPGE(): pathJSON is Invalid");
        errno = EINVAL;
        return NULL;
    }
    // load TextureAtlas from json.
    char *jsonString = readFile_UTIL(pathJSON);
    if (jsonString == NULL)
    {
        return NULL;
    }
    cJSON *assetsheet_JSON = cJSON_Parse(jsonString);
    free(jsonString);
    if (isValueInvalidJSON_UTIL(assetsheet_JSON))
        return NULL;

    const cJSON *ID_json = NULL;
    const cJSON *pathIMG_json = NULL;

    // ID:
    ID_json = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "ID");
    if (isValueInvalidJSON_UTIL(ID_json))
        return NULL;
    if (isValueTypeInvalidJSON_UTIL(ID_json, cJSON_IsString))
        return NULL;
    // pathIMG:
    pathIMG_json = cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "pathIMG");
    if (pathIMG_json == NULL)
    {
        log_warn("pathIMG_JSON is %s", pathIMG_json);
    }
    if (isValueInvalidJSON_UTIL(pathIMG_json))
        return NULL;
    if (isValueTypeInvalidJSON_UTIL(pathIMG_json, cJSON_IsString))
        return NULL;

    // vTableSize:
    Vec2D vTableSize = jsonToVec2D_UTIL_RPGE(cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vTableSize"));
    if (vTableSize.x == -1 || vTableSize.y == -1)
        return NULL;

    // vPatchSize:
    Vec2D vPatchSize = jsonToVec2D_UTIL_RPGE(cJSON_GetObjectItemCaseSensitive(assetsheet_JSON, "vPatchSize"));
    if (vPatchSize.x == -1 || vPatchSize.y == -1)
        return NULL;

    Assetsheet_RPGE *assetsheet_RPGE =
        create_Assetsheet_G_RPGE(renderer, vTableSize, vPatchSize, ID_json->valuestring, pathIMG_json->valuestring);
    cJSON_Delete(assetsheet_JSON);
    return assetsheet_RPGE;
}