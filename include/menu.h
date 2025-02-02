#ifndef MENU
#define MENU
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "util.h"

// ---- CONSTANTS ----
extern const int UI_ELEMENT_SLOT_SIZE;

// -------- UI-MENU-SYSTEM --------
// Determines if ui elment needs to be rendered or not;
enum UIRenderMode {
    SHOW, 
    HIDE
};

// Determines if logic for ui needs to updated;
enum UISelectMode {
    ACTIVE,
    INACTIVE
};

typedef struct {
    // build menu tile set;
    SDL_Texture* renderedTilemap;
    Tileset* tileset;
    enum UISelectMode selectMode;
    enum UIRenderMode renderMode;
    int x;
    int y;
    int w;
    int h;
    // tilemap for menu element;
    DynamicMatrix* tilemap;
} UIElement ;

typedef struct {
    UIElement* uiEls[10];
} MenuState;

#endif