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