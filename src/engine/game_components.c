#include <stdlib.h>
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
void printTileset(Tileset* tileset) {
    log_debug("\nTILESET:\n{\n\tID=%u;\n\ttextPath=%s;\n\tcols=%d;\n\trows=%d\n}", 
        tileset->ID,
        tileset->textPath,
        tileset->cols,
        tileset->rows    
    );
}

void printRoom(Room* room) {
    log_debug("\nROOM:\n{\n\tID=%u;\n\ttype=%s;",
        room->ID,
        printRoomType(room->type)
    );
    printTileset(room->tileset);
    log_debug("}");
}

char* printRoomType(enum RoomType type) {
    switch(type) {
        case R_MENU: return "MENU";
        case R_WORLD: return "WORLD";
        case R_COMBAT: return "COMBAT";
        default: return "Unkowne";
    }
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
    printRoom(&game->room);
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
void loadTileset(GameState* game, char* tilesetTexturePath, int tileSizeX, int tileSizeY, int cols, int rows, unsigned int ID) {
    Tileset** slotPtr = getTilesetSaveSlot(game);
    if(slotPtr == NULL) {  
        log_error("GAME_STATE: Can't load new TILESET:{path=%s;ID=%u}, because no slot is free!", tilesetTexturePath, ID);
    }   
    Tileset* tileset = (Tileset*)malloc(sizeof(Tileset));
    tileset->ID = ID;
    SDL_Texture *texture = IMG_LoadTexture(game->renderer, tilesetTexturePath);
    if(!texture) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    tileset->texture = texture;
    tileset->cols = cols;
    tileset->rows = rows;
    tileset->tileSizeX = tileSizeX;
    tileset->tileSizeY = tileSizeY;
    strncpy(tileset->textPath, tilesetTexturePath, sizeof(tileset->textPath) - 1);
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if(!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)) {
        log_error("%s", SDL_GetError());
        exitGame(game);
    }
    *slotPtr = tileset;
}

struct Map* loadMap(GameState* game, int cols, int rows, cJSON* backgroundMap, cJSON* middelgroudMap, cJSON* spriteMap, cJSON* logicMap) {
    struct Map* map = malloc(sizeof(struct Map));
    map->cols = cols;
    map->rows = rows;
    map->backgroundMap = createMatrixJSON(game, rows, cols, backgroundMap);
    map->middelgroudMap = createMatrixJSON(game, rows, cols, middelgroudMap);
    map->spriteMap = createMatrixJSON(game, rows, cols, spriteMap);
    map->logicMap = createMatrixJSON(game, rows, cols, logicMap);
    return map;
}

struct Sub* loadSub(const GameState* game, const cJSON* pathJSON) {
    struct Sub* sub = malloc(sizeof(struct Sub));
    cJSON *subJSON = cJSON_Parse(pathJSON);
    validateValueJSON(game, subJSON);
    
    const cJSON *subID = NULL;
    const cJSON *cols = NULL;
    const cJSON *rows = NULL;
    const cJSON *backgroundMap = NULL;
    const cJSON *middelgroudMap = NULL;
    const cJSON *spriteMap = NULL;
    const cJSON *logicMap = NULL;
    
    subID = cJSON_GetObjectItemCaseSensitive(subJSON, "subID");
    validateValueJSON(game, subID);
    cols = cJSON_GetObjectItemCaseSensitive(subJSON, "cols");
    validateValueJSON(game, cols);
    rows = cJSON_GetObjectItemCaseSensitive(subJSON, "rows");
    validateValueJSON(game, rows);
    
    // in LoadMap gets validated the json;
    backgroundMap = cJSON_GetObjectItemCaseSensitive(subJSON, "backgroundMap");
    middelgroudMap = cJSON_GetObjectItemCaseSensitive(subJSON, "middelgroudMap");
    spriteMap = cJSON_GetObjectItemCaseSensitive(subJSON, "spriteMap");
    logicMap = cJSON_GetObjectItemCaseSensitive(subJSON, "logicMap");
   
