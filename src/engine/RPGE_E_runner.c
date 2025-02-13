#include <stdlib.h>
#include <time.h>
#include "RPGE_E_runner.h"
#include "RPGE_E_context.h"
#include "RPGE_E_keymap.h"

#ifdef _WIN32
    #include <windows.h>
#else 
    #include <unistd.h>
#endif

void sleep_ms(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

/**
 * entry point of RPG-Engine
 */
int run_RPGE(
    const int TARGET_FPS,
    CONTEXT_RPGE *eContext
) {
    // setup.
    int run = 1;
    int FRAME_TIME = 1000 / TARGET_FPS;
    while (run) {
        clock_t start_time = clock();
        processEventsSDL(eContext);
        eContext->fupdatePtr(eContext);
        eContext->frenderPtr(eContext);
        clock_t end_time = clock();
        double elapsed_ms = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC; 
        if(elapsed_ms < FRAME_TIME) {
            sleep_ms(FRAME_TIME - (int)elapsed_ms);
        }
    }
    return 0;
}

void processEventsSDL(CONTEXT_RPGE* eContext) 
{
    reset_Keymap_RPGE(eContext->keymap);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                terminateEngine(eContext);
            }
            break;
            case SDL_EVENT_KEY_UP: 
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    eContext->keymap->pressedUP = false;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    eContext->keymap->pressedDOWN = false;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    eContext->keymap->pressedLEFT = false;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    eContext->keymap->pressedRIGHT = false;
                }
            }
            break;
            case SDL_EVENT_KEY_DOWN:
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    eContext->keymap->up = true;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    eContext->keymap->down = true;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    eContext->keymap->left = true;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    eContext->keymap->right = true;
                    break;
                case SDL_SCANCODE_RETURN:
                    log_trace("KEY:ENTER");
                    eContext->keymap->enter = true;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    log_trace("KEY:ESCAPE");
                    eContext->keymap->esc = true;
                }
            }
        }
    }
}