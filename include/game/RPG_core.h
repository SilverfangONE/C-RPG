#ifndef RPG_CORE
#define RPG_CORE

#include "RPGE_E_context.h"
#include <stdbool.h>

bool update(struct CONTEXT_RPGE *eContext);
bool render(struct CONTEXT_RPGE *eContext);

#endif