#ifndef RPGE_D_TILEMAP
#define RPGE_D_TILEMAP

#include "RPGE_G_tilemap.h" 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Tilemap_G_RPGE* load_JSON_Tilemap_G_RPGE(SDL_Renderer* renderer, const char* pathJSON); 
#endif