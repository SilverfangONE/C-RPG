#ifndef RPGE_C_COMBAT
#define RPGE_C_COMBAT

#include "RPGE_G_tilemap.h"

typedef struct Combat_C_RPGE {
    int ID;
    Tilemap_G_RPGE* tilemap;
} Comabt_C_RPGE;

int update_Combat_C_RPGE(Combat_C_RPGE* combat);
int render_Combat_C_RPGE(SDL_Renderer* renderer, Combat_C_RPGE* Combat);
#endif