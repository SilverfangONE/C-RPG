#ifndef RPGE_C_ROOM
#define RPGE_C_ROOM

#include "RPGE_G_tilemap.h"

typedef struct Room_C_RPGE {
    int ID;
    Tile_G_RPGE* tilemap;
} Room_C_RPGE;

int update_Room_C_RPGE(Room_C_RPGE* room);
int _update_Room_C_RPGE(void* room);
int render_Room_C_RPGE(SDL_Renderer* renderer, Room_C_RPGE* room);
int _render_Room_C_RPGE(SDL_Renderer* renderer, void* room);

void destroy_Room_C_RPGE(Room_C_RPGE* room);
void _destroy_Room_C_RPGE(void* room);
#endif