#include "RPGE_E_runner.h"
#include "RPGE_E_context.h"
#include "RPGE_E_keymap.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "RPGE_E_time.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void sleep_ms(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

/**
 * Entry point of RPG-Engine.
 * @return returns 0, but will never be reached because of terminate_RPGE()
 */
int run_RPGE(const int TARGET_FPS, CONTEXT_RPGE *eContext)
{
    log_info("Start RPG-ENGINE ...");
    int FRAME_TIME = 1000 / TARGET_FPS;
    init_TIME_RPGE(TARGET_FPS);
    while (true)
    {
        clock_t start_time = clock();
        // excute engine logics.
        if (processEventsSDL(eContext))
            break;
        if (_update_RPGE(eContext))
            break;
        if (_render_RPGE(eContext))
            break;
        clock_t end_time = clock();
        double elapsed_ms = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
        if (elapsed_ms < FRAME_TIME)
        {
            sleep_ms(FRAME_TIME - (int)elapsed_ms);
        }
        _update_TIME_RPGE();
    }
    return 0;
}

/**
 * @return if true is returned the program loop should stop, false it can go on.
 */
bool processEventsSDL(CONTEXT_RPGE *eContext)
{
    reset_Keymap_RPGE(eContext->keymap);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
            terminate_RPGE(eContext, EXIT_SUCCESS);
            return true;
        }
        break;
        case SDL_EVENT_KEY_UP: {
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
        case SDL_EVENT_KEY_DOWN: {
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
                terminate_RPGE(eContext, EXIT_SUCCESS);
                return true;
            }
        }
        }
    }
    return false;
}

int _update_RPGE(CONTEXT_RPGE *eContext)
{
    return eContext->fupdatePtr(eContext);
}

int _render_RPGE(CONTEXT_RPGE *eContext)
{
    // clear window.
    if (!SDL_RenderClear(eContext->renderer))
    {
        log_error("%s", SDL_GetError());
        return 1;
    }

    // render on display.
    SDL_SetRenderTarget(eContext->renderer, eContext->display->texture);

    // clear display.
    if (!SDL_RenderClear(eContext->renderer))
    {
        log_error("%s", SDL_GetError());
        return 1;
    }

    // invoke program render fun.
    if (eContext->frenderPtr(eContext))
    {
        return 1;
    }

    // render on window.
    SDL_SetRenderTarget(eContext->renderer, NULL);
    if (!SDL_RenderTexture(eContext->renderer, eContext->display->texture, NULL, &eContext->display->destRect))
    {
        log_error("%s", SDL_GetError());
    }

    // switch buffer.
    SDL_RenderPresent(eContext->renderer); // updates the renderer
    return 0;
}