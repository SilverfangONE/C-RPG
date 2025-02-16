#ifndef RPGE_UI_LABEL
#define RPGE_UI_LABEL

#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"

typedef struct Label_UI_RPGE {
    char textBuffer[250];
    Assetsheet_RPGE* font;
    Vec2D vTextTable;
    Vec2D vTextCoordinates;
    Background_UI_RPGE* background;
} Label_UI_RPGE;

Label_UI_RPGE* build_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates);
int render_Label_UI_RPGE(SDL_Renderer* renderer, Label_UI_RPGE* label);
#endif