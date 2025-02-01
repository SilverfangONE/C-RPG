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
extern const int TILESET_SLOT_SIZE;
// KEIN USECASE DAFÜR:
// const int TILE_SIZE_ARR

// -------- STRUCTS --------
// ---- GAME RENDER ----
enum GameObjTypes {
	PLAYER,
	ITEMS,	
};

enum textureTypes {
	STATIC,
	ANIMATION
};

typedef struct {
	SDL_Texture* spriteset;
	int spritesX; // cols of spritesheet
	int spirtesY; // rows of spritesheet
} GameObj;


typedef struct {
	SDL_Texture* texture;
	int width;
	int height;
	float scaleX;
	float scaleY;
	SDL_FRect destRect;
} Display;

/* bis jetzt noch kein use case dafür.
enum Tilesize {
	TILE_SIZE_SMALL,
	TILE_SIZE_BIG
};
*/

typedef struct {
	unsigned int ID;
	SDL_Texture* tileset;
	char textPath[50];
	int sizeX;
	int sizeY;
} Tileset;

enum RoomType{
	MENU,
	WORLD,
	COMBAT
};

typedef struct {
	unsigned int ID;
	enum RoomType type;
	Tileset* tileset;
} Room;

// ---- GAME SYSTEM ----
typedef struct {
	Tileset* sets[4]; // cann hold for tilessets in memory (vorerst) TILE_SLOT_SIZE
	Room room;
	Display display;
	SDL_Window* window;
	SDL_Renderer* renderer;
} GameState;

// -------- FUNCTIONS --------
// ---- LOAD/DESTROY SYSTEMS ----
GameState* loadGame();
void loadRoom(GameState*, char*, enum RoomType);
void loadDisplay(GameState*);
void loadTileset(GameState*);

void exitGame(GameState*);
void destoryRoom(Room*);
void destoryTileset(Tileset*);
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