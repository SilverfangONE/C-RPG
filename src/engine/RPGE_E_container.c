#include "RPGE_E_container.h"
#include "RPGE_C_combat.h"
#include "RPGE_C_menu.h"
#include "RPGE_C_room.h"
#include "RPGE_C_world.h"
#include <errno.h>
#include <stdlib.h>
#include "log.h"

static ContainerStack_RPGE* _CONTAINER_STACK;

bool _isContainerType_STACK_RPGE(ContainerType_RPGE type) {
    switch (type) 
    {
    case ROOM_CT_RPGE:
    case COMBAT_CT_RPGE:
    case WORLD_CT_RPGE: 
        return true;
    default:
        return false;
    }
}

// destroy.
static void _destroy_ContainerItem(ContainerItem_RPGE* conItem) {
    free(conItem->containerWrapper);
    free(conItem);
}

int _check_CONTAINER_STACK() {
    if (_CONTAINER_STACK == NULL)
    {
        log_error("push_Container_RPGE(): _CONTAINER_STACK {NULL} hasn't been set yet");
        errno = EPERM;
        return 1;
    }
    return 0;
}

int set_CONTAINER_STACK_RPGE(ContainerStack_RPGE* stack) 
{
    if (stack == NULL) {
        log_error("set_ContainerStack_RPGE(): stack is NULL");
        errno = EINVAL;
        return 1;
    }
    _CONTAINER_STACK = stack;
    return 0;
}

ContainerItem_RPGE* _create_CONTAINER_WRAPPER(bool prio, void* container, enum ContainerType_RPGE type) 
{
    ContainerWrapper_RPGE* cw = malloc(sizeof(ContainerWrapper_RPGE));
    // validate values.
    if (cw == NULL) return NULL;
    if (!_isContainerType_STACK_RPGE(type)) 
    {
        log_error("_create_CONTAINER_WRAPPER(): type {%d} is undefined");
        errno = EINVAL;
        return NULL;
    }
    if (container == NULL)
    {
        log_error("_create_CONTAINER_WRAPPER(): container is NULL");
        errno = EINVAL;
        return NULL;
    }
    // set values.
    // dispatch neccessary functions to wrapper.
    switch (type) 
    {
    case ROOM_CT_RPGE:
        cw->fupdate = &_update_Room_C_RPGE;
        cw->fupdate = &_update_Room_C_RPGE;
        cw->fdestroy = &_destroy_Room_C_RPGE;
        break;
    case COMBAT_CT_RPGE:
        cw->fupdate = &_update_Combat_C_RPGE;
        cw->frender = &_render_Combat_C_REPGE;
        cw->fdestroy = &_destroy_Combat_C_RPGE;
        break;
    case WORLD_CT_RPGE:
        cw->fupdate = &_update_Room_C_RPGE;
        cw->frender = &_render_World_C_RPGE;
        cw->fdestroy = &_destroy_World_C_RPGE;
        break;
    case MENU_CT_RPGE:
        cw->fupdate = &_update_Menu_C_RPGE;
        cw->frender = &_render_Menu_C_RPGE;
        cw->fdestroy = &_destroy_Menu_C_RPGE;
        break;
    // code dupplication:
    default:
        log_error("_create_CONTAINER_WRAPPER(): type {%d} is undefined");
        errno = EINVAL;
        return NULL;
    }

    cw->prio = prio;
    cw->type = type;
    cw->container = container;
    return cw;
}

int push_CONTAINER_STACK_RPGE(
    bool prio, 
    void* container, 
    enum ContainerType_RPGE type
)
{
    // check if stack exists.
    if(_check_CONTAINER_STACK()) return 1;
    ContainerItem_RPGE* conItem = malloc(sizeof(ContainerItem_RPGE));
    if (conItem == NULL) return 1;
    conItem->containerWrapper = _create_CONTAINER_ITEM(prio, container, type);
    if (conItem->containerWrapper == NULL) return 1;
    // push to stack.
    conItem->next = _CONTAINER_STACK->top;
    _CONTAINER_STACK->top = conItem;
    _CONTAINER_STACK->length++;
    return 0;
}

int pop_CONTAINER_STACK_RPGE() 
{
    if (_CONTAINER_STACK < 1) return 1;
    
    ContainerItem_RPGE* conItem = _CONTAINER_STACK->top;
    _CONTAINER_STACK->top = _CONTAINER_STACK->top->next;
    _destroy_ContainerItem(conItem);
    _CONTAINER_STACK->length--;
    return 0;
}

/**
 * render from buttom to top recursive.
 */
static int _render_CONTAINER_STACK(SDL_Renderer* renderer, ContainerItem_RPGE* conItem) 
{
    // render from buttom to top.
    if (conItem->next != NULL) 
    {
        return _render_CONTAINER_STACK(renderer, conItem->next);
    }
    if (_toRender_CONTAINER_STACK_RPGE(conItem->containerWrapper->type))
    return conItem->containerWrapper->frender(renderer, conItem->containerWrapper);
}

int render_CONTAINER_STACK_RPGE(SDL_Renderer* renderer) 
{
    // render from buttom to top.
    if(_check_CONTAINER_STACK()) return 1;
    if (_CONTAINER_STACK->length < 1) {
        // nothing to render.
        return 0;
    }
    return _render_CONTAINER_STACK(renderer, _CONTAINER_STACK->top);
}

static int _update_CONTAINER_STACK(ContainerItem_RPGE* conItem) 
{
    // update from top to buttom.
    // only top containerWrapper gets updated, except for prio containerWrapper.
    
    conItem->containerWrapper->fupdate(conItem->containerWrapper);
    
}

int update_CONTAINER_STACK_RPGE() {
    // update from top to buttom.
    if(_check_CONTAINER_STACK()) return 1;
    if (_CONTAINER_STACK->length < 1) {
        // nothing to update.
        return 0;
    }
    return _render_CONTAINER_STACK(_CONTAINER_STACK->top);
}

