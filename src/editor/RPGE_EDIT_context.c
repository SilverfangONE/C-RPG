#include <stdlib.h>
#include "RPGE_EDIT_context.h"
#include "log.h"

CONTEXT_EDIT* init_EDIT(char* pName) {
    CONTEXT_EDIT* context = malloc(sizeof(CONTEXT_EDIT));
    if (context == NULL) return NULL;
    context->pName = (char *)malloc(sizeof(char) * 20);
    if (context->pName == NULL) return NULL;
    if (pName == NULL)
    {
        log_error("init_EDIT(): pName is NULL");
        errno = EINVAL;
        return NULL;
    }
    strncpy(gContext->pName, "C_RPG", sizeof(gContext->pName));
 

    context->pName = (char *)malloc(sizeof(pName));
    strncpy(asset->pathIMG, pathIMG, sizeof(asset->pathIMG));
  
}; 

void destory_CONTEXT_EDITOR_RPGE(CONTEXT_EDIT* pContext) {
    free(pContext->pName);
    free(pContext);
}

void destory_VOID_CONTEXT_EDITOR_RPGE(void* pContext) {
    destory_CONTEXT_EDITOR_RPGE((CONTEXT_EDIT*) pContext);
}