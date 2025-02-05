#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "log.h"
#include "hashmap.h"
#include "game_components.h"
#include "game_core.h"
#include "game_util.h"
#include "game_to_string.h"

// ---- CONSTANTS ----
const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int SNES_PIXEL_WIDTH = 256;
const int SNES_PIXEL_HEIGHT = 224;
const int TARGET_FPS = 60;
const char NAME_OF_GAME[40] = "C_RPG";

// ---- LOAD & DESTROY Game Components ----
void loadDisplay(GameState* game) 
{
    Display disp;
    disp.texture = SDL_CreateTexture(
        game->renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        SNES_PIXEL_WIDTH, 
        SNES_PIXEL_HEIGHT
    );
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(disp.texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    // scaling.
    disp.height = SNES_PIXEL_HEIGHT;
    disp.width = SNES_PIXEL_WIDTH;
    // quadrtic scale;
    int scaleXInt = WINDOW_WIDTH / SNES_PIXEL_WIDTH;
    int scaleYInt = WINDOW_HEIGHT / SNES_PIXEL_HEIGHT;
    if(scaleXInt < scaleYInt) {
        scaleYInt = scaleXInt;
    } else {
        scaleXInt = scaleYInt;
    }
    
    disp.scaleX = (float) scaleXInt;
    disp.scaleY = (float) scaleYInt;
    
    // placement from display in window
    SDL_FRect destR;
    destR.w = (float) disp.width * disp.scaleX;
    destR.h = (float) disp.height * disp.scaleY;
    destR.x = (float) (WINDOW_WIDTH - destR.w) / 2;
    destR.y = (float) (WINDOW_HEIGHT - destR.h) / 2;
    disp.destRect = destR;
    game->display=disp;
    printDisplay(&disp, LOG_TRACE);
}

void destroyDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

// TODO: später steht das alles in einer json datei. => dan nur pfad zur json datei und zur texture
TextureAtlas* loadTextureAtlasJSON(GameState* game, char* pathJSON) {
    struct TextureAtlas* textureAtlas = malloc(sizeof(struct TextureAtlas));
    // load TextureAtlas from json.
    char* jsonString = readFile(pathJSON);
    if (!jsonString) {
        log_error("JSON-Datei=%s konnte nicht gelesen werden!", pathJSON);
        exitGame(game);
    }
    cJSON *textureAtlasJSON = cJSON_Parse(jsonString);
    free(jsonString);
    validateValueJSON(game, textureAtlasJSON);
    
    const cJSON *ID = NULL;
    const cJSON *cols = NULL;
    const cJSON *rows = NULL;
    const cJSON *tileSizeX = NULL;
    const cJSON *tileSizeY= NULL;
    const cJSON *texturePath = NULL;
    const cJSON *textureType = NULL;
    
    ID = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "ID");
    validateValueConstJSON(game, ID, "ID", pathJSON);
    validateTypeValueJSON(game, ID, cJSON_IsString);
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

void destroyTextureAtlas(TextureAtlas* atlas) {
    SDL_DestroyTexture(atlas->texture);
    free(atlas);
}

struct Map* loadMap(
    GameState* game, 
    int cols, 
    int rows, 
    const cJSON* backgroundMap, 
    const cJSON* middelgroudMap, 
    const cJSON* spriteMap, 
    const cJSON* logicMap
) {
    struct Map* map = malloc(sizeof(struct Map));
    map->cols = cols;
    map->rows = rows;
    map->backgroundMap = createMatrixJSON(game, rows, cols, backgroundMap);
    map->middelgroudMap = createMatrixJSON(game, rows, cols, middelgroudMap);
    map->spriteMap = createMatrixJSON(game, rows, cols, spriteMap);
    map->logicMap = createMatrixJSON(game, rows, cols, logicMap);
    printMap(map, LOG_TRACE);
    return map;
}

struct Sub* loadSub(GameState* game, char* pathJSON) {
    struct Sub* sub = malloc(sizeof(struct Sub));
    
    char* jsonString = readFile(pathJSON);
    if (!jsonString) {
        log_error("JSON-Datei=%s konnte nicht gelesen werden!", pathJSON);
        exitGame(game);
    }
    cJSON *subJSON = cJSON_Parse(jsonString);
    free(jsonString);
    validateValueJSON(game, subJSON);
    
    const cJSON *subID = NULL;
    const cJSON *cols = NULL;
    const cJSON *rows = NULL;
    const cJSON *backgroundMap = NULL;
    const cJSON *middelgroudMap = NULL;
    const cJSON *spriteMap = NULL;
    const cJSON *logicMap = NULL;
    
    subID = cJSON_GetObjectItemCaseSensitive(subJSON, "subID");
    validateValueConstJSON(game, subID, "subID", pathJSON);
    cols = cJSON_GetObjectItemCaseSensitive(subJSON, "cols");
    validateValueConstJSON(game, cols, "cols", pathJSON);
    rows = cJSON_GetObjectItemCaseSensitive(subJSON, "rows");
    validateValueConstJSON(game, rows, "rows", pathJSON);
    
    // in LoadMap gets validated the json;
    backgroundMap = cJSON_GetObjectItemCaseSensitive(subJSON, "backgroundMap");
    validateValueConstJSON(game, backgroundMap, "backgroundMap", pathJSON);
    middelgroudMap = cJSON_GetObjectItemCaseSensitive(subJSON, "middelgroudMap");
    validateValueConstJSON(game, middelgroudMap, "middelgroudMap", pathJSON);
    spriteMap = cJSON_GetObjectItemCaseSensitive(subJSON, "spriteMap");
    validateValueConstJSON(game, spriteMap, "spriteMap", pathJSON);
    logicMap = cJSON_GetObjectItemCaseSensitive(subJSON, "logicMap");
    validateValueConstJSON(game, logicMap, "logicMap", pathJSON);
   
    strncpy(sub->ID, subID->valuestring, sizeof(sub->ID) - 1);
    sub->ID[sizeof(sub->ID) - 1] = '\0';

    sub->map = loadMap(
        game,
        cols->valueint, 
        rows->valueint, 
        backgroundMap, 
        middelgroudMap, 
        spriteMap, 
        logicMap
    );
    cJSON_Delete(subJSON);
    printSub(sub, LOG_TRACE);
    return sub;
}

void destroySub(struct Sub* sub) {
    destroyMap(sub->map);
    free(sub);
}

void destroyMap(struct Map* map) {
    free(map->backgroundMap);
    free(map->logicMap);
    free(map->middelgroudMap);
    free(map->spriteMap);
    free(map);
}

GameState* initGameState() {
    GameState* game = (GameState*)malloc(sizeof(GameState));
    // setup window and renderer context SDL3.
    if(!SDL_CreateWindowAndRenderer(
        NAME_OF_GAME,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        &game->window,
        &game->renderer
    )) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    // load game components.
    loadDisplay(game);
    initEnviromentStack(game);
    printGameState(game, LOG_TRACE);
    return game;
}

void destroyGameState(GameState* game) {
    destroyDisplay(&game->display);
    destroyEnviromentStack(&game->envStack);
    free(game);
}

void destroyUIElement(struct UIElement* uiEl) {
    // TODO
    free(uiEl);
}


struct Enviroment* loadEnviroment(GameState* game, char* pathJSON) {
    // create env from JSON.
    log_trace("Loading Enviroment from %s ...", pathJSON);
    struct Enviroment *env = malloc(sizeof(struct Enviroment));
    char* jsonString = readFile(pathJSON);
    if (!jsonString) {
        log_warn("JSON-Datei konnte nicht gelesen werden!");
        return NULL;
    }
    cJSON *envJSON = cJSON_Parse(jsonString);
    free(jsonString);
    if(envJSON == NULL) {
        log_warn("JSON File with path %s was not found!", pathJSON);
    }
    validateValueJSON(game, envJSON);
    const cJSON *ID = NULL;
    const cJSON *enableGlobalUI = NULL;
    const cJSON *tilesheetPath = NULL;
    const cJSON *spritesheetPath = NULL;
    const cJSON *subIDs = NULL;
    const cJSON *subID = NULL;
    const cJSON *initSubID = NULL;
    const cJSON *type = NULL;
    
    ID = cJSON_GetObjectItemCaseSensitive(envJSON, "ID");
    validateValueConstJSON(game, ID, "ID", pathJSON);
    validateTypeValueJSON(game, ID, cJSON_IsString);

    // ceck if gloable ui is not enabled.
    enableGlobalUI = cJSON_GetObjectItemCaseSensitive(envJSON, "enableGlobalUI");
    if(enableGlobalUI == NULL) {
        env->enableGlobalUI = true;
    } else {
        validateTypeValueJSON(game, enableGlobalUI, cJSON_IsBool);
        env->enableGlobalUI = cJSON_IsTrue(enableGlobalUI);
    }

    // TextureAtlas Paths.
    tilesheetPath = cJSON_GetObjectItemCaseSensitive(envJSON, "tilesheetPath");
    validateValueConstJSON(game, tilesheetPath, "tilesheetPath", pathJSON);
    validateTypeValueJSON(game, tilesheetPath, cJSON_IsString);

    spritesheetPath = cJSON_GetObjectItemCaseSensitive(envJSON, "spritesheetPath");
    validateValueConstJSON(game, tilesheetPath, "spritesheetPath", pathJSON);
    validateTypeValueJSON(game, tilesheetPath, cJSON_IsString);
    
    // switch case for enum
    type = cJSON_GetObjectItemCaseSensitive(envJSON, "type");
    validateValueConstJSON(game, type, "type", pathJSON);
    validateTypeValueJSON(game, type, cJSON_IsString);;
    env->type = toEnviromentType(game, type->valuestring);
    
    initSubID = cJSON_GetObjectItemCaseSensitive(envJSON, "initSubID");
    validateValueConstJSON(game, initSubID, "initSubID", pathJSON);
    validateTypeValueJSON(game, initSubID, cJSON_IsString);

    // Hash Map sub IDs
    struct hashmap *subRoomIDMap = hashmap_new(sizeof(struct SubRoomIDNode), 0, 0, 0, subRoomIDNode_hash, subRoomIDNode_compare, NULL, NULL);
    subIDs = cJSON_GetObjectItemCaseSensitive(envJSON, "subIDs");
    validateValueConstJSON(game, subIDs, "subIDs", pathJSON);
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, subIDs) {
        cJSON *idJSON = cJSON_GetObjectItemCaseSensitive(item, "ID");
        validateValueJSON(game, idJSON);
        cJSON *pathJSON = cJSON_GetObjectItemCaseSensitive(item, "path");
        validateValueJSON(game, pathJSON);
        struct SubRoomIDNode sub;
        sub.id = idJSON->valuestring;
        sub.path = pathJSON->valuestring;
        if(hashmap_set(subRoomIDMap, &sub) == NULL) {
            log_trace("Item was added to hashmap:\n{\n\tID=%s;\n\tpath=%s\n}", sub.id, sub.path);
        } else {
            log_warn("Item in hashmap was repaced:\n{\n\tID=%s;\n\tpath=%s\n}", sub.id, sub.path);
        }
    }    
    
    struct SubRoomIDNode searchKey;
    searchKey.id = initSubID->valuestring;
    const struct SubRoomIDNode* node = hashmap_get(subRoomIDMap, &searchKey);
    if(node == NULL) {
        log_error("'initSubIDs'(%s) path isn't present in subIDs!", initSubID->valuestring);
        exitGame(game);
    }
    // TODO
    strncpy(env->ID, ID->valuestring, sizeof(env->ID) - 1);
    env->ID[sizeof(env->ID) - 1] = '\0';
    env->sub = loadSub(game, node->path);
    env->subRoomIDMap = subRoomIDMap;
    env->tilesheet = loadTextureAtlasJSON(game, tilesheetPath->valuestring);
    env->spritesheet = loadTextureAtlasJSON(game, spritesheetPath->valuestring);
    env->isLocalUIActive = false;
    // deciedes EnvStack.
    env->toRender = true;

    // TODO UI for Envoiment not implemented.
    env->uiElementCount = 0;
    cJSON_Delete(envJSON);
    printEnviroment(env, LOG_DEBUG);
    return env;
}

