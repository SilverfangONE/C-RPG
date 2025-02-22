#include "RPGE_UI_select_menu.h"
#include <stdlib.h>
#include <log.h>
#include <errno.h>
#include <string.h>

static const int _DEFAULT_ARR_MENU_SIZE = 20;

SelectMenu_UI_RPGE* create_RootSelectMenu_UI_RPGE(Vec2D vCoordinates, Vec2D vEntryTableSize) 
{
    SelectMenu_UI_RPGE* menu = malloc(sizeof(SelectMenu_UI_RPGE));
    if (vEntryTableSize.x < 0 || vEntryTableSize.y < 0) {
        log_error("create_SelectMenu_UI_RPGE(): vEntryTableSize {.x=%d, .y=%d} is invalid", vEntryTableSize.x, vEntryTableSize.y);
        errno = EINVAL;
        return NULL;
    }
    menu->_arrMenu = (SelectMenu_UI_RPGE**)(sizeof(SelectMenu_UI_RPGE*) * _DEFAULT_ARR_MENU_SIZE);
    menu->ID = 0;
    strncpy(menu->_textBuffer, "root", sizeof(menu->_textBuffer) - 1);
    menu->_textBuffer[sizeof(menu->_arrMenu) - 1] = '\0';
    menu->show = true;
    menu->_build = false;
    menu->_lengthArrMenu = _DEFAULT_ARR_MENU_SIZE;
    return menu;
}

/**
 * returns index of free slot
 */
int _getFreeSlot_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu) {
    // check of size and ID of _arrMenu.
    int currSize = 0;
    for (int i = 0; i < menu->_lengthArrMenu; i++) {
        if (menu->_arrMenu[i] == NULL) 
        {
            return i;
        }
    }
    // no space left.
    // expand by _DEFAULT_ARR_MENU_SIZE
    SelectMenu_UI_RPGE** arr = (SelectMenu_UI_RPGE**) malloc(sizeof(SelectMenu_UI_RPGE*) * (menu->_lengthArrMenu + _DEFAULT_ARR_MENU_SIZE));
    
}

int add_SelecMenu_UI_RPGE(SelectMenu_UI_RPGE* menu, char* label, unsigned int ID, int (*fonclick)(CONTEXT_RPGE* eContext))
{
    
    SelectMenu_UI_RPGE* menu = malloc(sizeof(SelectMenu_UI_RPGE));

}

SelectMenu_UI_RPGE* build_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* rooMenu) 
{
    
}