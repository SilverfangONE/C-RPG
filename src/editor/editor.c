// %%%%%% EDITOR for Tilemaps %%%%%%%
#include "editor.h"
#include "log.h"
#include <stdlib.h>

const int EDITOR_WINDOW_HEIGHT = 1200;
const int EDITOR_WINDOW_WIDTH = 1200;

int main() {
    // Setup
    SDL_Init(SDL_INIT_VIDEO);
    EditorContext* context = (EditorContext*)malloc(sizeof(EditorContext));
    if(!SDL_CreateWindowAndRenderer(
        "Editor",
        EDITOR_WINDOW_WIDTH,
        EDITOR_WINDOW_HEIGHT,
        0,
        &context->window,
        &context->renderer
    )) {
        log_error("%s", SDL_GetError());
        terminate(context);
    }
    resetKeymap(&context->keymap);
    context->display = createDisplay(
        context->renderer,
        SNES_PIXEL_WIDTH,
        SNES_PIXEL_HEIGHT,
        EDITOR_WINDOW_WIDTH,
        EDITOR_WINDOW_HEIGHT
    );
    context->menuStack.size = 0;
    context->menuStack.top = NULL;
    // Program loop
    int run = 1;
    while(run) {
        processEditorEventsSDL(context);
        update(context);
        render(context);
    }
    terminate(context);
    return 0;
}

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
