#ifndef RPGE_UI_INPUT
#define RPGE_UI_INPUT

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"
#include "RPGE_E_keymap.h"

/**
 * just one line label with input 
 */
typedef struct InputField_UI_RPGE {
    bool show;
    char *textBuffer;
    Assetsheet_RPGE* font;
    Vec2D vTextTable;
    Vec2D vTextCoordinates;
    Background_UI_RPGE* background;
} InputField_UI_RPGE;

int update_InputField_UI_RPGE(InputField_UI_RPGE* input, Keymap_RPGE* keymap);
int render_InputField_UI_RPGE(SDL_Renderer* renderer, InputField_UI_RPGE* input);

InputField_UI_RPGE* build_InputField_UI_RPGE (Assetsheet_RPGE* aFont, Assetsheet_RPGE* aMenu, int sizeOfTextBuffer, Vec2D vCoordinates);
void destroy_InputField_UI_RPGE(InputField_UI_RPGE* input);

#endif