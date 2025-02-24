#ifndef RPGE_UI_TEXTFIELD
#define RPGE_UI_TEXTFIELD

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct TextField_UI_RPGE {
    // Kib;
    char textBuffer[4096];
    Vec2D vTable;
    Vec2D vPixelSize;
    Vec2D vCor; 
    Assetsheet_RPGE* font;
} TextField_UI_RPGE;

// api;
TextField_UI_RPGE* build_TextField_UI_RPGE (Assetsheet_RPGE* asset, char* text, Vec2D vCor);
void destroy_TextField_UI_RPGE (TextField_UI_RPGE* text_UI_RPGE);
int render_TextField_UI_RPGE(SDL_Renderer* renderer, TextField_UI_RPGE* text_UI_RPGE);
Vec2D getAlphabetSubTileVec2D_UI_RPGE(char c);

#endif