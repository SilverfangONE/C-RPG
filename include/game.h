#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	

typedef struct {
	
} GameState;

int processEvents(SDL_Window*, GameState*);
void load(SDL_Window*, SDL_Renderer*, GameState*);
void exitGame(SDL_Window* window, GameState* gameState);

// ROOM SYSTEM
typedef struct {
	int x;
	int y;
} GameObj;

typedef enum {
	MENU,
	WORLD,
	COMBAT
} RoomType;

typedef struct {
	long long id;
	char* tilesetPath;
	int** tilesetMap;
	RoomType type;
} Room;

Room* loadRoom();

#endif