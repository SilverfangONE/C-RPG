#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "log.h"
#include "hashmap.h"
#include "game_components.h"
#include "game_core.h"
#include "game_util.h"


// ---- CONSTANTS ----
const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int NES_PIXEL_WIDTH = 256;
const int NES_PIXEL_HEIGHT = 240;
const int TILE_PIXEL_SIZE_B = 16;
const int TILE_PIXEL_SIZE_S = 8;
const int TARGET_FPS = 60;
const int TILES_X = 6;
const int TILES_Y = 6;
const int TILE_COUNT = 6 * 6;
const int TILE_SIZE = 8;
const int TILESET_SLOT_SIZE = 6;

// ---- PRINT STRUCTS ----
void printTextureAtlas(TextureAtlas* textureAtlas) {
    log_debug("\nTILESET:\n{\n\tID=%s;\n\ttextPath=%s;\n\tcols=%d;\n\trows=%d\n}", 
        textureAtlas->ID,
        textureAtlas->textPath,
        textureAtlas->cols,
        textureAtlas->rows    
    );
}

void printDisplay(Display* disp) {
    log_debug("\nDISPLAY:\n{\n\twidth=%d;\n\theight=%d;\n\tscaleX=%f;\n\tscaleY=%f;\n\tx=%f;\n\ty=%f\n}",
        disp->width, 
        disp->height, 
        disp->scaleX, 
        disp->scaleY,
        disp->destRect.x,
        disp->destRect.y
    );
}

void printGameState(GameState* game) {
    log_debug("\nGAME_STATE:\n{");
    printDisplay(&game->display);
    log_debug("}");
}

// ---- LOAD & DESTROY Game Components ----
void loadDisplay(GameState* game) 
{
    Display disp;
    disp.texture = SDL_CreateTexture(
        game->renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        NES_PIXEL_WIDTH, 
        NES_PIXEL_HEIGHT
    );
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(disp.texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    // scaling.
    disp.height = NES_PIXEL_HEIGHT;
    disp.width = NES_PIXEL_WIDTH;
    // quadrtic scale;
    int scaleXInt = WINDOW_WIDTH / NES_PIXEL_WIDTH;
    int scaleYInt = WINDOW_HEIGHT / NES_PIXEL_HEIGHT;
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
    printDisplay(&disp);
}

void destroyDisplay(Display* display) {
    SDL_DestroyTexture(display->texture);
}

// TODO: später steht das alles in einer json datei. => dan nur pfad zur json datei und zur texture
TextureAtlas* loadTextureAtlasJSON(GameState* game, char* pathJSON) {
    struct TextureAtlas* textureAtlas = malloc(sizeof(struct TextureAtlas));
    // load TextureAtlas from json.
    cJSON *textureAtlasJSON = cJSON_Parse(pathJSON);
    validateValueJSON(game, textureAtlasJSON);
    
    const cJSON *ID = NULL;
    const cJSON *cols = NULL;
    const cJSON *rows = NULL;
    const cJSON *tileSizeX = NULL;
    const cJSON *tileSizeY= NULL;
    const cJSON *texturePath = NULL;
    const cJSON *textureType = NULL;
    
    ID = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "ID");
    validateValueConstJSON(game, ID);
    validateTypeValueJSON(game, ID, cJSON_IsString);
    strncpy(textureAtlas->ID, ID->string, sizeof(textureAtlas->ID - 1));
    textureAtlas->ID[sizeof(textureAtlas->ID) - 1] = '\0';
    
    texturePath = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "texturePath");
    validateValueConstJSON(game, texturePath);
    validateTypeValueJSON(game, texturePath, cJSON_IsString);
    strncpy(textureAtlas->textPath, texturePath->string, sizeof(textureAtlas->textPath - 1));
    textureAtlas->textPath[sizeof(textureAtlas->textPath) - 1] = '\0';
    
    textureType = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "textureType");
    validateValueConstJSON(game, textureType);
    validateTypeValueJSON(game, textureType, cJSON_IsString);
    textureAtlas->textureType = toTextureType(game, textureType->string);

    cols = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "cols");
    validateValueConstJSON(game, cols);
    textureAtlas->cols = cols->valueint;

    rows = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "rows");
    validateValueConstJSON(game, rows);
    textureAtlas->rows = rows->valueint;

    tileSizeX = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "tileSizeX");
    validateValueConstJSON(game, tileSizeX);
    textureAtlas->tileSizeX = rows->valueint;

    tileSizeY = cJSON_GetObjectItemCaseSensitive(textureAtlasJSON, "tileSizeY");
    validateValueConstJSON(game, tileSizeY);
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

    cJSON_Delete(textureAtlasJSON);
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
    return map;
}