void destroyEnviroment(struct Enviroment* env) {
    for(int i = 0; i < env->uiElementCount; i++) {
        struct UIElement *el = env->uiElements[i];
        destroyUIElement(env->uiElements[i]);
    }
    destroyTextureAtlas(env->spritesheet);
    destroyTextureAtlas(env->tilesheet);
    destroySub(env->sub);
    hashmap_free(env->subRoomIDMap);
    free(env);
}

struct EnviromentStackItem* createEnviromentStackItem(
    struct EnviromentStackItem* next,
    struct Enviroment* env
) {
    struct EnviromentStackItem *item = malloc(sizeof(struct EnviromentStackItem));   
    item->env = env;
    item->next = next;
    return item;
}

void destroyEnviromentStackItem(struct EnviromentStackItem* stackItem) {
    // pointer next won't be destoryed here.
    destroyEnviroment(stackItem->env);
    free(stackItem->env);
}

void initEnviromentStack(GameState* game) {
    game->envStack.size = 0;
    game->envStack.top = NULL;
    printEnviromentStack(&game->envStack, LOG_TRACE);
}

void destroyEnviromentStack(EnviromentStack* envStack) {
    struct EnviromentStackItem* item = envStack->top;
    while(item != NULL) {
        struct EnviromentStackItem* temp = item;
        item = item->next;
        destroyEnviromentStackItem(temp);
    }
    free(envStack);
}

