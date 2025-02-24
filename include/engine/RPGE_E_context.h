#ifndef RPGE_E_CONTEXT
#define RPGE_E_CONTEXT

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include "RPGE_E_display.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_E_keymap.h"
#include "RPGE_E_time.h"

/**
 * Global Context for the RPG-ENGINE
 */
typedef struct CONTEXT_RPGE {
    /**
     * @return if true is returned the program loop should stop, false it can go on.
     */
    bool (*fupdatePtr)(struct CONTEXT_RPGE *eContext);
    /**
     * @return if true is returned the program loop should stop, false it can go on.
     */
    bool (*frenderPtr)(struct CONTEXT_RPGE *eContext);
    void (*fdestroyPContextPtr)(void* pContext);
    void* pContext;
    Keymap_RPGE* keymap;
    Display_RPGE* display;
    SDL_Window* window;
    SDL_Renderer* renderer;  
    // resouces.
    Assetsheet_RPGE* defaultFont;
    Assetsheet_RPGE* menuAsset;
    // timer
    TimerManager_TIME_RPGE* timeManager;
    int _TARGET_FPS;
} CONTEXT_RPGE;

void terminate_RPGE(CONTEXT_RPGE* eContext, int);
CONTEXT_RPGE* init_RPGE ( 
    bool (*fupdatePtr)(struct CONTEXT_RPGE *eContext),
    bool (*frenderPtr)(struct CONTEXT_RPGE *eContext),
    void (*fdestroyPContextPtr)(void* pContext),
    void* pContext,
    const int WINDOW_WIDTH,
    const int WINDOW_HEIGHT,
    enum SYSTEM_RPGE system,
    const char* pName,
    const char* defaultFontPathJSON,
    const char* defaultMenuPathJSON,
    int TARGET_FPS
);
#endif