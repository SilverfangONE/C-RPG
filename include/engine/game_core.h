#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	
#include "game_components.h"

// ---- LOAD/DESTROY SYSTEMS ----
GameState* loadGame();
void loadRoom(GameState* , enum RoomType, unsigned int, unsigned int);
void loadDisplay(GameState*);
void loadTileset(GameState* , char* , int , int , int , int , unsigned int);

void exitGame(GameState*);
void destoryRoom(Room*);
void destoryTileset(Tileset*);
void destoryDisplay(Display*);
void destoryGameState(GameState*);
void destroySub(struct Sub*);
void destroyMap(struct Map*);

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