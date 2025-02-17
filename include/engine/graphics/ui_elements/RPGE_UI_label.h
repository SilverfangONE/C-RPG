#ifndef RPGE_UI_LABEL
#define RPGE_UI_LABEL

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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

/**
 * Builds a Label_UI_RPGE struct with given params (in heap). 
 * 
 * @param font Assetsheet_RPGE for font asset
 * @param asset Assetsheet_RPGE for menu asset
 * @param text The text to display on the label
 * @param vCoordinates Vec2D wich contains the upper left edge Coordinates of the label  
 * @return pointer to created Label_UI_RPGE struct, or NULL if error occured.
 */
Label_UI_RPGE* build_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates);

/**
 * Renderes given Label_UI_RPGE struct on the current render target.
 * 
 * @param render SDL_Renderer* pointer for SDL context
 * @param label Label_UI_RPGE which should get rendered
 * @return 0 if no error occored during exection, otherwise 1
 */
int render_Label_UI_RPGE(SDL_Renderer* renderer, Label_UI_RPGE* label);

/**
 * Frees Label_UI_RPGE struct except for asset pointers.
 * 
 * @param label Label_UI_RPGE struct which should get freed from heap
 */
void destory_Label_UI_RPGE(Label_UI_RPGE* label);

#endif