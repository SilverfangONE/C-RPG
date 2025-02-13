#include <stdbool.h>
#include "log.h"
#include "RPG_core.h"
#include "RPGE_E_context.h"
#include "RPG_context.h"

bool update(CONTEXT_RPGE *eContext) {
    CONTEXT_RPG* pContext = (CONTEXT_RPG*)eContext->pContext;
    log_trace("update from rpg context.");
}

bool render(CONTEXT_RPGE *eContext ) {
    CONTEXT_RPG* pContext = (CONTEXT_RPG*)eContext->pContext;
    log_trace("render from rpg context.");
}