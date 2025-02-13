#include "RPGE_E_runner.h"
#include "RPGE_E_context.h"
#include "RPGE_E_system_infos.h"
#include "RPG_context.h"
#include "RPG_core.h"

const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int TARGET_FPS = 60;

int main() {
    CONTEXT_RPG* pContext = init_RPG();
    CONTEXT_RPGE* eContext = init_RPGE(
        &update,
        &render,
        &destory_VOID_CONTEXT_RPG,
        pContext,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SNES,
        pContext->gName
    );
    run_RPGE(TARGET_FPS, eContext);
    return 0;
}