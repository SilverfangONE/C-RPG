#ifndef RPGE_C_WORLD
#define RPGE_C_WORLD

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_C_room.h"

typedef struct World_C_RPGE {
    Room_C_RPGE* rooms;
    int roomsLength;
    int currentRoomIndex;
} World_C_RPGE;

int update_World_C_RPGE(World_C_RPGE* world);
int _update_World_C_RPGE(void* world);
int render_World_C_RPGE(SDL_Renderer* renderer, World_C_RPGE* world);
int _render_World_C_RPGE(SDL_Renderer* renderer, void* world);

int destroy_World_C_RPGE(World_C_RPGE* world);
int _destroy_World_C_RPGE(void* world);
#endif