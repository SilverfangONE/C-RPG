#ifndef RPGE_E_CONTAINER
#define RPGE_E_CONTAINER

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>

typedef enum ContainerType_RPGE {
    ROOM_CT_RPGE,
    COMBAT_CT_RPGE,
    WORLD_CT_RPGE,
    MENU_CT_RPGE
} ContainerType_RPGE;

typedef struct ContainerWrapper_RPGE {
    bool prio;
    enum ContainerType_RPGE type;
    void* container;
    int (*fupdate)(void*);
    int (*frender)(SDL_Renderer* renderer, void*);
    int (*fdestroy)(void*);
} ContainerWrapper_RPGE;

typedef struct ContainerItem_RPGE {
    ContainerItem_RPGE* next;
    ContainerWrapper_RPGE* containerWrapper;
} ContainerItem_RPGE;

typedef struct ContainerStack_RPGE {
    ContainerItem_RPGE* top;
    int length;
} ContainerStack_RPGE;

int set_CONTAINER_STACK_RPGE(ContainerStack_RPGE* stack);
int push_CONTAINER_STACK_RPGE(
    bool prio, 
    void* container, 
    enum ContainerType_RPGE type
);
int pop_CONTAINER_STACK_RPGE();
int render_CONTAINER_STACK_RPGE();
int update_CONTAINER_STACK_RPGE();

ContainerItem_RPGE* _create_CONTAINER_WRAPPER_RPGE(bool prio, void* container, enum ContainerType_RPGE type);

bool _isContainerType_STACK_RPGE();
int _check_CONTAINER_STACK();
bool _toRender_CONTAINER_STACK_RPGE(ContainerType_RPGE type);
bool _toUpdate_CONTAINER_STACK_RPGE(ContainerType_RPGE type);
#endif