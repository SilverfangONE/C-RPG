#include "RPGE_E_keymap.h"

void reset_Keymap_RPGE(Keymap_RPGE* keymap) {
    keymap->down = false;
    keymap->up = false;
    keymap->left = false;
    keymap->right = false;
    keymap->esc = false;
    keymap->enter = false;
}

void resetAll_Keymap_RPGE(Keymap_RPGE* keymap) {
    keymap->down = false;
    keymap->up = false;
    keymap->left = false;
    keymap->right = false;
    keymap->esc = false;
    keymap->enter = false;
    keymap->pressedDOWN = false;
    keymap->pressedUP = false;
    keymap->pressedLEFT = false;
    keymap->pressedRIGHT = false;
}

Keymap_RPGE* create_Keymap_RPGE() {
    Keymap_RPGE* keymap = malloc(sizeof(Keymap_RPGE));
    resetKeymap(keymap);
    return keymap;
}

void destroy_Keymap_RPGE(Keymap_RPGE* keymap) {
    free(keymap);
}