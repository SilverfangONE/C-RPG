#ifndef RPGE_O_NPC
#define RPGE_O_NPC

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"

typedef struct NPC_Obj_RPGE {
    Base_Obj_RPG base;
} NPC_Obj_RPGE;

// struct.
void destroy_NPC_Obj_RPGE(NPC_Obj_RPGE* npcObj);
void _destroy_NPC_Obj_RPGE(void* npcObj);

// lifecylce.
int update_NPC_Obj_RPGE(NPC_Obj_RPGE* npcObj);
int _update_NPC_Obj_RPGE(void* npcObj);
int render_NPC_Obj_RPGE(SDL_Renderer* renderer, NPC_Obj_RPGE* npcObj);
int _render_NPC_Obj_RPGE(SDL_Renderer* renderer, void* npcObj);

#endif