    sub->ID = subID->string;
    sub->map = loadMap(
        game,
        cols->valueint, 
        rows->valueint, 
        backgroundMap, 
        middelgroudMap, 
        spriteMap, 
        logicMap
    );
    return sub;
}

void destroySub(struct Sub* sub) {
    destoryMap(sub->map);
    free(sub);
}

void destroyMap(struct Map* map) {
    free(map->backgroundMap);
    free(map->logicMap);
    free(map->middelgroudMap);
    free(map->spriteMap);
    free(map);
}

void destroyGameState(GameState* game) {
    destoryRoom(&game->room);
    destoryDisplay(&game->display);
    // free SDL_Textures;
    for(int i = 0; i < TILESET_SLOT_SIZE; i++) {
        free(game->sets[i]);
    }
    destroyEnviromentStack(game);
    free(game);
}


void destroyRoom(Room* room) {
    // NOTHING TO DESTROY YET.
}

void loadRoom(GameState* game, enum RoomType type, unsigned int roomID, unsigned int tilesetID)
{
    Room room;
    room.ID = roomID;
    room.type = type;
    room.tileset = lookupTileset(game, tilesetID);
    game->room=room;
    printRoom(&room);
}


void destroyUIElement(struct UIElement* uiEl) {
    // TODO
    free(uiEl);
}


struct Enviroment* loadEnviroment(GameState* game, char* pathJSON) {
 // create env from JSON.
    struct Enviroment *env = malloc(sizeof(struct Enviroment));
    cJSON *envJSON = cJSON_Parse(pathJSON);
    validateValueJSON(game, envJSON);
    const cJSON *blockGlobalUI = NULL;
    const cJSON *tilesheetPath = NULL;
    const cJSON *subIDs = NULL;
    const cJSON *subID = NULL;
    const cJSON *initSub = NULL;
    const cJSON *type = NULL;

    blockGlobalUI = cJSON_GetObjectItemCaseSensitive(envJSON, "blockGlobalUI");
    validateValueJSON(game, blockGlobalUI);
    tilesheetPath = cJSON_GetObjectItemCaseSensitive(envJSON, "tilesheetPath");
    validateValueJSON(game, tilesheetPath);
    type = cJSON_GetObjectItemCaseSensitive(envJSON, "type");
    validateValueJSON(game, type);
    initSub = cJSON_GetObjectItemCaseSensitive(envJSON, "initSub");
    validateValueJSON(game, initSub);

    // Hash Map sub IDs
    struct hashmap *subRoomIDMap = hashmap_new(sizeof(struct SubRoomIDNode), 0, 0, 0, subRoomIDNode_hash, subRoomIDNode_compare, NULL, NULL);
    subIDs = cJSON_GetObjectItemCaseSensitive(envJSON, "subIDs");
    validateValueJSON(game, subIDs);
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
    
    struct SubRoomIDNode* node = hashmap_get(subRoomIDMap, &(struct SubRoomIDNode){.id=initSub->string});
    if(node == NULL) {
        log_error("'initSubIDs' path isn't present in subIDs!");
        exitGame(game);
    }
    env->sub = loadSub(game, node->path);
    env->subRoomIDMap = subRoomIDMap;
    // TODO. SUB 
    return env;
}

void destroyEnviroment(struct Enviroment* env) {
    for(int i = 0; i < env->uiElsCount; i++) {
        struct UIElement *el = env->uiElements[i];
        destroyUIElement(env->uiElements[i]);
    }
    destroyTilesheet(env->tilesheet);
    destroySpritesheet(env->spritesheet);
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
    destoryEnviroment(stackItem->env);
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
    struct EnviromentStackItem* stackItem = createEnviromentStackItem(NULL, NULL, env);
    // push env to EnvStack.
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
}
