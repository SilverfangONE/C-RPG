#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL3/SDL.h>	
#include "game_components.h"

// -------- FUNCTIONS --------
void renderTileFromRoom(GameState* game, int tileIndex, int x, int y);
void renderGame(GameState* game);

#endif