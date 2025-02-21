#include "RPGE_E_context.h"
#include "RPGE_E_runner.h"
#include "RPGE_E_system_infos.h"
#include "RPGE_UI_dialog.h"
#include "RPGE_UI_label.h"
#include "RPG_context.h"
#include "RPGE_EDIT_core.h"
#include "RPGE_EDIT_context.h"
#include "log.h"
#include <errno.h>
#include <stdlib.h>

const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int TARGET_FPS = 60;

void onError()
{
    log_error("EXIT MAIN[ERROR]: \n\tValue of errno: %d\n\tError message: %s", errno, strerror(errno));
}

int main()
{
    log_set_level(LOG_TRACE);
    // setup.
    CONTEXT_EDIT *pContext = init_EDIT("Editor C_RPG");
    if (pContext == NULL)
    {
        onError();
        return EXIT_FAILURE;
    }
    CONTEXT_RPGE *eContext = init_RPGE(&update_EDIT, &render_EDIT, &destory_VOID_CONTEXT_EDIT, pContext, WINDOW_WIDTH,
                                       WINDOW_HEIGHT, SNES, pContext->pName, "./res/assets/engine/json/font.json",
                                       "./res/assets/engine/json/menu.json", TARGET_FPS);
    if (eContext == NULL)
    {
        onError();
        return EXIT_FAILURE;
    }
    // setup.

    pContext->label =
        build_Label_UI_RPGE(eContext->defaultFont, eContext->menuAsset, "Hallo das hier ist ein Editor", (Vec2D){10, 10});
    // configure timer
    setTimerSec_TIME_RPGE("pText", 10);

    // start.
    run_RPGE(eContext);

    // clean up.
    destory_Label_UI_RPGE(pContext->label);
    return 0;
}