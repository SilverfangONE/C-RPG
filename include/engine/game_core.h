#ifndef GAME
#define GAME

#include "cJSON.h"
#include "game_components.h"
#include <SDL3/SDL.h>

GameState *loadGame ();
void exitGame (GameState *);

// ---- GAME SYSTEM ----
void loopGame (GameState *);
void updateGame (GameState *);

// ---- GAME RENDER ----
void renderGame (GameState *);

// ---- SMOKE-TEST ----
void smokeTestIMGRender (GameState *game);

#endif