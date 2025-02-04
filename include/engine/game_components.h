#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL3/SDL.h>	
#include "cJSON.h"
// -------- ALL STRUCTS FOR GLOBAL CONTEXT --------
/**
 * Global game context.
 */
typedef struct {
	Tileset* sets[6]; // cann hold for tilessets in memory (vorerst) TILE_SLOT_SIZE
	Room room;
	Display display;
	SDL_Window* window;
	SDL_Renderer* renderer;
    EnviromentStack envStack;
} GameState;

// -------- Envoirment Context --------
struct SubRoomIDNode {
    char* id;
    char* path;
};

struct Enviroment {
    /*Blocks calling global UI lobic and rendering from ENV*/
    int blockGlobalUI; // standart 0; 
    // sub rooms[] oder sub jedes mal rein laden
    struct Sub* sub;
    /* ID TO PATH */
    struct hashmap *subRoomIDMap;
    int sheetCount;
    int uiElsCount;
    struct Tileset* tileset; // array of sheets
    struct Spritesheet* spritesheet;
    struct UIElement **uiElements; // array of ui elements
    int localUIActive;
};

struct Sub {
    struct Map* map;
    char* ID;
};

struct Map {
    int cols;
    int rows;
    struct Matrix* backgroundMap;
    struct Matrix* middelgroudMap;
    struct Matrix* spriteMap;
    struct Matrix* logicMap; // player spawn point and exit 
};

struct EnviromentStackItem {
    struct EnviromentStackItem* next;
    struct Enviroment* env;
};

typedef struct EnviromentStack {
    struct EnviromentStackItem* top;
    int size;  
} EnviromentStack;

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

// -------- Rendering Components --------
enum textureTypes {
	TEXT_STATIC,
	TEXT_ANIMATION
};

typedef struct {
	SDL_Texture* texture;
	int width;
	int height;
	float scaleX;
	float scaleY;
	SDL_FRect destRect;
} Display;

typedef struct Tileset {
	unsigned int ID;
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} Tileset;

typedef struct Spritesheet {} Spritesheet;
struct UIElement {};

// ---- GLOBAL CONSTANTS ---- 
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

// ---- PRINT STRUCTS ----
void printTileset(Tileset*);
void printGameState(GameState*);
void printDisplay(Display*);
void printRoom(Room*);
char* printRoomType(enum RoomType);

// ---- LOAD & DESTROY Game Components ----
struct GameState* initGameState();
void destroyyGameState(GameState*);

struct Enviroment* loadEnviroment(GameState* game, char* pathJSON);
void destroyEnviroment(struct Enviroment* env);

struct Sub* loadSub(const GameState* game, const cJSON* pathJSON) ;
void destroySub(struct Sub*);

struct Map* loadMap(GameState*, int cols, int rows, cJSON* backgroundMap, cJSON* middelgroudMap, cJSON* spriteMap, cJSON* logicMap);
void destroyMap(struct Map*);

void loadRoom(GameState* , enum RoomType, unsigned int, unsigned int);
void destroyRoom(Room*);

void loadDisplay(GameState*);
void destroyDisplay(Display*);

void loadTileset(GameState* , char* , int , int , int , int , unsigned int);
void loadTilesetJSON(GameState*, char* pathJSON );
void destroyTileset(Tileset*);

struct EnviromentStackItem* createEnviromentStackItem(struct EnviromentStackItem* next, struct Enviroment* env);
void destroyEnviromentStackItem(struct EnviromentStackItem* stackItem); 

void initEnviromentStack(GameState* game);
void destroyEnviromentStack(EnviromentStack* envStack);

#endif