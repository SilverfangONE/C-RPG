#include "menu.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "util.h"

// ---- CONSTANTS ----
// TODO adjust wenn cap size of menu elements is known for 
// global-UI, ROOMS have theier own LOCAL-UI;
const int UI_ELEMENT_SLOT_SIZE = 10;

// -------- UI-MENU-SYSTEM --------
void createMenuState(GameState* game) {
    MenuState* menu = malloc(sizeof(MenuState)); 
}

void destroyMenuState(GameState* game) {
    destoryLocalUI(game);
    destroyGlobalUI(game);
    free(game->menu);
}


void loadLocalUIForRoom(GameState* game, unsigned int ids[], int id_size) {
    // Handle ui switch.
} 

void destoryLocalUI(GameState* game) {

}

void loadGobalUI(GameState* game) {

}

void destroyGlobalUI(GameState* game) {

}


void createTextBox() {

}

void renderText() {

}