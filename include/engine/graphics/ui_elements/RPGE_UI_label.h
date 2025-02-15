#ifndef RPGE_UI_LABEL
#define RPGE_UI_LABEL

#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"

typedef struct LABEL_UI_RPGE {
    char* text;
    Assetsheet_RPGE* font;
    Vec2D vTable;
    Vec2D vCoordinates;
    BACKGROUND_UI_RPGE* background;
} LABEL_UI_RPGE;

LABEL_UI_RPGE* create_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text);
#endif