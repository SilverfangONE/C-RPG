#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_O_base.h"
#include "RPGE_O_item.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// struct.
void destroy_Item_Obj_RPGE(Item_Obj_RPGE* itemObj)
{
    // TODO: impl
    return;
}

void _destroy_Item_Obj_RPGE(void* itemObj)
{
    // TODO: impl
    return;
}

// lifecycle.
int update_Item_Obj_RPGE(Item_Obj_RPGE* itemObj) {
    // TODO: impl
    return 0;
}

int _update_Item_Obj_RPGE(void* itemObj) {
    Item_Obj_RPGE* item = (Item_Obj_RPGE*) itemObj;
    update_Item_Obj_RPGE(item);
}

int render_Item_Obj_RPGE(SDL_Renderer* renderer, Item_Obj_RPGE* itemObj) {
    // TODO: impl
    return 0;
}

int _render_Item_Obj_RPGE(SDL_Renderer* renderer, void* itemObj) {
    Item_Obj_RPGE* item = (Item_Obj_RPGE*) itemObj;
    render_Item_Obj_RPGE(renderer, item);
}