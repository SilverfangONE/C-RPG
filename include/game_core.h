#ifndef GAME_CORE
#define GAME_CORE
#include "game_render.h"
#include "game_util.h"

typedef struct GameState {
    
} GameState;

struct Enviroment {
    // sub rooms[] oder sub jedes mal rein laden
    struct Sub* sub;   

    int sheetCount;
    int uiElsCount;
    struct Tilesheet tilesheet; // array of sheets
    struct Spritesheet spritesheet;
    struct UIElement* uiElements; // array of ui elements
};

struct Sub {
    struct Map* map;
};

struct Map {
    struct Matrix* backgroundMap;
    struct Matrix* middelgroudMap;
    struct Matrix* spriteMap;
    struct Matrix* logicMap; // player spawn point and exit 
};

struct ENVItem {
    struct Enviroment env;        
    struct ENVItem* next;
};

struct ENVStack {
    
};

void exitGame(GameState*);

#endif