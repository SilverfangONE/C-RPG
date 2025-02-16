#ifndef RPGE_G_UI_ELEMENTS
#define RPGE_G_UI_ELEMENTS

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_E_context.h"

extern const int PATCH_SIZE;

enum MenuassetComponents_UI_RPGE {
    UPER_LEFT_EDGE,
    UPER_RIGHT_EDGE,
    DOWN_LEFT_EDGE,
    DOWN_RIGHT_EDGE,
    MIDDEL
};

int getIndex_Menuasset_UI_RPGE(enum MenuassetComponents_UI_RPGE);
int render_Text_UI_RPGE(char* text, Vec2D coordinates, Vec2D vTableSize);

typedef struct Background_UI_RPGE {
    Vec2D vTableSize;
    int* m_indices;
} Background_UI_RPGE;

int render_Background_UI_RPGE(SDL_Renderer* renderer, Background_UI_RPGE* background);

typedef struct BASE_UI_RPGE {
    char* label;
    Vec2D vLabel;
    Background_UI_RPGE* background;    
} BASE_UI_RPGE, Label_UI_RPGE;

BASE_UI_RPGE* build_BASE_UI_RPGE(char* label);
void destroy_BASE_UI_RPGE(BASE_UI_RPGE* label);
int render_BASE_UI_RPGE(SDL_Renderer* renderer, BASE_UI_RPGE* label);

typedef struct Btn_UI_RPGE {
    BASE_UI_RPGE* base;
    void (*faction)(struct CONTEXT_RPGE *eContext);
} Btn_UI_RPGE;

Btn_UI_RPGE* build_Btn_UI_RPGE(char* label,  void (*faction)(struct CONTEXT_RPGE *eContext));
void destroy_Btn_UI_RPGE(Btn_UI_RPGE* btn);

typedef struct Dialog_UI_RPGE {
    BASE_UI_RPGE* base;
    int lastCharIndex;
} Dialog_UI_RPGE;

/**
 * @return 0 if no erros occured, and 1 if erros occured
 */
int update_Dialog_UI_RPGE(CONTEXT_RPGE* eContext, Dialog_UI_RPGE* dialog);
Dialog_UI_RPGE* build_Dialog_UI_RPGE(char* label, Vec2D vTableSize);
void destroy_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog);

#endif