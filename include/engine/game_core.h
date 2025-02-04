#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	
#include "cJSON.h"
#include "game_components.h"


GameState* loadGame();
void exitGame(GameState*);

// ---- GAME SYSTEM ----
Tileset** getTilesetSaveSlot(GameState* );
Tileset* lookupTileset(GameState* , unsigned int);
void processEventsSDL(GameState*);
void loopGame(GameState*);
void updateGame(GameState*);

// ---- GAME RENDER ---- 
void renderGame(GameState*);
void renderTileFromRoom(GameState*, int, int, int);

// ---- PRINT STRUCTS ----
void printTileset(Tileset*);
void printGameState(GameState*);
void printDisplay(Display*);
void printRoom(Room*);
char* printRoomType(enum RoomType);

// ---- SMOKE-TEST ----
void smokeTestIMGRender(GameState* game);

#endif