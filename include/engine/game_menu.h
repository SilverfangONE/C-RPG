#ifndef GAME_MENU
#define GAME_MENU

typedef struct MenuManager {

} MenuManager;

typedef struct MenuObject {
    char* name;
} MenuObject;

void mmOpen(MenuManager*);
void mmOnUp(MenuManager*);
void mmOnDown(MenuManager*);
void mmOnLeft(MenuManager*);
void mmOnRight(MenuManager*);
void mmOnBack(MenuManager*);
void mmOnConfirm(MenuManager*); // returns command.
void mmDraw(MenuManager*);

#endif