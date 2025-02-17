#ifndef RPGE_E_RUNNER
#define RPGE_E_RUNNER

#include <stdbool.h>
#include "RPGE_E_context.h"
#include "RPGE_E_time.h"

// TODO add timer facilites for debugging in program loop.

int run_RPGE(const int TARGET_FPS, CONTEXT_RPGE *eContext);
bool _processEventsSDL(CONTEXT_RPGE* eContext);
int _update_RPGE (CONTEXT_RPGE* eContext);
int _render_RPGE (CONTEXT_RPGE* eContext);

#endif