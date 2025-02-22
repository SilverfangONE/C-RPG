#ifndef EDIT_CONTEXT
#define EDIT_CONTEXT

#include "RPGE_UI_label.h"

typedef struct CONTEXT_EDIT {
    /**
     * Programm Name
     */
    char* pName;
    Label_UI_RPGE* label;
} CONTEXT_EDIT;

CONTEXT_EDIT* init_EDIT(char* );
void destory_CONTEXT_EDIT(CONTEXT_EDIT* );
void destory_VOID_CONTEXT_EDIT(void* );

#endif
