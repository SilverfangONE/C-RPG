#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL3/SDL.h>	
#include "cJSON.h"
// -------- ALL STRUCTS FOR GLOBAL CONTEXT --------

// -------- CAMERA --------
typedef struct Camera {
    int x;
    int y;
} Camera;

// -------- KEY INPUT --------
typedef struct Keymap {
    bool up;
    bool pressedUP;
    bool down;
    bool pressedDOWN;
    bool left;
    bool pressedLEFT;
    bool right;
    bool pressedRIGHT;
    bool enter;
    bool esc;
} Keymap;

// -------- Game Objs --------
typedef struct Player {
    int x;
    int y;
    int hitBoxWidth;
    int hitBoxHeight;
    int textureAtlasIndex;
    int speed;
} Player;

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
    /* is set by @EnviromentStack */
    bool toRender;
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

typedef struct Display {
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
	char textPath[300];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} TextureAtlas;

struct UIElement {};
/**
 * Global game context.
 */
typedef struct GameState {
    Keymap* keymap;
	Player* player;
    Display display;
	SDL_Window* window;
	SDL_Renderer* renderer;
    EnviromentStack envStack;
} GameState;

// ---- GLOBAL CONSTANTS ---- 
extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int SNES_PIXEL_WIDTH;
extern const int SNES_PIXEL_HEIGHT;
extern const int TARGET_FPS;
extern const char NAME_OF_GAME[40];

// ---- LOAD & DESTROY Game Components ----
GameState* init_GameState();
void destroy_GameState(GameState*);

void load_Player(GameState* game, int x, int y, int width, int height, int speed, int textureAtlasIndex);
void destroy_Player(Player* player);

void loadKeymap(GameState* game);
void resetKeymap(Keymap* keymap); 
void resetKeymapExceptPressed(Keymap* keymap);
void destroyKeymap(Keymap* map);

struct Enviroment* loadEnviroment(GameState* game, char* pathJSON);
void destroyEnviroment(struct Enviroment* env);

struct Sub* loadSub(GameState* game, char* pathJSON) ;
void destroySub(struct Sub*);

struct Map* loadMap(GameState*, int cols, int rows, const cJSON* backgroundMap, const cJSON* middelgroudMap, const cJSON* spriteMap, const cJSON* logicMap);
void destroyMap(struct Map*);

Display* createDisplay(SDL_Renderer* renderer, int pixelWidth, int pixelHeight, int windowWith, int windowHeight);
void loadDisplay(GameState*);
void destroyDisplay(Display*);

TextureAtlas* loadTextureAtlasJSON(GameState*, char* pathJSON );
void destroyTextureAtlas(TextureAtlas*);

struct EnviromentStackItem* createEnviromentStackItem(struct EnviromentStackItem* next, struct Enviroment* env);
void destroyEnviromentStackItem(struct EnviromentStackItem* stackItem); 

void initEnviromentStack(GameState* game);
void destroyEnviromentStack(EnviromentStack* envStack);

// ---- Sub functions ----
int subRoomIDNode_compare(const void *a, const void *b, void *udata);
bool subRoomIDNode_iter(const void *item, void *udata);
uint64_t subRoomIDNode_hash(const void *item, uint64_t seed0, uint64_t seed1);

// ---- EnviromentStack functions ----
void pushEnviroment(GameState* game, char* pathJSON);
void popEnviroment(GameState* game);
void updateToRenderFlagsFromStackEnvs(struct EnviromentStackItem* item);
void setToRenderFlagFromLowerENV(struct Enviroment* top, struct Enviroment* next);

// ---- Convert String to ENUM ----
enum EnviromentType toEnviromentType(GameState* game, char* string);
enum TextureType toTextureType(GameState* game, char* string);
#endif