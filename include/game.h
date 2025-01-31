#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	

// ---- CONSTANTS ----
extern const int NES_PIXEL_WIDTH;
extern const int NES_PIXEL_HEIGHT;
extern const int TILE_PIXEL_SIZE_B;
extern const int TILE_PIXEL_SIZE_S;
extern const int TARGET_FPS;
extern const int TILES_X;
extern const int TILES_Y;
extern const int TILE_COUNT;
extern const int TILE_SIZE;

// ---- ROOM SYSTEM ----
typedef struct {
	int x;
	int y;
} GameObj;

enum RoomType{
	MENU,
	WORLD,
	COMBAT
};

typedef struct {
	long long id;
	SDL_Texture* tilesheet;
	enum RoomType type;
} Room;

Room loadRoom(SDL_Renderer* renderer, char* imgPath);

// ---- GAME SYSTEM ----
typedef struct {
	Room* currentRoom;
} GameState;

void processEvents(GameState*, SDL_Window*);
void loadGame(GameState*, SDL_Window*, SDL_Renderer*);
void exitGame(GameState*, SDL_Window*);
void loopGame(GameState*, SDL_Window*, SDL_Renderer*);
void updateGame(GameState*);
void renderGame(GameState*, SDL_Window*, SDL_Renderer*);

#endif