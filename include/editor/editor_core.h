// %%%%%% EDITOR for Tilemaps %%%%%%%
#ifndef EDITOR
#define EDITOR
#include <SDL3/SDL.h>	
#include "game_components.h"
#include "game_util.h"

// &&&& MENU &&&&
struct Courser {
    int x;
    int y;
    int tileIndex;
};

struct MenuUI {
    bool active;
    struct Courser courser;
    char* charBuffer8bit;
    char* charBuffer16bit;
    Matrix* charLayer8bit;
    Matrix* charLayer16bit;
    Matrix* tilesheetLayer;
    void (*update)(EditorContext* context, struct MenuUI* menu);
    void (*render)(EditorContext* context, struct MenuUI* menu);
    SDL_Texture* texture;
    int sizeTileX;
    int sizeTileY;
};

struct MenuLayerStackItem {
    struct MenuLayerStackItem* next;
    struct MenuUI* ui;
};

struct MenuLayerStack {
    int size;
    struct MenuLayerStackItem* top;
};

// &&&& EDITOR CONTEXT &&&&

struct Settings {
    int tileSizeX;
    int tileSizeY;
    char* pathJSON;
    char* tilesheetPath;
    char* spritesheetPath;
};

typedef struct EditorContext {
    struct MenuLayerStack menuStack;
    struct Settings settings;
    SDL_Window* window;
	SDL_Renderer* renderer;
    Display* display;
    Keymap keymap;
} EditorContext;


void processEditorEventsSDL(EditorContext* context);
int main();
void update(EditorContext* context);
void render(EditorContext* context);
void terminate(EditorContext* context);

#endif