// ---- Sub functions ----
int subRoomIDNode_compare(const void *a, const void *b, void *udata) {
    const struct SubRoomIDNode *sa = a;
    const struct SubRoomIDNode *sb = b;
    return strcmp(sa->id, sb->id);
}

bool subRoomIDNode_iter(const void *item, void *udata) {
    const struct SubRoomIDNode *subRoomIDNode = item;
    printf("%s (path=%s)\n", subRoomIDNode->id, subRoomIDNode->path);
    return true;
}

uint64_t subRoomIDNode_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const struct SubRoomIDNode *subRoomIDNode = item;
    return hashmap_sip(subRoomIDNode->id, strlen(subRoomIDNode->id), seed0, seed1);
}

// ---- EnviromentStack functions ----
void pushEnviroment(GameState* game, char* pathJSON) {    
    struct Enviroment* env = loadEnviroment(game, pathJSON);
    struct EnviromentStackItem* stackItem = createEnviromentStackItem(NULL, env);
    // push env to EnvStack.
    stackItem->next = game->envStack.top;
    game->envStack.top = stackItem;
    game->envStack.size++;
    updateToRenderFlagsFromStackEnvs(game->envStack.top);
    printEnviromentStack(&game->envStack, LOG_TRACE);
}

void popEnviroment(GameState* game) {
    struct EnviromentStackItem* stackItem = game->envStack.top;
    if(stackItem->next == NULL) {
        log_warn("\nLast Element from ENV-Stack was poped.\nGame will close now!");
        exitGame(game);
    }
    game->envStack.top = stackItem->next;  
    destroyEnviromentStackItem(stackItem);
    game->envStack.size--;
    updateToRenderFlagsFromStackEnvs(game->envStack.top);
    printEnviromentStack(&game->envStack, LOG_TRACE);
}

