#ifndef RPGE_UI_DIALOG
#define RPGE_UI_DIALOG

#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"
#include "RPGE_E_keymap.h"

typedef struct Dialog_UI_RPGE {
    // 4 KiB
    bool show;
    char textBuffer[4096];
    int textDisplayBufferSize;
    int nextDisplayCharIndex;
    Assetsheet_RPGE* font;
    Vec2D vTextTable;
    Vec2D vTextCoordinates;
    Vec2D vIndicatorCoordinates;
    Background_UI_RPGE* background;
} Dialog_UI_RPGE;

/**
 * Builds a Dialog_UI_RPGE struct with given params (in heap).
 * 
 * @param font Assetsheet_RPGE for font asset
 * @param asset Assetsheet_RPGE for menu asset
 * @param text The text to display in dialog
 * @param vCoordinates Vec2D wich contains the upper left edge Coordinates of the dialog
 * @param vTextTable Vec2D wich contains table of chars of the dialog box
 * @return pointer to created Dialog_UI_RPGE struct, or NULL if an error occured.
 */
Dialog_UI_RPGE* build_Dialog_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates, Vec2D vTextTable);

/**
 * Renderes given Dialog_UI_RPGE struct on the current render target.
 * 
 * @param render SDL_Renderer* pointer for SDL context
 * @param dialog Dialog_UI_RPGE which should get rendered
 * @return 0 if no error occored during exection, otherwise 1
 */
int render_Dialog_UI_RPGE(SDL_Renderer* renderer, Dialog_UI_RPGE* dialog);

/**
 * Updates given Dialog_UI_RPGE struct.
 * 
 * @param dialog Dialog_UI_RPGE which should get updated
 * @param keymap Keymap_RPGE* pointer to get current key input from user
 * @return 0 if no error occored during exection, otherwise 1
 */
int update_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog, Keymap_RPGE* keymap);

/**
 * Frees Dialog_UI_RPGE struct except for asset pointers.
 * 
 * @param dialog Dialog_UI_RPGE struct which should get freed from heap
 */
void destory_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog);
#endif