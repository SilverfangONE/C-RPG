#include "RPG_core.h"
#include "RPGE_E_context.h"
#include "RPG_context.h"
#include "log.h"
#include <stdbool.h>
#include <stdlib.h>
#include "RPGE_UI_label.h"
#include "RPGE_E_system_infos.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_UI_dialog.h"

bool update_RPG(CONTEXT_RPGE *eContext)
{
    CONTEXT_RPG *pContext = (CONTEXT_RPG *)eContext->pContext;
    // update.
    update_Dialog_UI_RPGE(pContext->dialog, eContext->keymap);
    return 0;
}


static int render_TestIMG(CONTEXT_RPGE *eContext) {
    SDL_FRect srcR;
    srcR.w = 8;
    srcR.h = 8;
    srcR.x = (7 % 6) * 8;
    srcR.y = (7 / 6) * 8;

    SDL_FRect destR;
    destR.w = 8;
    destR.h = 8;
    destR.x = 0;
    destR.y = 0;

    SDL_RenderTexture(eContext->renderer, eContext->menuAsset->imgText, &srcR, &destR);
    return 0;
}

bool render_RPG(CONTEXT_RPGE *eContext)
{
    CONTEXT_RPG *pContext = (CONTEXT_RPG *)eContext->pContext;
    // render.
    // render_TestIMG(eContext);
    int indexCounter = 0;
    for (int yTile = 0; yTile < eContext->display->height / 8; yTile++) {
        for (int xTile = 0; xTile < eContext->display->width / 8; xTile++) {
            if (indexCounter > 96) indexCounter = 0;
            renderTile_Assetsheet_G_RPGE(
                eContext->renderer, 
                eContext->defaultFont, 
                indexCounter++, 
                (Vec2D) {.x=xTile*8, .y=yTile*8}
            );
        }
    }    
    render_Label_UI_RPGE(eContext->renderer, pContext->label);
    render_Dialog_UI_RPGE(eContext->renderer, pContext->dialog);
    return 0;
}