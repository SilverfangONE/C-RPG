#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include "log.h"
#include "RPGE_E_display.h"
#include "RPGE_E_keymap.h"
#include "RPGE_E_system_infos.h"
#include "RPGE_E_context.h"

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
        // malloc sets errno.
        return NULL;
    }
    
    if (pContext == NULL) {
        errno = EINVAL;
        return NULL;    
    }
    eContext->pContext = pContext;
    
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
    
    Display_RPGE* display = create_Display_RPGE(
        eContext->renderer,
        system,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );  
    if (display == NULL) {
        return NULL;
    }
    eContext->display = display;
    
    Keymap_RPGE* keymap = create_Keymap_RPGE();
    if (keymap == NULL) {
        return NULL;
    }
    eContext->keymap = keymap;
    
    if (frenderPtr == NULL) {
        errno = EINVAL;
        return NULL;
    }
    eContext->frenderPtr = frenderPtr;
   
    if (fupdatePtr == NULL) {
        errno = EINVAL;
        return NULL;
    }
    eContext->fupdatePtr = fupdatePtr;
    
    if (fdestroyPContextPtr == NULL) {
        errno = EINVAL;
        return NULL;
    }
    eContext->fdestroyPContextPtr = fdestroyPContextPtr;
    return eContext;
}

/**
 * Terminates RPG-ENGINE by freeing allocated memory for CONTEXT_RPGE form heap in right order.
 * @param eContext Context from RPG-ENGINE
 */
void terminate_RPGE(CONTEXT_RPGE* eContext, int _Code) {
    eContext->fdestroyPContextPtr(eContext->pContext);
    destroy_Keymap_RPGE(eContext->keymap);
    destroy_Display_RPGE(eContext->display);
    SDL_DestroyWindow(eContext->window);
    SDL_DestroyRenderer(eContext->renderer);
    SDL_Quit();
    free(eContext);
    switch (_Code) {
        case EXIT_FAILURE: 
            log_error("Terminated[EXIT_FAILURE] RPG-ENGINE:\n\tValue of errno: %d\n\t Error message: %s", errno, strerror(errno));
            exit(_Code);
        case EXIT_SUCCESS:
            log_info("Terminated[EXIT_SUCCESS] RPG-ENGINE ...", _Code);
            break;
        default: 
            log_warn("Terminated[Unknown] RPG-ENGINE ...", _Code);
            break;    
    }
}