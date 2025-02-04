// @author: SilverfangOne 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "game_core.h"
#include "game_render.h"
#include "game_util.h"
#include "log.h"
#include "cJSON.h"

// temp
int roomIDCounter = 0;

// ---- LOAD/DESTROY SYSTEMS ----
GameState* loadGame()
{
    GameState* game = (GameState*)malloc(sizeof(GameState));
    // set sets to NULL default
    for(int i = 0; i < TILESET_SLOT_SIZE; i++)
    {
        game->sets[i] = NULL;
    }
 
    log_info("LOAD: GAME");
    // setup SDL3.
    SDL_Init(SDL_INIT_VIDEO);
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
    log_debug("LOAD: GAME: init SDL3");
    // init game state.
    loadDisplay(game);
    loadTileset(game, "./res/tilesheets/tilesheet.8..png", 8, 8, 6, 6, 0);
    loadRoom(game, R_WORLD, 0, 0);
    log_debug("LOAD: GAME: init GameState");
    return game;
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


void exitGame(GameState* game)
{
    log_info("TERMINATE_GAME");
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    destoryGameState(game);
    exit(0);
}

void destoryGameState(GameState* game) {
    destoryRoom(&game->room);
    destoryDisplay(&game->display);
    // free SDL_Textures;
    for(int i = 0; i < TILESET_SLOT_SIZE; i++) {
        free(game->sets[i]);
    }
    free(game);
}

void destoryRoom(Room* room) {
    // NOTHING TO DESTROY YET.
}

// ---- GAME SYSTEM ----
void processEventsSDL(GameState* game) 
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                exitGame(game);
            }
            break;
            case SDL_EVENT_KEY_DOWN:
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    break;
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    break;
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    break;
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                }
            }
        }
    }
}

void updateGame(GameState* game) 
{
    // TODO
}

void loopGame(GameState* game)
{
    smokeTestIMGRender(game);
    // start.
    log_info("GAME_LOOP:START");
    int frameDelay = 1000000 / TARGET_FPS;
    int run = 1;
    while (run) {
        // double start = GetCurrentTime();
        processEventsSDL(game);
        updateGame(game);
        renderGame(game);
        // Sleep(start + frameDelay - GetCurrentTime());
    }
}

// ---- ENV SYSTEM ----
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

void destoryEnviroment(struct Enviroment* env) {
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

void destroySub(struct Sub* sub) {
    destoryMap(sub->map);
    
}

void destroyMap(struct Map* map) {
    destory
}

void pushEnviroment(GameState* game, char* pathJSON) {    
    // create env from JSON.
    struct Enviroment *env = malloc(sizeof(struct Enviroment));
    cJSON *envJSON = cJSON_Parse(pathJSON);
    if (envJSON == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        exitGame(game);
    }
    const cJSON *blockGlobalUI = NULL;
    const cJSON *tilesheetPath = NULL;
    const cJSON *subIDs = NULL;
    const cJSON *subID = NULL;
    const cJSON *initSub = NULL;
    const cJSON *type = NULL;

    blockGlobalUI = cJSON_GetObjectItemCaseSensitive(envJSON, "blockGlobalUI");
    tilesheetPath = cJSON_GetObjectItemCaseSensitive(envJSON, "tilesheetPath");
    type = cJSON_GetObjectItemCaseSensitive(envJSON, "type");
    initSub = cJSON_GetObjectItemCaseSensitive(envJSON, "initSub");
    
    // Hash Map sub IDs
    struct hashmap *subRoomIDMap = hashmap_new(sizeof(struct SubRoomIDNode), 0, 0, 0, subRoomIDNode_hash, subRoomIDNode_compare, NULL, NULL);
    subIDs = cJSON_GetObjectItemCaseSensitive(envJSON, "subIDs");

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, subIDs) {
        cJSON *idJSON = cJSON_GetObjectItemCaseSensitive(item, "ID");
        if(idJSON == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        }
        cJSON *pathJSON = cJSON_GetObjectItemCaseSensitive(item, "path");
        if(pathJSON == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        }
        struct SubRoomIDNode sub;
        sub.id = idJSON->string;
        sub.path = pathJSON->string;
        hashmap_set(subRoomIDMap, &sub);
    }    
    env->subRoomIDMap = subRoomIDMap;
    // push env to EnvStack.
    struct EnviromentStackItem* stackItem = createEnviromentStackItem(NULL, NULL, env);
    if(game->envStack.bottom != NULL & game->envStack.top != NULL) {
        item->next = game->envStack.top;
        game->envStack.top = stackItem;
    } else {
        game->envStack.top = stackItem;
        game->envStack.bottom = stackItem;
    }
    game->envStack.size++;
}

void popEnviroment(GameState* game) {
    struct EnviromentStackItem* stackItem = game->envStack.top;
    if(stackItem->next == NULL) {
        log_warn("\nLast Element from ENV-Stack was poped.\nGame will close now!");
        exitGame(game);
    }
    game->envStack.top = stackItem->next;
    game->envStack.top->prev = NULL;    
    destoryEnviroment(stackItem->env);
    free(stackItem->env);
    game->envStack.size--;
}

void initEnviromentStack(GameState* game) {
    game->envStack.size = 0;
    game->envStack.bottom = NULL;
    game->envStack.top = NULL;
}

struct EnviromentStackItem* createEnviromentStackItem(
    struct EnviromentStackItem* prev,  
    struct EnviromentStackItem* next,
    struct Enviroment* env
) {
    struct EnviromentStackItem *item = malloc(sizeof(struct EnviromentStackItem));   
    item->env = env;
    item->prev = prev;
    item->next = next;
    return item;
}

void validateValueJSON(GameState* game, cJSON* value) {
    if(value == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        exitGame(game);
    }
}

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

// ---- SMOKE-TESTS ----
void smokeTestIMGRender(GameState* game) {
    // test 
    SDL_Texture* img = IMG_LoadTexture(game->renderer, "./res/tilesheets/Studio_Logo.png");
    SDL_FRect texture_rect;
    texture_rect.x = 0; //the x coordinate
    texture_rect.y = 0; //the y coordinate
    texture_rect.w = NES_PIXEL_WIDTH; //the width of the texture
    texture_rect.h = NES_PIXEL_HEIGHT; //the height of the texture
    SDL_RenderClear(game->renderer); //clears the renderer
    SDL_RenderRect(game->renderer, &texture_rect);
    if(!SDL_RenderTexture(game->renderer, img, NULL, &texture_rect)) {
        log_error("%s", SDL_GetError());
    }
    SDL_RenderPresent(game->renderer); //updates the renderer
    Sleep(2000);
}