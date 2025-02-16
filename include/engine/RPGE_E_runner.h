#ifndef RPGE_E_RUNNER
#define RPGE_E_RUNNER

#include <stdbool.h>
#include "RPGE_E_context.h"

int run_RPGE(const int TARGET_FPS, CONTEXT_RPGE *eContext);
bool processEventsSDL(CONTEXT_RPGE* eContext);
int _update_RPGE (CONTEXT_RPGE* eContext);
int _render_RPGE (CONTEXT_RPGE* eContext);

#endif