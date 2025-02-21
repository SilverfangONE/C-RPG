#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"
#include "RPGE_O_npc.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// struct.
void destroy_NPC_Obj_RPGE(NPC_Obj_RPGE* npcObj)
{
    // TODO: impl
    return;
}

void _destroy_NPC_Obj_RPGE(void* npcObj)
{
    // TODO: impl
    return;
}

// lifecycle.
int update_NPC_Obj_RPGE(NPC_Obj_RPGE* npcObj) {
    // TODO: impl
    return 0;
}

int _update_NPC_Obj_RPGE(void* npcObj) {
    NPC_Obj_RPGE* npc = (NPC_Obj_RPGE*) npcObj;
    update_NPC_Obj_RPGE(npc);
}

int render_NPC_Obj_RPGE(SDL_Renderer* renderer, NPC_Obj_RPGE* npcObj) {
    // TODO: impl
    return 0;
}

int _render_NPC_Obj_RPGE(SDL_Renderer* renderer, void* npcObj) {
    NPC_Obj_RPGE* npc = (NPC_Obj_RPGE*) npcObj;
    render_NPC_Obj_RPGE(renderer, npc);
}