struct Sub* loadSub(GameState* game, char* pathJSON) {
    struct Sub* sub = malloc(sizeof(struct Sub));
    
    char* jsonString = readFile(pathJSON);
    if (!jsonString) {
        log_warn("JSON-Datei konnte nicht gelesen werden!");
        return NULL;
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
    validateValueConstJSON(game, subID);
    cols = cJSON_GetObjectItemCaseSensitive(subJSON, "cols");
    validateValueConstJSON(game, cols);
    rows = cJSON_GetObjectItemCaseSensitive(subJSON, "rows");
    validateValueConstJSON(game, rows);
    
    // in LoadMap gets validated the json;
    backgroundMap = cJSON_GetObjectItemCaseSensitive(subJSON, "backgroundMap");
    middelgroudMap = cJSON_GetObjectItemCaseSensitive(subJSON, "middelgroudMap");
    spriteMap = cJSON_GetObjectItemCaseSensitive(subJSON, "spriteMap");
    logicMap = cJSON_GetObjectItemCaseSensitive(subJSON, "logicMap");
   
    strncpy(sub->ID, subID->string, sizeof(sub->ID - 1));
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
        "C-RPG",
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
    const cJSON *enableGlobalUI = NULL;
    const cJSON *tilesheetPath = NULL;
    const cJSON *spritesheetPath = NULL;
    const cJSON *subIDs = NULL;
    const cJSON *subID = NULL;
    const cJSON *initSub = NULL;
    const cJSON *type = NULL;
    
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
    validateValueConstJSON(game, tilesheetPath);
    validateTypeValueJSON(game, tilesheetPath, cJSON_IsString);

    spritesheetPath = cJSON_GetObjectItemCaseSensitive(envJSON, "spritesheetPath");
    validateValueConstJSON(game, tilesheetPath);
    validateTypeValueJSON(game, tilesheetPath, cJSON_IsString);
    
    // switch case for enum
    type = cJSON_GetObjectItemCaseSensitive(envJSON, "type");
    validateValueConstJSON(game, type);
    validateTypeValueJSON(game, type, cJSON_IsString);;
    env->type = toEnviromentType(game, type->valuestring);
    
    initSub = cJSON_GetObjectItemCaseSensitive(envJSON, "initSub");
    validateValueConstJSON(game, initSub);
    validateTypeValueJSON(game, initSub, cJSON_IsString);

    // Hash Map sub IDs
    struct hashmap *subRoomIDMap = hashmap_new(sizeof(struct SubRoomIDNode), 0, 0, 0, subRoomIDNode_hash, subRoomIDNode_compare, NULL, NULL);
    subIDs = cJSON_GetObjectItemCaseSensitive(envJSON, "subIDs");
    validateValueConstJSON(game, subIDs);
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, subIDs) {
        cJSON *idJSON = cJSON_GetObjectItemCaseSensitive(item, "ID");
        validateValueJSON(game, idJSON);
        cJSON *pathJSON = cJSON_GetObjectItemCaseSensitive(item, "path");
        validateValueJSON(game, pathJSON);
        struct SubRoomIDNode sub;
        sub.id = idJSON->string;
        sub.path = pathJSON->string;
        hashmap_set(subRoomIDMap, &sub);
    }    
    
    struct SubRoomIDNode searchKey;
    searchKey.id = initSub->string;
    const struct SubRoomIDNode* node = hashmap_get(subRoomIDMap, &searchKey);
    if(node == NULL) {
        log_error("'initSubIDs' path isn't present in subIDs!");
        exitGame(game);
    }
    env->sub = loadSub(game, node->path);
    env->subRoomIDMap = subRoomIDMap;
    env->tilesheet = loadTextureAtlasJSON(game, tilesheetPath->string);
    env->spritesheet = loadTextureAtlasJSON(game, spritesheetPath->string);
    env->isLocalUIActive = false;
    // deciedes EnvStack.
    env->toRender = false;

    // TODO UI for Envoiment not implemented.
    env->uiElementCount = 0;
    cJSON_Delete(envJSON);
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
    setToRenderFlagFromLowerENV(env, game->envStack.top->env);
    stackItem->next = game->envStack.top;
    game->envStack.top = stackItem;
    game->envStack.size++;
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
            return ENV_COMBAT;
        }
        if(_stricmp("ENV_WORLD", string) == 0) {
            return ENV_WORLD;
        }
        if(_stricmp("ENV_MENU", string) == 0) {
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
            return TEXT_STATIC;
        }
        if(_stricmp("TEXT_ANIMATED", string) == 0) {
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
