#include "RPGE_UI_select_menu.h"
#include <stdlib.h>
#include <log.h>
#include <errno.h>
#include <string.h>
#include "RPGE_U_array.h"

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
    setNull_ArrayPtr_UTIL(menu->_arrMenu, menu->_lengthArrMenu);
    menu->ID = 0;
    strncpy(menu->_textBuffer, "root", sizeof(menu->_textBuffer) - 1);
    menu->_textBuffer[sizeof(menu->_arrMenu) - 1] = '\0';
    menu->show = true;
    menu->_build = false;
    menu->_lengthArrMenu = _DEFAULT_ARR_MENU_SIZE;
    return menu;
}

/**
 * returns index of free slot, or -1 if ID is duplicated
 */
int _getFreeSlot_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu, unsigned int ID) 
{
    int index = -1;
    
    // only if _arrMenu size is not zero
    if (menu->_arrMenu != NULL) {
        // check of size and ID of _arrMenu.
        for (int i = 0; i < menu->_lengthArrMenu; i++) {
            if (menu->_arrMenu[i] == NULL) 
            {
                return i;
            }
            // check for duplicated ID.
            if (menu->_arrMenu[i]->ID == ID) 
            {
                return -1;
            }
        }
        if (index > -1) {
            return index;
        }
    }
    
    // no space left.
    // expand space of _arrMenu by _DEFAULT_ARR_MENU_SIZE
    SelectMenu_UI_RPGE** arr = (SelectMenu_UI_RPGE**) malloc(sizeof(SelectMenu_UI_RPGE*) * (menu->_lengthArrMenu + _DEFAULT_ARR_MENU_SIZE));
    setNull_ArrayPtr_UTIL(arr, menu->_lengthArrMenu + _DEFAULT_ARR_MENU_SIZE);
    // copy stuff over.
    for (int i = 0; i < menu->_lengthArrMenu; i++) 
    {
        arr[i] = menu->_arrMenu[i];
    }
    
    // setting stuf.
    index = menu->_lengthArrMenu;
    menu->_lengthArrMenu += _DEFAULT_ARR_MENU_SIZE;
    menu->_arrMenu = arr;
    return index;
}

/**
 * returns created SelectMenu_UI_RPGE struct pointer which has been added to given root menu.
 */
SelectMenu_UI_RPGE* add_SelecMenu_UI_RPGE(SelectMenu_UI_RPGE* rootMenu, char* label, unsigned int ID, int (*fonclick)(CONTEXT_RPGE* eContext))
{
    // search for free slot and check if ID is already used.
    int index = _getFreeSlot_SelectMenu_UI_RPGE(rootMenu, ID);
    if (index < 0) {
        log_error("add_SelecMenu_UI_RPGE(): ID {%u} is already used", ID);
        errno = EINVAL;
        return NULL;
    }
    if (label == NULL || strnlen(label, sizeof(label) - 1) < 1) {
        log_error("add_SelecMenu_UI_RPGE(): label {'%s'} is invalid", label);
        errno = EINVAL;
        return NULL;
    }
    // create sub menu.
    SelectMenu_UI_RPGE* subMenu = malloc(sizeof(SelectMenu_UI_RPGE));
    
    subMenu->ID = ID;
    subMenu->show = false;
    subMenu->_build = false;
    subMenu->_lengthArrMenu = 0;
    subMenu->_arrMenu = NULL;
    subMenu->fonclick = fonclick;

    strncpy(subMenu->_textBuffer, label, sizeof(subMenu->_textBuffer) - 1);
    subMenu->_textBuffer[sizeof(subMenu->_textBuffer) - 1] = '\0';

    // add to _arrMenu
    rootMenu->_arrMenu[index] = subMenu;
    
    return subMenu;
}

void destroy_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* menu) 
{
    
}

void _destroy_SelectMenu_UI_RPGE(void* voidMenu) 
{
    SelectMenu_UI_RPGE* menu = (SelectMenu_UI_RPGE*) voidMenu;

}

SelectMenu_UI_RPGE* build_SelectMenu_UI_RPGE(SelectMenu_UI_RPGE* rooMenu) 
{
    
}