#ifndef GAME_RENDER
#define GAME_RENDER

#include "game_components.h"
#include "game_util.h"
#include <SDL3/SDL.h>

// -------- FUNCTIONS --------
void renderGame (GameState *game);
void renderPlayer (GameState *game, TextureAtlas *atlas);
void renderMatrixMap (GameState *game, Matrix *matrix, TextureAtlas *atlas);
void renderTextureFromAtlas (GameState *game, TextureAtlas *atlas,
                             int tileIndex, int x, int y);
void renderEnviromentStack (GameState *game, struct ENV_StackItem *item);

#endif