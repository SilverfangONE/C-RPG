#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	
#include "cJSON.h"
#include "game_components.h"


GameState* loadGame();
void exitGame(GameState*);

// ---- GAME SYSTEM ----
void loopGame(GameState*);
void updateGame(GameState*);

// ---- GAME RENDER ---- 
void renderGame(GameState*);

// ---- SMOKE-TEST ----
void smokeTestIMGRender(GameState* game);

#endif