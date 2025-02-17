#ifndef RPGE_UI_DIALOG
#define RPGE_UI_DIALOG

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"
#include "RPGE_E_keymap.h"

typedef struct Dialog_UI_RPGE {
    // 4 KiB
    char* textBuffer[4096];
    int lastDisplayedChar;
    Assetsheet_RPGE* font;
    Vec2D vTextTable;
    Vec2D vTextCoordinates;
    Background_UI_RPGE* background;
};

Dialog_UI_RPGE* build_Dialog_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates);
int render_Dialog_UI_RPGE(SDL_Renderer* renderer, Dialog_UI_RPGE* dialog);
int update_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog, Keymap_RPGE* keymap);
void destory_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog);

#endif