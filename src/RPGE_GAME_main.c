#include <errno.h>
#include <stdlib.h>
#include "log.h"
#include "RPGE_E_runner.h"
#include "RPGE_E_context.h"
#include "RPGE_E_system_infos.h"
#include "RPG_context.h"
#include "RPG_core.h"

const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int TARGET_FPS = 60;

void onError() {
    log_error("EXIT MAIN[ERROR]: \n\tValue of errno: %d\n\tError message: %s", errno, strerror(errno));
}

int main() {
    // setup.
    CONTEXT_RPG* pContext = init_RPG("C_RPG");
    if (pContext == NULL) {
        onError();
        return EXIT_FAILURE;
    }
    CONTEXT_RPGE* eContext = init_RPGE(
        &update_RPG,
        &render_RPG,
        &destory_VOID_CONTEXT_RPG,
        pContext,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SNES,
        pContext->pName
    );
    if (eContext == NULL) {
        onError();
        return EXIT_FAILURE;
    }
    // start.
    run_RPGE(TARGET_FPS, eContext);
    return 0;
}