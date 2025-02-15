#ifndef RPGE_UI_BACKGROUND
#define RPGE_UI_BACKGROUND

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

typedef struct BACKGROUND_UI_RPGE {
    Assetsheet_RPGE* asset;
    Vec2D vTableSize;
    Vec2D vCoordinates;
    int* m_indices;
} BACKGROUND_UI_RPGE;

/**
 * @return 0 if no error occurded, 1 if occurded.
 */
int render_Background_UI_RPGE(SDL_Renderer* renderer, BACKGROUND_UI_RPGE* background);

/**
 * dont call destory asset!
 */
void destroy_Background_UI_RPGE(BACKGROUND_UI_RPGE* background);
#endif