#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	

// ---- ROOM SYSTEM ----
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

Room* loadRoom(char*);

// ---- GAME SYSTEM ----
typedef struct {
	Room* currentRoom;
} GameState;

int processEvents(GameState*, SDL_Window*);
void loadGame(GameState*, SDL_Window*, SDL_Renderer*);
void exitGame(GameState*, SDL_Window*);
void loopGame(GameState*, SDL_Window*, SDL_Renderer*);
void updateGame(GameState*);
void renderGame(GameState*, SDL_Window*, SDL_Renderer*);

#endif