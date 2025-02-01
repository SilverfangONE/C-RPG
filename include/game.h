#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	

// ---- CONSTANTS ----
extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int NES_PIXEL_WIDTH;
extern const int NES_PIXEL_HEIGHT;
extern const int TILE_PIXEL_SIZE_B;
extern const int TILE_PIXEL_SIZE_S;
extern const int TARGET_FPS;
extern const int TILES_X;
extern const int TILES_Y;
extern const int TILE_COUNT;
extern const int TILE_SIZE;

// -------- STRUCTS --------
// ---- GAME RENDER ----
typedef struct {
	SDL_Texture* texture;
	int width;
	int height;
	int scaleX;
	int scaleY;
	SDL_FRect destRect;
} Display;

enum RoomType{
	MENU,
	WORLD,
	COMBAT
};

typedef struct {
	SDL_Texture* tileset;
	enum RoomType type;
	char* tilesetPath;
} Room;

// ---- GAME SYSTEM ----
typedef struct {
	Room room;
	Display display;
	SDL_Window* window;
	SDL_Renderer* renderer;
} GameState;

// -------- FUNCTIONS --------
// ---- LOAD/DESTROY SYSTEMS ----
void loadGame(GameState**);
void loadRoom(GameState*, char*, enum RoomType);
void loadDisplay(GameState*);

void exitGame(GameState*);
void destoryRoom(Room*);
void destoryDisplay(Display*);
void destoryGameState(GameState*);

// ---- GAME SYSTEM ----
void processEventsSDL(GameState*);
void loopGame(GameState*);
void updateGame(GameState*);

// ---- GAME RENDER ---- 
void renderGame(GameState*);
void renderTile(GameState*, SDL_Texture*, int, int, int);

// ---- PRINT STRUCTS ----
void printGameState(GameState*);
void printDisplay(Display*);
void printRoom(Room*);
char* printRoomType(enum RoomType);

#endif