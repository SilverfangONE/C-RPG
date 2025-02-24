#ifndef RPGE_E_KEYMAP
#define RPGE_E_KEYMAP

#include <stdbool.h>

typedef struct Keymap_RPGE {
    bool up;
    bool down;
    bool left;
    bool right;
    bool enter;
    bool esc;
    bool pressedUP;
    bool pressedDOWN;
    bool pressedLEFT;
    bool pressedRIGHT;
} Keymap_RPGE;

void reset_Keymap_RPGE(Keymap_RPGE*);
void resetAll_Keymap_RPGE(Keymap_RPGE*);
Keymap_RPGE* create_Keymap_RPGE();
void destroy_Keymap_RPGE(Keymap_RPGE*);

#endif