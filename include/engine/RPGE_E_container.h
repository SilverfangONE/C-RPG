#ifndef RPGE_E_CONTAINER
#define RPGE_E_CONTAINER

typedef enum ContainerType_RPGE {
    ROOM,
    COMBAT,
    WORLD
};

typedef struct Container_RPGE {
    enum ContainerType_RPGE type;
    void* container;
    int (*fupdate)(void*);
    int (*frender)(void*);
} Container_RPGE;

typedef struct ContainerItem_RPGE {
    ContainerItem_RPGE* next;
    Container_RPGE* container;
} ContainerItem_RPGE;

typedef struct ContainerStack_RPGE {
    ContainerItem_RPGE* top;
    int length;
} ContainerStack_RPGE;

int set_ContainerStack_RPGE(ContainerStack_RPGE* stack);
int push_Container_RPGE(Container_RPGE* container);
Container_RPGE* pop_Container_RPGE();
int render_ContainerStack_RPGE(ContainerStack_RPGE* stack);
int update_ContainerStack_RPGE(ContainerStack_RPGE* stack);
#endif