#include "RPG_context.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

/**
 * Creates CONTEXT_RPG Struct with given params.
 * @param pName Program name
 * @return pointer to created CONTEXT_RPG struct or NULL if some error occured
 * while init.
 */
CONTEXT_RPG *init_RPG(char *pName)
{
    CONTEXT_RPG *gContext = (CONTEXT_RPG *)malloc(sizeof(CONTEXT_RPG));
    if (gContext == NULL)
    {
        // malloc sets errno.
        return NULL;
    }
    gContext->pName = (char *)malloc(sizeof(char) * 20);
    if (gContext->pName == NULL)
    {
        // malloc sets errno.
        return NULL;
    }
    if (pName == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    strncpy(gContext->pName, "C_RPG", sizeof(gContext->pName));
    return gContext;
}

/**
 * For Destorying CONTEXT_RPG, is only called via.
 * CONTEXT_RPGE*->fdestroyPContextPtr.
 * @param pContext CONTEXT_RPG as void pointer
 */
void destory_VOID_CONTEXT_RPG(void *pContext)
{
    CONTEXT_RPG *context = (CONTEXT_RPG *)pContext;
    destory_CONTEXT_RPG(context);
}

/**
 * Destorying CONTEXT_RPG.
 * @param pContext CONTEXT_RPG pointer to get freed
 */
void destory_CONTEXT_RPG(CONTEXT_RPG *gContext)
{
    free(gContext->pName);
    free(gContext);
}