#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	
#include "game_render.h"

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
enum GameObjTypes {
	GO_PLAYER,
	GO_ITEMS,	
};

typedef struct {
	SDL_Texture* spriteset;
	int spritesX; // cols of spritesheet
	int spirtesY; // rows of spritesheet
} GameObj;


// ........ GAME ENV SYSTEM ........
struct SubRoomIDNode {
    unsigned int ID;
    char* path;
};

struct Enviroment {
    /*Blocks calling global UI lobic and rendering from ENV*/
    int blockGlobalUI; // standart 0; 
    // sub rooms[] oder sub jedes mal rein laden
    struct Sub* sub;
    /* ID TO PATH */
    struct hashmap *mapSubRoomIDs;
    int sheetCount;
    int uiElsCount;
    struct Tilesheet tilesheet; // array of sheets
    struct Spritesheet spritesheet;
    struct UIElement* uiElements; // array of ui elements
    int localUIActive;
};

struct Sub {
    struct Map* map;
};

struct Map {
    struct Matrix* backgroundMap;
    struct Matrix* middelgroudMap;
    struct Matrix* spriteMap;
    struct Matrix* logicMap; // player spawn point and exit 
};

/* bis jetzt noch kein use case dafür.
enum Tilesize {
	TILE_SIZE_SMALL,
	TILE_SIZE_BIG
};
*/

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