#ifndef RPGE_O_PLAYER
#define RPGE_O_PLAYER

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"

typedef struct Player_Obj_RPGE {
    Base_Obj_RPG base;
} Player_Obj_RPGE;

// struct.
void destroy_Player_Obj_RPGE(Player_Obj_RPGE* playerObj);
void _destroy_Player_Obj_RPGE(void* playerObj);

// lifecylce.
int update_Player_Obj_RPGE(Player_Obj_RPGE* playerObj);
int _update_Player_Obj_RPGE(void* playerObj);
int render_Player_Obj_RPGE(SDL_Renderer* renderer, Player_Obj_RPGE* playerObj);
int _render_Player_Obj_RPGE(SDL_Renderer* renderer, void* playerObj);

#endif