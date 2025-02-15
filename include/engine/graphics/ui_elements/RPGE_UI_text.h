#ifndef RPGE_UI_TEXT
#define RPGE_UI_TEXT

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

int getAlphabetIndex_UI_RPGE(char letter);
int getAlphabetSpecialIndex_UI_RPGE(char* letter);
int render_Text_UI_RPGE(SDL_Renderer* renderer, char* text, Vec2D vCoordinates, Vec2D vTable, Assetsheet_RPGE* font);
#endif