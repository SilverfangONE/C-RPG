#ifndef RPGE_C_COMBAT
#define RPGE_C_COMBAT

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_G_tilemap.h"

typedef struct Combat_C_RPGE {
    int ID;
    Tilemap_G_RPGE* tilemap;
} Combat_C_RPGE;

int update_Combat_C_RPGE(Combat_C_RPGE* combat);
int _update_Combat_C_RPGE(void* combat);
int render_Combat_C_RPGE(SDL_Renderer* renderer, Combat_C_RPGE* Combat);
int _render_Combat_C_REPGE(SDL_Renderer* renderer, void* combat);

int destroy_Combat_C_RPGE(Combat_C_RPGE* combat);
int _destroy_Combat_C_RPGE(void* combat);
#endif