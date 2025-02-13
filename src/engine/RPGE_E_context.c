#include <stdlib.h>
#include "log.h"
#include "RPGE_E_context.h"
#include "RPGE_E_display.h"
#include "RPGE_E_keymap.h"
#include "RPGE_E_system_infos.h"

/**
 * Creates CONTEXT_RPGE Struct with given params.
 * @param fupdatePtr Pointer to update function
 * @param frenderPtr Poitner to render function
 * @param pContext Pointer to program context struct
 * @param WINDOW_WIDTH Size of Windowwidth in pixel
 * @param WINDOW_HEIGHT Size of Windowheight in pixel
 * @param system Target system for resolution of display
 * @param pName Program name
 * 
 * @return pointer to created CONTEXT_RPGE struct or NULL if some error occured while init.
 */
CONTEXT_RPGE* init_RPGE ( 
    bool (*fupdatePtr)(struct CONTEXT_RPGE *eContext),
    bool (*frenderPtr)(struct CONTEXT_RPGE *eContext),
    void (*fdestroyPContextPtr)(void* pContext),
    void* pContext,
    const int WINDOW_WIDTH,
    const int WINDOW_HEIGHT,
    enum SYSTEM_RPGE system,
    const char* pName
) {
    CONTEXT_RPGE* eContext = (CONTEXT_RPGE*)malloc(sizeof(CONTEXT_RPGE));
    if (eContext == NULL) {
        return NULL;
    }
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_CreateWindowAndRenderer(
        pName,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        &eContext->window,
        &eContext->renderer
    )) {
        log_error("%s", SDL_GetError());
        return NULL;
    }
    eContext->display = create_Display_RPGE(
        eContext->renderer,
        system,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );  
    if (eContext->display == NULL) {
        return NULL;
    }
    eContext->keymap = create_Keymap_RPGE();
    if (eContext->keymap == NULL) {
        return NULL;
    }
    if (eContext->frenderPtr == NULL || eContext->fdestroyPContextPtr == NULL || eContext->fupdatePtr == NULL) {
        return NULL;
    }
    return eContext;
}

/**
 * Terminates RPG-ENGINE by freeing allocated memory for CONTEXT_RPGE form heap in right order.
 * @param eContext Context from RPG-ENGINE
 */
void terminate_RPGE(CONTEXT_RPGE* eContext) {
    log_debug("Exit RPG-ENGINE ...");
    eContext->fdestroyPContextPtr(eContext->pContext);
    destroy_Keymap_RPGE(eContext->keymap);
    destroy_Display_RPGE(eContext->display);
    SDL_DestroyWindow(eContext->window);
    SDL_DestroyRenderer(eContext->renderer);
    SDL_Quit();
    free(eContext);
}