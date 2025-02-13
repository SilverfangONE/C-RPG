#ifndef RPGE_EDIT_CONTEXT
#define RPGE_EDIT_CONTEXT

#include "RPGE_E_context.h"

typedef struct CONTEXT_EDITOR_RPGE {
    /**
     * Programm Name
     */
    char* pName;
} CONTEXT_EDITOR_RPGE;

CONTEXT_EDITOR_RPGE* init_RPG();
void destory_CONTEXT_EDITOR_RPGE(CONTEXT_EDITOR_RPGE* );
void destory_VOID_CONTEXT_EDITOR_RPGE(void* );

#endif