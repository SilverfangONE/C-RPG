#include "RPGE_E_context.h"
#include "RPGE_E_display.h"
#include "RPGE_E_keymap.h"
#include "RPGE_E_system_infos.h"
#include "RPGE_E_time.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_JSON_assetsheet.h"
#include "log.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

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
 * @return pointer to created CONTEXT_RPGE struct or NULL if some error occured
 * while init.
 */
CONTEXT_RPGE *init_RPGE(bool (*fupdatePtr)(struct CONTEXT_RPGE *eContext),
                        bool (*frenderPtr)(struct CONTEXT_RPGE *eContext), void (*fdestroyPContextPtr)(void *pContext),
                        void *pContext, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, enum SYSTEM_RPGE system,
                        const char *pName, const char *defaultFontPathJSON, const char *defaultMenuPathJSON,
                        int TARGET_FPS)
{
    CONTEXT_RPGE *eContext = (CONTEXT_RPGE *)malloc(sizeof(CONTEXT_RPGE));
    if (eContext == NULL)
        return NULL;
    if (pContext == NULL)
    {
        log_error("init_RPGE(): pContext%s is invalid", pContext);
        errno = EINVAL;
        return NULL;
    }
    eContext->pContext = pContext;

    SDL_Init(SDL_INIT_VIDEO);
    if (!SDL_CreateWindowAndRenderer(pName, WINDOW_WIDTH, WINDOW_HEIGHT, 0, &eContext->window, &eContext->renderer))
    {
        log_error("%s", SDL_GetError());
        return NULL;
    }

    Display_RPGE *display = create_Display_RPGE(eContext->renderer, system, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (display == NULL)
        return NULL;
    eContext->display = display;

    Keymap_RPGE *keymap = create_Keymap_RPGE();
    if (keymap == NULL)
        return NULL;
    eContext->keymap = keymap;

    if (frenderPtr == NULL)
    {
        log_error("init_RPGE(): frenderPtr%s is invalid", frenderPtr);
        errno = EINVAL;
        return NULL;
    }
    eContext->frenderPtr = frenderPtr;

    if (fupdatePtr == NULL)
    {
        log_error("init_RPGE(): fupdatePtr%s is invalid", fupdatePtr);
        errno = EINVAL;
        return NULL;
    }
    eContext->fupdatePtr = fupdatePtr;

    if (fdestroyPContextPtr == NULL)
    {
        log_error("init_RPGE(): fdestroyPContextPtr%s is invalid", fdestroyPContextPtr);
        errno = EINVAL;
        return NULL;
    }
    eContext->fdestroyPContextPtr = fdestroyPContextPtr;

    if (TARGET_FPS < 1)
    {
        log_error("init_RPGE(): TARGET_FPS { %d } is invalid", TARGET_FPS);
        errno = EINVAL;
        return NULL;
    }
    eContext->_TARGET_FPS = TARGET_FPS;

    // load default ressouces
    eContext->defaultFont = load_Assetsheet_JSON_RPGE(eContext->renderer, defaultFontPathJSON);
    if (eContext->defaultFont == NULL)
        return NULL;
    eContext->menuAsset = load_Assetsheet_JSON_RPGE(eContext->renderer, defaultMenuPathJSON);
    if (eContext->menuAsset == NULL)
        return NULL;

    // Time Manager.
    eContext->timeManager = _create_TimerManager_TIME_RPGE();
    INIT_TIME_RPGE(eContext->timeManager, eContext->_TARGET_FPS);
    log_debug("[Created CONTEXT_RPGE]");
    return eContext;
}

/**
 * Terminates RPG-ENGINE by freeing allocated memory for CONTEXT_RPGE form heap
 * in right order.
 * @param eContext Context from RPG-ENGINE
 */
void terminate_RPGE(CONTEXT_RPGE *eContext, int _Code)
{
    eContext->fdestroyPContextPtr(eContext->pContext);
    destroy_Keymap_RPGE(eContext->keymap);
    destroy_Display_RPGE(eContext->display);
    SDL_DestroyWindow(eContext->window);
    SDL_DestroyRenderer(eContext->renderer);
    SDL_Quit();
    free(eContext->timeManager);
    free(eContext);
    switch (_Code)
    {
    case EXIT_FAILURE:
        log_error("Terminated[EXIT_FAILURE] RPG-ENGINE:\n\tValue of errno: "
                  "%d\n\t Error message: %s",
                  errno, strerror(errno));
        exit(_Code);
    case EXIT_SUCCESS:
        log_info("Terminated[EXIT_SUCCESS] RPG-ENGINE ...", _Code);
        break;
    default:
        log_warn("Terminated[Unknown] RPG-ENGINE ...", _Code);
        break;
    }
}