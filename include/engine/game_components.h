#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL3/SDL.h>	
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
    struct Tilesheet* tilesheet; // array of sheets
    struct Spritesheet* spritesheet;
    struct UIElement **uiElements; // array of ui elements
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

struct EnviromentStackItem {
    struct EnviromentStackItem* prev;
    struct EnviromentStackItem* next;
    struct Enviroment* env;
};

typedef struct EnviromentStack {
    struct EnviromentStackItem* top;
    struct EnviromentStackItem* bottom;
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

typedef struct Tilesheet {
    unsigned int ID;
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} Tilesheet;

typedef struct {
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

#endif