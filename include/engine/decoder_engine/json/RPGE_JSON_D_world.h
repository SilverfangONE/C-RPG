#ifndef RPGE_D_WORLD
#define RPGE_D_WORLD

#include "RPGE_C_world.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

World_C_RPGE* load_JSON_World_C_RPGE(SDL_Renderer* renderer, const char* pathJSON);

#endif