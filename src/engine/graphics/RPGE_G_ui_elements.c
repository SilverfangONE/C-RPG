#include <stdlib.h>
#include "RPGE_G_ui_elements.h"
#include "RPGE_U_array.h"

extern const int PATCH_SIZE;

BASE_UI_RPGE* build_base_UI_RPGE(char* label) {
    if (label == NULL) {
        errno = EINVAL;
        return NULL;
    }
    
    BASE_UI_RPGE* base = (BASE_UI_RPGE*) malloc (sizeof(BASE_UI_RPGE));
    if (base == NULL) return NULL;

    // calc text postion 
    
    
    
    return NULL;
}

void destroy_base_UI_RPGE(BASE_UI_RPGE* base) {
    free(base);
}

Btn_UI_RPGE* build_Btn_UI_RPGE(char* label,  void (*faction)(struct CONTEXT_RPGE *eContext)) {
    return NULL;
}

void destroy_Btn_UI_RPGE(Btn_UI_RPGE* btn) {
    destroy_base_UI_RPGE(btn->base);
    free(btn);   
}

/**
 * @return 0 if no erros occured, and 1 if erros occured
 */
int update_Dialog_UI_RPGE(CONTEXT_RPGE* eContext, Dialog_UI_RPGE* dialog) {
    return 1;
}

Dialog_UI_RPGE* build_Dialog_UI_RPGE(char* label, Vec2D vTableSize) {
    return NULL;
}

void destroy_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog) {

}

int getIndex_Menuasset_UI_RPGE(enum MenuassetComponents_UI_RPGE tile) {
    switch (tile) {
        case UPER_LEFT_EDGE:
            return 0;
        case UPER_RIGHT_EDGE:
            return 1;
        case DOWN_LEFT_EDGE:
            return 2;
        case DOWN_RIGHT_EDGE:
            return 3;
        case MIDDEL:
            return 4;
    }
}

int getIndex_Menuasset_UI_RPGE(enum MenuassetComponents_UI_RPGE tile) {
    switch (tile) {
        case UPER_LEFT_EDGE:
            return 0;
        case UPER_RIGHT_EDGE:
            return 1;
        case DOWN_LEFT_EDGE:
            return 2;
        case DOWN_RIGHT_EDGE:
            return 3;
        case MIDDEL:
            return 4;
    }
}