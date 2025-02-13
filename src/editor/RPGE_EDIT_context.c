#include <stdlib.h>
#include "RPGE_EDIT_context.h"

CONTEXT_EDITOR_RPGE* init_RPG() {
    return NULL;
};

void destory_CONTEXT_EDITOR_RPGE(CONTEXT_EDITOR_RPGE* pContext) {
    free(pContext->pName);
    free(pContext);
}

void destory_VOID_CONTEXT_EDITOR_RPGE(void* pContext) {
    destory_CONTEXT_EDITOR_RPGE((CONTEXT_EDITOR_RPGE*) pContext);
}