#ifndef RPGE_EDIT_CONTEXT
#define RPGE_EDIT_CONTEXT

#include "RPGE_E_context.h"
#include "RPGE_UI_label.h"

typedef struct CONTEXT_EDIT {
    /**
     * Programm Name
     */
    char* pName;
    Label_UI_RPGE* label;
} CONTEXT_EDIT;

CONTEXT_EDIT* init_EDIT();
void destory_CONTEXT_EDIT(CONTEXT_EDIT* );
void destory_VOID_CONTEXT_EDIT(void* );

#endif
