#ifndef RPG_CORE
#define RPG_CORE

#include "RPGE_E_context.h"
#include <stdbool.h>

/**
 * @return if true is returned the program loop should stop, false it can go on.
 */
bool update_RPG(struct CONTEXT_RPGE *eContext);
/**
 * @return if true is returned the program loop should stop, false it can go on.
 */
bool render_RPG(struct CONTEXT_RPGE *eContext);

#endif