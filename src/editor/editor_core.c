// %%%%%% EDITOR for Tilemaps %%%%%%%
#include "editor.h"
#include "log.h"
#include <stdlib.h>

// Process SDL_EVENTSvoid processEventsSDL(contextState* context) 
void processEditorEventsSDL(EditorContext* context) {
    resetKeymapExceptPressed(&context->keymap);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                terminate(context);
            }
            break;
            case SDL_EVENT_KEY_UP: 
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    context->keymap.pressedUP = false;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    context->keymap.pressedDOWN = false;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    context->keymap.pressedLEFT = false;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    context->keymap.pressedRIGHT = false;
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
                    context->keymap.up = true;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    context->keymap.down = true;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    context->keymap.left = true;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    context->keymap.right = true;
                    break;
                case SDL_SCANCODE_RETURN:
                    log_trace("KEY:ENTER");
                    context->keymap.enter = true;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    log_trace("KEY:ESCAPE");
                    context->keymap.esc = true;
                }
            }
        }
    }
}

void update(EditorContext* context) {
    // TODO.
}

void render(EditorContext* context) {
    // render grid;
    // render tilesheet;
    // render menu stack;
    
    // TODO.
}

void renderMenuStack(struct MenuLayerStackItem* item) {
    if(item->next != NULL) {
        renderMenuStack(item->next);
    }
    // render from bottoum to top.

}

void renderMenuUI(struct MenuUI* ui) {
    
}

/* Terminates Editor Context*/
void terminate(EditorContext* context) {
    SDL_DestroyWindow(context->window);
    SDL_DestroyRenderer(context->renderer);
    destroyDisplay(context->display);
    SDL_Quit();
    free(context);
}

// &&&& Load and Destory &&&&
void loadSettingsFromEnvJSON(EditorContext* context) {
    return;
}  
