#include "RPGE_E_context.h"
#include "RPGE_E_runner.h"
#include "RPGE_E_system_infos.h"
#include "RPGE_UI_dialog.h"
#include "RPGE_UI_textfield.h"
#include "RPGE_UI_label.h"
#include "RPG_context.h"
#include "RPG_core.h"
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
    CONTEXT_RPG *pContext = init_RPG("C_RPG");
    if (pContext == NULL)
    {
        onError();
        return EXIT_FAILURE;
    }
    CONTEXT_RPGE *eContext = init_RPGE(&update_RPG, &render_RPG, &destory_VOID_CONTEXT_RPG, pContext, WINDOW_WIDTH,
                                       WINDOW_HEIGHT, SNES, pContext->pName, "./res/assets/engine/json/font.json",
                                       "./res/assets/engine/json/menu.json", TARGET_FPS);
    if (eContext == NULL)
    {
        onError();
        return EXIT_FAILURE;
    }
    // create test comps.
    /*
        Dialog_UI_RPGE *dialog = build_Dialog_UI_RPGE(
            eContext->defaultFont, eContext->menuAsset,
            "Das Abenteuer, das RPG-Spiele auf Super Nintendo revolutioniert hat, hat seinen ersten Auftritt in Europa! ",
            (Vec2D){55, 55}, (Vec2D){50, 100});
        pContext->dialog = dialog;
        
        Label_UI_RPGE *label =
        build_Label_UI_RPGE(eContext->defaultFont, eContext->menuAsset, "Hello\n W\norld", (Vec2D){10, 10});
        pContext->label = label;
    */

    TextField_UI_RPGE* textField = build_TextField_UI_RPGE(eContext->defaultFont, "Hello\n W\norld", (Vec2D) {30, 30});
    log_warn("textfield = {'%s'}", textField);
    pContext->textField = textField;

    // configure timer
    setTimerSec_TIME_RPGE(10, 10);

    // start.
    run_RPGE(eContext);

    // clean up.
    destroy_TextField_UI_RPGE(textField);
    // destory_Label_UI_RPGE(label);
    // destory_Dialog_UI_RPGE(dialog);
    return 0;
}