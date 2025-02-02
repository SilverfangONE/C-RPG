#ifndef MENU
#define MENU

#include "game.h"

enum UIRenderMode {
    OPEN, 
    CLOSED
};

enum UISelectMode {
    ACTIVE,
    INACTIVE
};

typedef struct {
    Tileset* tileset;
    enum UISelectMode selectMode;
    enum UIRenderMode renderMode;
    int x;
    int y;
    int w;
    int h;
    // tilemap for menu element;
    int 
} UIElement ;

#endif