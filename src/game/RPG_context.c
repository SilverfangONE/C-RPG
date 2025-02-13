#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "RPG_context.h"

CONTEXT_RPG* init_RPG() {
    CONTEXT_RPG* gContext = (CONTEXT_RPG*)malloc(sizeof(CONTEXT_RPG));
    if (gContext == NULL) {
        log_error("Couldn't allocate memory for gContext with malloc!");
        return NULL;
    }
    gContext->gName = (char*)malloc(sizeof(char) * 20);
    if (gContext->gName == NULL) {
        log_error("Couldn't allocate memory for gContext->gName with malloc!");
        return NULL;
    }
    strncpy (gContext->gName, "C_RPG", sizeof(gContext->gName));
    return gContext;
}

void destory_VOID_CONTEXT_RPG(void* pContext) {
    destory_CONTEXT_RPG((CONTEXT_RPG*) pContext);
}

void destory_CONTEXT_RPG(CONTEXT_RPG* gContext) {
    free(gContext->gName);
    free(gContext);
}
