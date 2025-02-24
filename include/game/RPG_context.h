#ifndef RPGE_G_CONTEXT
#define RPGE_G_CONTEXT

#include "RPGE_E_context.h"
#include "RPGE_UI_label.h"
#include "RPGE_UI_dialog.h"
#include "RPGE_UI_textfield.h"

typedef struct Object_RPG {
    void* obj;
    int (*update)(CONTEXT_RPGE* eContext, void* obj);
    int (*render)(CONTEXT_RPGE* eContext, void* obj);
} Object_RPG;

typedef struct CONTEXT_RPG {
    char* pName;
    Label_UI_RPGE* label;
    Dialog_UI_RPGE* dialog;
    TextField_UI_RPGE* textField;
} CONTEXT_RPG;

CONTEXT_RPG* init_RPG(char*);
void destory_CONTEXT_RPG(CONTEXT_RPG*);
void destory_VOID_CONTEXT_RPG(void*);
#endif