/**
 * Implements render hierary for EnviromentStack in terms of which envs get rendered.
 */
void updateToRenderFlagsFromStackEnvs(struct EnviromentStackItem* item) {
    if(item == NULL || item->next == NULL) {
        return;
    }
    setToRenderFlagFromLowerENV(item->env, item->next->env);
    return updateToRenderFlagsFromStackEnvs(item->next);
}

void setToRenderFlagFromLowerENV(struct Enviroment* top, struct Enviroment* next) {
    if(next != NULL) {
        if(top->toRender) {
            switch(top->type) {
                case ENV_MENU:
                    next->toRender = true;
                    return;
                case ENV_WORLD:
                    next->toRender = false;
                    return;
                case ENV_COMBAT:
                    next->toRender = false;
                    return;
            }
        } else {
            next->toRender = false;
        }
    }
}

// ---- Convert String to ENUM ----
enum EnviromentType toEnviromentType(GameState* game, char* string) {
    #ifdef _WIN32
        if(_stricmp("ENV_COMBAT", string) == 0) {
            log_trace("toEnviromentType: %s to ENV_COMBAT", string);
            return ENV_COMBAT;
        }
        if(_stricmp("ENV_WORLD", string) == 0) {
            log_trace("toEnviromentType: %s to ENV_WORLD", string);
            return ENV_WORLD;
        }
        if(_stricmp("ENV_MENU", string) == 0) {
            log_trace("toEnviromentType: %s to ENV_MENU", string);
            return ENV_MENU;
        }
    #elif defined(__linux__) || defined(__APPLE__)
        if(strcasecmp("ENV_COMBAT", string) == 0) {
            return ENV_COMBAT;
        }
        if(strcasecmp("ENV_WORLD", string) == 0 ) {
            return ENV_WORLD;
        }
        if(strcasecmp("ENV_MENU", string) == =) {
            return ENV_MENU;
        }
    #endif
    log_error("No EnviromentType matches with %s", string);
    exitGame(game);
}

enum TextureType toTextureType(GameState* game, char* string) {
    #ifdef _WIN32
        if(_stricmp("TEXT_STATIC", string) == 0) {
            log_trace("toTextureType: %s to TEXT_STATIC", string);     
            return TEXT_STATIC;
        }
        if(_stricmp("TEXT_ANIMATED", string) == 0) {
            log_trace("toTextureType: %s to TEXT_ANIMATED", string);     
            return TEXT_ANIMATED;
        }
    #elif defined(__linux__) || defined(__APPLE__)
        if(strcasecmp("TEXT_STATIC", string) == 0) {
            return TEXT_STATIC;
        }
        if(strcasecmp("TEXT_ANIMATED", string) == 0 ) {
            return TEXT_ANIMATED;
        }
    #endif
    log_error("No TextureType matches with %s", string);
    exitGame(game);
}
