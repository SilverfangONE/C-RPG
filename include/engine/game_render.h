#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL3/SDL.h>	
#include "game_components.h"
#include "game_util.h"

// -------- FUNCTIONS --------
void renderGame(GameState* game);
void renderMatrixMap(GameState* game, Matrix* matrix, TextureAtlas* atlas);
void renderTextureFromAtlas(GameState* game, TextureAtlas* atlas, int tileIndex, int x, int y);
void renderEnviromentStack(GameState* game, struct EnviromentStackItem* item);

#endif