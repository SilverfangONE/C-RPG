#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL3/SDL.h>	
#include "game_components.h"

// -------- FUNCTIONS --------
void renderTileFromRoom(GameState* game, int tileIndex, int x, int y);
void renderGame(GameState* game);
Tileset* lookupTileset(GameState* game, unsigned int tilesetID);
Tileset** getTilesetSaveSlot(GameState* game);

// ---- LOAD/DESTROY SYSTEMS ----
void loadTileset(GameState* game, char* tilesetTexturePath, int tileSizeX, int tileSizeY, int cols, int rows, unsigned int ID);
void loadDisplay(GameState* game);
void destroyUIElement(struct UIElement* uiEl);
void destroyDisplay(Display* display);
void destroyTilesheet(Tilesheet *tilesheet);
void destroySpritesheet(Spritesheet*);

#endif