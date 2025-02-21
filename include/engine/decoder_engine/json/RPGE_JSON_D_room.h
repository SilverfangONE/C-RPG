#ifndef RPGE_JSON_D_ROOM
#define RPGE_JSON_D_ROOM

#include "RPGE_C_room.h" 
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Room_C_RPGE* load_JSON_Room_C_RPGE(SDL_Renderer* renderer, const char* pathJSON); 
#endif 
