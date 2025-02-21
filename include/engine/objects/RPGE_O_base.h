#ifndef RPGE_O_BASE
#define RPGE_O_BASE

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include <stdbool.h>

typedef enum ObjType_RPGE {
    PLAYER_O_TYPE,
    NPC_O_TYPE,
    ITEM_O_TYPE
} ObjType_RPGE;

typedef struct Base_Obj_RPGE {
    bool show;
    Vec2D vCoordinates;
    Assetsheet_RPGE* asset;
} Base_Obj_RPG;

typedef struct Wrapper_Obj_RPGE {
    ObjType_RPGE type;
    void* obj;
    int (*fupdate)(void*);
    int (*frender)(SDL_Renderer*, void*);
    void (*fdestroy)(void*);
} Wrapper_Obj_RPGE;

Wrapper_Obj_RPGE* wrap_Obj_RPGE(void* obj, ObjType_RPGE type);
#endif