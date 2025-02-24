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
    enum ContainerType_RPGE type;
    void* container;
    int (*fupdate)(void*);
    int (*frender)(SDL_Renderer* renderer, void*);
    void (*fdestroy)(void*);
} ContainerWrapper_RPGE;

typedef struct ContainerItem_RPGE {
    bool _prio;
    bool toRender;
    bool toUpdate;
    struct ContainerItem_RPGE* next;
    ContainerWrapper_RPGE* cw;
} ContainerItem_RPGE;

typedef struct ContainerStack_RPGE {
    ContainerItem_RPGE* top;
    int length;
} ContainerStack_RPGE;

// entry and exit point.
ContainerStack_RPGE* INIT_CONTAINER_STACK_RPGE();
void QUIT_CONTAINER_STACK_RPGE();

// manage stack.
int push_CONTAINER_STACK_RPGE(bool prio, void* container, enum ContainerType_RPGE type);
int pop_CONTAINER_STACK_RPGE();
int _check_CONTAINER_STACK_RPGE();
ContainerWrapper_RPGE *_create_CONTAINER_WRAPPER_RPGE(void *container, enum ContainerType_RPGE type);
bool _isContainerType_STACK_RPGE(ContainerType_RPGE type);

// lifecycle.
int render_CONTAINER_STACK_RPGE(SDL_Renderer* renderer);
int update_CONTAINER_STACK_RPGE();

// flags
void update_FLAGS_CONTAINER_STACK_RPGE();

void destroy_ContainerItem_RPGE(ContainerItem_RPGE *item);
#endif