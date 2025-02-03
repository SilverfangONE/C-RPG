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
	GO_PLAYER,
	GO_ITEMS,	
};

enum textureTypes {
	TEXT_STATIC,
	TEXT_ANIMATION
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
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} Tileset;

enum RoomType{
	R_MENU,
	R_WORLD,
	R_COMBAT
};

typedef struct {
	unsigned int ID;
	enum RoomType type;
	Tileset* tileset;
} Room;

// ---- GAME SYSTEM ----
typedef struct {
	Tileset* sets[6]; // cann hold for tilessets in memory (vorerst) TILE_SLOT_SIZE
	Room room;
	Display display;
	SDL_Window* window;
	SDL_Renderer* renderer;
} GameState;

// -------- FUNCTIONS --------
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