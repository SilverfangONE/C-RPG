#ifndef RPGE_C_MENU
#define RPGE_C_MENU

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

enum UI_COMP_Type_C_RPGE {
    LABEL_UI_COMP_TYPE,
    DIALOG_UI_COMP_TYPE,
    TEXT_UI_COMP_TYPE,
    BACKGROUND_UI_COMP_TYPE,
    // TODO needs to be implemented 
    TREE_MENU_UI_COMP_TYPE,
    HEALTH_BAR_UI_COMP_TYPE
};

typedef struct _UI_COMP_C_RPGE {
    enum UI_COMP_Type_C_RPGE type;
    void* comp;
    int (*fupdate)(void* comp);
    int (*frender)(void* comp);
} _UI_COMP_C_RPGE;

typedef struct Menu_C_RPGE {
    // def size 4 elements.
    int ID;
    _UI_COMP_C_RPGE* _uiComps;
    int _sizeUIComps;
    int activeUICompIndex;
    int (*fupdate)(Menu_C_RPGE* menu);
    int (*frender)(SDL_Renderer* renderer, Menu_C_RPGE* menu);
} Menu_C_RPGE;

Menu_C_RPGE* build_Menu_C_RPGE();
int add_UIComp_Menu_C_RPGE(void* comp, enum UI_COMP_Type_C_RPGE type);

int update_Menu_C_RPGE(Menu_C_RPGE* menu);
int _update_Menu_C_RPGE(void* menu);
int render_Menu_C_RPGE(SDL_Renderer* renderer, Menu_C_RPGE* menu);
int _render_Menu_C_RPGE(SDL_Renderer* renderer, void* menu);

void destroy_Menu_C_RPGE(Menu_C_RPGE* room);
void _destroy_Menu_C_RPGE(void* room);
#endif