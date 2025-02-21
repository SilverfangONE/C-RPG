#include "RPGE_O_base.h"
#include "RPGE_O_player.h"
#include "RPGE_O_item.h"
#include "RPGE_O_npc.h"
#include <stdlib.h>
#include "log.h"
#include <errno.h>

Wrapper_Obj_RPGE* wrap_Obj_RPGE(void* obj, ObjType_RPGE type) {
    Wrapper_Obj_RPGE* wrapper = (Wrapper_Obj_RPGE*)malloc(sizeof(Wrapper_Obj_RPGE));
    if (wrapper == NULL) return NULL;
    if (obj == NULL)
    {
        log_error("wrap_Obj_RPGE(): obj is NULL");
        errno = EINVAL;
        return NULL;
    }
    // set values.
    wrapper->obj = obj;
    wrapper->type = type;

    // dispatch.
    switch (type)
    {
    case PLAYER_O_TYPE:
        wrapper->fupdate = &_update_Player_Obj_RPGE;
        wrapper->frender = &_render_Player_Obj_RPGE;
        wrapper->fdestroy = &_destroy_Player_Obj_RPGE;
        break;
    case NPC_O_TYPE:
        wrapper->fupdate = &_update_NPC_Obj_RPGE;
        wrapper->frender = &_render_NPC_Obj_RPGE;
        wrapper->fdestroy = &_destroy_NPC_Obj_RPGE;
        break;
    case ITEM_O_TYPE:
        wrapper->fupdate = &_update_Item_Obj_RPGE;
        wrapper->frender = &_render_Item_Obj_RPGE;
        wrapper->fdestroy = &_destroy_Item_Obj_RPGE;
        break;
    default:
        log_error("wrap_Obj_RPGE(): type {%d} is invalid", type);
        errno = EINVAL;
        return NULL;
    }
    log_trace("[Created Wrapper_Obj_RPGE {.type=%d}]", wrapper->obj);
    return wrapper;
}