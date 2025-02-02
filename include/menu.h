#ifndef MENU
#define MENU
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "util.h"

// ---- CONSTANTS ----
extern const int GLOBAL_UI_SIZE;

// -------- UI-MENU-SYSTEM --------
// Determines if ui elment needs to be rendered or not;
enum UIRenderMode {
    UI_SHOW, 
    UI_HIDE
};

// Determines if logic for ui needs to updated;
enum UISelectMode {
    UI_ACTIVE,
    UI_INACTIVE
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

// maybe linked list bauen? kommt drauf an.
typedef struct {
    // global is constant.
    UIElement* globalUI[10];
    // local is dynamic.
    // or adjustable. 
    // TODO: decite best approche
    UIElement* localUI[10];
    int countLocalUIEls;
} MenuState;

#endif