#ifndef RPGE_UI_TEXT
#define RPGE_UI_TEXT

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

int getAlphabetIndex_UI_RPGE(char letter);
int getAlphabetSpecialIndex_UI_RPGE(char* letter);
int render_Text_WIDE_UI_RPGE(SDL_Renderer* renderer, char* text, Vec2D vCoordinates, Vec2D vTable, Assetsheet_RPGE* font);
/**
 * currently only for 8 bit font which accuatly has an offset x wise with 2 pixel 
 */
int render_Text_NARROW_UI_RPGE(SDL_Renderer *renderer, char *textBuffer, Vec2D vCoordinates, Vec2D vTable, Assetsheet_RPGE *font);

// calc from vTableSize with vPatchSize.
Vec2D _calc_vTextTable_TEXT_WIDE_UI_RPGE(Assetsheet_RPGE* asset, Assetsheet_RPGE* font,  Vec2D vTableSize, Vec2D vPaddingHorizontal, Vec2D vPaddingVertical);
Vec2D _calc_vTextTable_TEXT_NARROW_UI_RPGE(Assetsheet_RPGE* asset, Assetsheet_RPGE* font, Vec2D vTableSize, Vec2D vSubPatchSize, Vec2D vPaddingHorizontal, Vec2D vPaddingVertical);
Vec2D _calc_vTextTable_TEXT_UI_RPGE(char *textBuffer);
Vec2D _calc_vTableSize_TEXT_WIDE_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTextTable, Vec2D vPaddingHorizontal, Vec2D vPaddingVertical, Vec2D vSubPatchSize);
Vec2D _calc_vTableSize_TEXT_NARROW_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTextTable, Vec2D vPaddingHorizontal, Vec2D vPaddingVertical, Vec2D vSubPatchSize);
Vec2D _calc_vTextCoordinates_TEXT_UI_RPGE(Assetsheet_RPGE* asset, Vec2D vCoordinates);
#endif