#ifndef RPGE_DEC_ASSETSHEET
#define RPGE_DEC_ASSETSHEET

#include "RPGE_G_assetsheet.h" 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Assetsheet_RPGE* load_Assetsheet_JSON_RPGE(SDL_Renderer* renderer, const char* pathJSON) ; 

#endif