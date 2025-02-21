#include "RPGE_E_container.h"
#include "RPGE_C_combat.h"
#include "RPGE_C_menu.h"
#include "RPGE_C_room.h"
#include "RPGE_C_world.h"
#include "log.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

static ContainerStack_RPGE *_CONTAINER_STACK;

ContainerStack_RPGE* INIT_CONTAINER_STACK_RPGE()
{
    _CONTAINER_STACK = (ContainerStack_RPGE*) malloc(sizeof(ContainerStack_RPGE));
    if (_CONTAINER_STACK == NULL) return NULL;
    _CONTAINER_STACK->top = NULL;
    _CONTAINER_STACK->length = 0;
    log_trace("[Created _CONTAINER_STACK {length=%d}]", _CONTAINER_STACK->length);
    return _CONTAINER_STACK;
}

void QUIT_CONTAINER_STACK_RPGE() 
{
    if (_CONTAINER_STACK == NULL) return;
    log_trace("[Destroy _CONTAINER_STACK {length=%d}]", _CONTAINER_STACK->length);
    
    // free all elements in stack.
    ContainerItem_RPGE* item = _CONTAINER_STACK->top;
    while(item != NULL) {
        ContainerItem_RPGE* temp = item->next;
        destroy_ContainerItem_RPGE(item);
        item = temp;
    }
    free(_CONTAINER_STACK);
}

