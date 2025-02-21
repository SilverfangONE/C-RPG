#ifndef RPEG_O_ITEM
#define RPEG_O_ITEM

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"

typedef struct Item_Obj_RPGE {
    Base_Obj_RPG base;
} Item_Obj_RPGE;

// struct.
void destroy_Item_Obj_RPGE(Item_Obj_RPGE* itemObj);
void _destroy_Item_Obj_RPGE(void* itemObj);

// lifecylce.
int update_Item_Obj_RPGE(Item_Obj_RPGE* itemObj);
int _update_Item_Obj_RPGE(void* itemObj);
int render_Item_Obj_RPGE(SDL_Renderer* renderer, Item_Obj_RPGE* itemObj);
int _render_Item_Obj_RPGE(SDL_Renderer* renderer, void* itemObj);


#endif