// https://www.youtube.com/watch?v=jde1Jq5dF0E&t=1359s
#ifndef GAME_MENU
#define GAME_MENU

#include "hashmap.h"
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

extern const int nPatch;

typedef struct Vec2D {
    int x;
    int y;
} Vec2D;

typedef struct MenuManager {

} MenuManager;

typedef struct MenuObject {
    char* sName;
    bool bEnable;
    int nID;
    int nTotalRows;
    int nTopVisibleRow;
    Vec2D vCellTable;
    Vec2D vCellSize;
    Vec2D vCellPadding;
    Vec2D vPatchSize;
    Vec2D vSizeInPatches;
    struct hashmap* items;
} MenuObject;

struct Node_mobj {
    char* key;
    MenuObject* value;
};

// MenuManger functioncs.
void Open_MM(MenuManager*);
void OnUp_MM(MenuManager*);
void OnDown_MM(MenuManager*);
void OnLeft_MM(MenuManager*);
void OnRight_MM(MenuManager*);
void OnBack_MM(MenuManager*);
void OnConfirm_MM(MenuManager*); // returns command.
void Draw_MM(MenuManager*);

// MenuObject
/**
 * MenuObject Konst.
 * def = 0: calls default create_mobj (void, 0);
 * else: creates mobj with (name, 1);
 */
MenuObject* create_mobj(char* name, int mod);
void destroy_mobj(MenuObject* mobj);
void DrawSelf_mobj(SDL_Renderer* renderer, SDL_Texture* menuTilesheet, MenuObject* mobj);
MenuObject* setTable_mobj(MenuObject* mobj, int nColumns, int nRows);
MenuObject* setID_mobj(MenuObject* mobj, int ID);
MenuObject* enable_mobj(MenuObject* mobj, bool b);
int getID_mobj(MenuObject* mobj);
char* getName_mobj(MenuObject* mobj);
Vec2D getSize_mobj(MenuObject* mobj);
bool hasChildren_mobj(MenuObject* mobj);
MenuObject* addChild_mobj(MenuObject* mobjP, MenuObject* mobjC);
MenuObject* accessChild_mobj(MenuObject* mobj, char* sName);
void Build_mobj(MenuObject* mobj);

#endif