#include <stdbool.h>
#include "log.h"
#include "RPGE_E_context.h"
#include "RPGE_EDIT_core.h"

/**
 * @return if true is returned the program loop should stop, false it can go on.
 */
bool update_EDITOR(CONTEXT_RPGE* eContext) {
    log_trace("UPDATE: EDITOR_CONTEXT");
    return false;
}

/**
 * @return if true is returned the program loop should stop, false it can go on.
 */
bool render_EDITOR(CONTEXT_RPGE* eContext) {
    log_trace("UPDATE: EDITOR_CONTEXT");
    return false;
}