bool _isContainerType_STACK_RPGE(ContainerType_RPGE type)
{
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
void destroy_ContainerItem_RPGE(ContainerItem_RPGE *item)
{
    item->cw->fdestroy(item->cw->container);
    free(item->cw);
    free(item);
}

int _check_CONTAINER_STACK_RPGE()
{
    if (_CONTAINER_STACK == NULL)
    {
        log_error("_check_CONTAINER_STACK_RPGE(): _CONTAINER_STACK {NULL} hasn't been set yet");
        errno = EPERM;
        return 1;
    }
    return 0;
}

ContainerWrapper_RPGE* _create_CONTAINER_WRAPPER_RPGE(void *container, enum ContainerType_RPGE type)
{
    ContainerWrapper_RPGE *cw = malloc(sizeof(ContainerWrapper_RPGE));
    // validate values.
    if (cw == NULL)
        return NULL;
    if (!_isContainerType_STACK_RPGE(type))
    {
        log_error("_create_CONTAINER_WRAPPER_RPGE(): type {%d} is undefined");
        errno = EINVAL;
        return NULL;
    }
    if (container == NULL)
    {
        log_error("_create_CONTAINER_WRAPPER_RPGE(): container is NULL");
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
        cw->frender = &_render_Combat_C_RPGE;
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
    }

    cw->type = type;
    cw->container = container;
    return cw;
}

int push_CONTAINER_STACK_RPGE(bool prio, void *container, enum ContainerType_RPGE type)
{
    // check if stack exists.
    if (_check_CONTAINER_STACK_RPGE())
        return 1;
    
    // create a ContainerItem to push container on stack.
    ContainerItem_RPGE *conItem = malloc(sizeof(ContainerItem_RPGE));
    if (conItem == NULL)
        return 1;
    conItem->cw = _create_CONTAINER_WRAPPER_RPGE(container, type);
    if (conItem->cw == NULL)
        return 1;
    
    // default toRender and toUpdate true because top element of stack now.
    conItem->toRender = true;
    conItem->toRender = true;
    conItem->_prio = prio;
        
    // push to stack.
    conItem->next = _CONTAINER_STACK->top;
    _CONTAINER_STACK->top = conItem;
    _CONTAINER_STACK->length++;
    
    // update toRender and toUpdate flags.
    update_FLAGS_CONTAINER_STACK_RPGE();

    return 0;
}

int pop_CONTAINER_STACK_RPGE()
{
    if (_CONTAINER_STACK->length < 1)
        return 1;
    
    // remove element.
    ContainerItem_RPGE *conItem = _CONTAINER_STACK->top;
    _CONTAINER_STACK->top = _CONTAINER_STACK->top->next;
    // toRender and toUpdate flags true because top element of stack now.
    _CONTAINER_STACK->top->toRender = true;
    _CONTAINER_STACK->top->toUpdate = true;

    // clear up.
    destroy_ContainerItem_RPGE(conItem);
    _CONTAINER_STACK->length--;

    // update toRender and toUpdate flags.
    update_FLAGS_CONTAINER_STACK_RPGE();

    return 0;
}

/**
 * render from buttom to top recursive.
 */
static int _render_CONTAINER_STACK(SDL_Renderer *renderer, ContainerItem_RPGE *conItem)
{
    // traverse stack.
    if (conItem->next != NULL)
        return _render_CONTAINER_STACK(renderer, conItem->next);
    // render from buttom to top.
    if (conItem->toRender || conItem->_prio)
        return conItem->cw->frender(renderer, conItem->cw);
}

int render_CONTAINER_STACK_RPGE(SDL_Renderer *renderer)
{
    // render from buttom to top.
    if (_check_CONTAINER_STACK_RPGE())
        return 1;
    if (_CONTAINER_STACK->length < 1)
    {
        // nothing to render.
        return 0;
    }
    return _render_CONTAINER_STACK(renderer, _CONTAINER_STACK->top);
}

static int _update_CONTAINER_STACK(ContainerItem_RPGE *conItem)
{
    // update from top to buttom.
    // only top containerWrapper gets updated, except for prio containerWrapper.
    if (conItem->toUpdate || conItem->_prio) 
        // update container.
        conItem->cw->fupdate(conItem->cw);
    // traverse stack.
    if (conItem->next != NULL)
        return _update_CONTAINER_STACK(conItem->next);       
}

int update_CONTAINER_STACK_RPGE()
{
    // update from top to buttom.
    if (_check_CONTAINER_STACK_RPGE())
        return 1;
    if (_CONTAINER_STACK->length < 1)
    {
        // nothing to update.
        return 0;
    }
    return _update_CONTAINER_STACK(_CONTAINER_STACK->top);
}

// rules for which elements gets displayed and updated.
static void _setToUpdateFlag_CONTAINER_ITEM(struct ContainerItem_RPGE* top, struct ContainerItem_RPGE* next) {
    if(next != NULL) {
        if(top->toUpdate) {
            switch(top->cw->type) {
                case MENU_CT_RPGE:
                    next->toUpdate = false;
                case ROOM_CT_RPGE:
                    next->toUpdate = false;
                    return;
                case COMBAT_CT_RPGE:
                    next->toUpdate = false;
                    return;
                case WORLD_CT_RPGE:
                    next->toUpdate = false;
                    return;
            }
        } else {
            next->toUpdate = false;
        }
    }
}

static void _setToRenderFlag_CONTAINER_ITEM(struct ContainerItem_RPGE* top, struct ContainerItem_RPGE* next) {
    if(next != NULL) {
        if(top->toRender) {
            switch(top->cw->type) {
                case MENU_CT_RPGE:
                    next->toRender = true;
                case ROOM_CT_RPGE:
                    next->toRender = false;
                    return;
                case COMBAT_CT_RPGE:
                    next->toRender = false;
                    return;
                case WORLD_CT_RPGE:
                    next->toRender = false;
                    return;
            }
        } else {
            next->toRender = false;
        }
    }
}

static void _update_FLAGS_CONTAINER_STACK_RPGE(ContainerItem_RPGE* item) {
    if(item == NULL || item->next == NULL) {
        return;
    }
    // update toRenders.
    _setToRenderFlag_CONTAINER_ITEM(item, item->next);
    // update toUpdates.
    _setToUpdateFlag_CONTAINER_ITEM(item, item->next);
}

void update_FLAGS_CONTAINER_STACK_RPGE() {
    if (_CONTAINER_STACK->top == NULL) return;
    // update toRenders.
    _update_FLAGS_CONTAINER_STACK_RPGE(_CONTAINER_STACK->top);
}