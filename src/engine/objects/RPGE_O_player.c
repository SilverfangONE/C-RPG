#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"
#include "RPGE_O_player.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// struct.
void destroy_Player_Obj_RPGE(Player_Obj_RPGE* playerObj)
{
    // TODO: impl
    return;
}

void _destroy_Player_Obj_RPGE(void* playerObj)
{
    // TODO: impl
    return;
}

// lifecycle.
int update_Player_Obj_RPGE(Player_Obj_RPGE* playerObj) {
    // TODO: impl
    return 0;
}

int _update_Player_Obj_RPGE(void* playerObj) {
    Player_Obj_RPGE* player = (Player_Obj_RPGE*) playerObj;
    update_Player_Obj_RPGE(player);
}

int render_Player_Obj_RPGE(SDL_Renderer* renderer, Player_Obj_RPGE* playerObj) {
    // TODO: impl
    return 0;
}

int _render_Player_Obj_RPGE(SDL_Renderer* renderer, void* playerObj) {
    Player_Obj_RPGE* player = (Player_Obj_RPGE*) playerObj;
    render_Player_Obj_RPGE(renderer, player);
}