#ifndef RPGE_UI_BACKGROUND
#define RPGE_UI_BACKGROUND

#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"

enum MENU_TILE_TYPE {
    MENU_UP_LEFT_CORN,
    MENU_UP_RIGTH_CORN,
    MENU_DOWN_LEFT_CORN,
    MENU_DOWN_RIGTH_CORN,
    MENU_NORTH_BOARDER_MID,
    MENU_EAST_BOARDER_MID,
    MENU_WEST_BOARDER_MID,
    MENU_SOUTH_BOARRDER_MID,
    MENU_MID,
    MENU_ARROW_UP,
    MENU_ARROW_DOWN,
    MENU_ARROW_LEFT,
    MENU_CHECKBOX_ENABLED,
    MENU_CHECKBOX_NOT_ENABLED
};

int lookup_BackgroundTiles_UI_RPGE(enum MENU_TILE_TYPE tile);
int set_flookupBackgroundTiles_UI_RPGE(int (*newflookupBackgroundTiles_UI_RPGE)(enum MENU_TILE_TYPE));
void set_flookupBackgroundTiles_DEFAULT_UI_RPGE();
int default_getIndex_Background_MENU_TILE_UI_RPGE(enum MENU_TILE_TYPE tile);

typedef struct Background_UI_RPGE {
    Assetsheet_RPGE* asset;
    Vec2D vTableSize;
    Vec2D vCoordinates;
    int* m_indices;
} Background_UI_RPGE;

int *constructBackgroundIndexArr_UI_RPGE(Vec2D vTableSize);

/**
 * @return 0 if no error occurded, 1 if occurded.
 */
int render_Background_UI_RPGE(SDL_Renderer* renderer, Background_UI_RPGE* background);

/**
 * dont call destory asset!
 */
void destroy_Background_UI_RPGE(Background_UI_RPGE* background);

Background_UI_RPGE* build_Background_UI_RPGE(Assetsheet_RPGE* asset, Vec2D vCoordinates, Vec2D vTableSize );
#endif