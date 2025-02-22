#ifndef RPGE_UI_SELECT_MENU
#define RPGE_UI_SELECT_MENU

#include "RPGE_UI_background.h"
#include "RPGE_E_context.h"
#include "RPGE_U_vec.h"
#include <stdbool.h>

typedef struct SelectMenu_UI_RPGE {
    unsigned int ID;
    bool show;
    struct SelectMenu_UI_RPGE **_arrMenu;
    int _lengthArrMenu;
    int (*fonclick)(CONTEXT_RPGE* eContext);
    // Text.
    // TODO: refactor text to own comp.
    char _textBuffer[250];
    Assetsheet_RPGE* _font;
    Vec2D _vTextTable;
    Vec2D _vTextCoordinates; 
    Background_UI_RPGE* _background;
    // build process.
    Vec2D _vEntryTableSize;
    Vec2D _vCoordinates;
    bool _build;
} SelectMenu_UI_RPGE;

// api.
SelectMenu_UI_RPGE* create_RootSelectMenu_UI_RPGE(Vec2D vCoodinates, Vec2D vEntryTableSize);
SelectMenu_UI_RPGE* build_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu);
int add_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu, char* label, unsigned int ID, int (*fonclick)(CONTEXT_RPGE* eContext));

int render_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu);
int update_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu);

// lifecylce.
void destroy_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu);
void _destroy_SelectMenu_UI_RPGE(void* menu);

#endif