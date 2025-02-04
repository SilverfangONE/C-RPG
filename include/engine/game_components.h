#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL3/SDL.h>	
#include "cJSON.h"
// -------- ALL STRUCTS FOR GLOBAL CONTEXT --------
/**
 * Global game context.
 */
typedef struct GameState {
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

enum EnviromentType{
	ENV_MENU,
	ENV_WORLD,
	ENV_COMBAT
};

struct Enviroment {
    char ID[20];
    enum EnviromentType type;
    /*Blocks calling global UI lobic and rendering from ENV*/
    bool enableGlobalUI; // standart 0; 
    // sub rooms[] oder sub jedes mal rein laden
    struct Sub* sub;
    /* ID TO PATH */
    struct hashmap *subRoomIDMap;
    struct TextureAtlas* tilesheet; // array of sheets
    struct TextureAtlas* spritesheet;
    struct UIElement **uiElements; // array of ui elements
    int uiElementCount;
    bool isLocalUIActive;
};

struct Sub {
    char ID[20];
    struct Map* map;
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

// -------- Rendering Components --------
enum TextureType {
	TEXT_STATIC,
	TEXT_ANIMATED
};

typedef struct {
	SDL_Texture* texture;
	int width;
	int height;
	float scaleX;
	float scaleY;
	SDL_FRect destRect;
} Display;

typedef struct TextureAtlas {
	char ID[20];
    enum TextureType textureType;
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} TextureAtlas;

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
void printTextureAtlas(TextureAtlas*);
void printGameState(GameState*);
void printDisplay(Display*);
//TODO rest print funs.

// ---- LOAD & DESTROY Game Components ----
GameState* initGameState();
void destroyGameState(GameState*);

struct Enviroment* loadEnviroment(GameState* game, char* pathJSON);
void destroyEnviroment(struct Enviroment* env);

struct Sub* loadSub(const GameState* game, const cJSON* pathJSON) ;
void destroySub(struct Sub*);

struct Map* loadMap(GameState*, int cols, int rows, cJSON* backgroundMap, cJSON* middelgroudMap, cJSON* spriteMap, cJSON* logicMap);
void destroyMap(struct Map*);

void loadDisplay(GameState*);
void destroyDisplay(Display*);

TextureAtlas* loadTextureAtlasJSON(GameState*, char* pathJSON );
void destroyTextureAtlas(TextureAtlas*);

struct EnviromentStackItem* createEnviromentStackItem(struct EnviromentStackItem* next, struct Enviroment* env);
void destroyEnviromentStackItem(struct EnviromentStackItem* stackItem); 

void initEnviromentStack(GameState* game);
void destroyEnviromentStack(EnviromentStack* envStack);

// ---- EnviromentStack functions ----
void pushEnviroment(GameState* game, char* pathJSON);
void popEnviroment(GameState* game);

// ---- Convert String to ENUM ----
enum EnviromentType toEnviromentType(GameState* game, char* string);
enum TextureType toTextureType(GameState* game, char* string);
#endif