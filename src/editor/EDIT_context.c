#include <stdlib.h>
#include "EDIT_context.h"
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
    strncpy(context->pName, "C_RPG", sizeof(context->pName));
    log_debug("[Created CONTEXT_EDIT]");
    return context;
}; 

void destory_CONTEXT_EDIT(CONTEXT_EDIT* pContext) {
    free(pContext->pName);
    free(pContext);
}

void destory_VOID_CONTEXT_EDIT(void* pContext) {
    destory_CONTEXT_EDIT((CONTEXT_EDIT*) pContext);
}