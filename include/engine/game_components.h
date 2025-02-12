#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include "cJSON.h"
#include <SDL3/SDL.h>
// -------- ALL STRUCTS FOR GLOBAL CONTEXT --------

// -------- CAMERA --------
typedef struct Camera
{
  int x;
  int y;
} Camera;

// -------- KEY INPUT --------
typedef struct Keymap
{
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
typedef struct Player
{
  int x;
  int y;
  int hitBoxWidth;
  int hitBoxHeight;
  int textureAtlasIndex;
  int speed;
} Player;

// -------- Envoirment Context --------
struct SubRoomIDNode
{
  char *id;
  char *path;
};

enum ENV_Type
{
  ENV_MENU,
  ENV_WORLD,
  ENV_COMBAT
};

/**
 * Enviroment
 */
struct ENV
{
  char ID[20];
  enum ENV_Type type;
  /*Blocks calling global UI lobic and rendering from ENV*/
  bool enableGlobalUI; // standart 0;
  // sub rooms[] oder sub jedes mal rein laden
  struct Sub *sub;
  /* ID TO PATH */
  struct hashmap *subRoomIDMap;
  struct TextureAtlas *tilesheet; // array of sheets
  struct TextureAtlas *spritesheet;
  struct UIElement **uiElements; // array of ui elements
  int uiElementCount;
  /* is set by @EnviromentStack */
  bool toRender;
  bool isLocalUIActive;
};

struct Sub
{
  char ID[20];
  struct Map *map;
};

struct Map
{
  int cols;
  int rows;
  struct Matrix *backgroundMap;
  struct Matrix *middelgroudMap;
  struct Matrix *spriteMap;
  struct Matrix *logicMap; // player spawn point and exit
};

struct ENV_StackItem
{
  struct ENV_StackItem *next;
  struct ENV *env;
};

/**
 * Enviroment Stack
 */
typedef struct ENV_Stack
{
  struct ENV_StackItem *top;
  int size;
} ENV_Stack;

// -------- Rendering Components --------
enum TextureType
{
  TEXT_STATIC,
  TEXT_ANIMATED
};

typedef struct Display
{
  SDL_Texture *texture;
  int width;
  int height;
  float scaleX;
  float scaleY;
  SDL_FRect destRect;
} Display;

typedef struct TextureAtlas
{
  char ID[20];
  enum TextureType textureType;
  SDL_Texture *texture;
  char textPath[300];
  int cols;
  int rows;
  int tileSizeX;
  int tileSizeY;
} TextureAtlas;

struct UIElement
{
};
/**
 * Global game context.
 */
typedef struct GameState
{
  Keymap *keymap;
  Player *player;
  Display display;
  SDL_Window *window;
  SDL_Renderer *renderer;
  ENV_Stack envStack;
} GameState;

// ---- GLOBAL CONSTANTS ----
extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int SNES_PIXEL_WIDTH;
extern const int SNES_PIXEL_HEIGHT;
extern const int TARGET_FPS;
extern const char NAME_OF_GAME[40];

// ---- LOAD & DESTROY Game Components ----
GameState *init_GameState ();
void destroy_GameState (GameState *);

void load_Player (GameState *game, int x, int y, int width, int height,
                  int speed, int textureAtlasIndex);
void destroy_Player (Player *player);

void load_Keymap (GameState *game);
void reset_Keymap (Keymap *keymap);
void reset_KeymapExceptPressed (Keymap *keymap);
void destroy_Keymap (Keymap *map);

struct ENV *load_ENV (GameState *game, char *pathJSON);
void destroy_ENV (struct ENV *env);

struct Sub *load_Sub (GameState *game, char *pathJSON);
void destroy_Sub (struct Sub *);

struct Map *load_Map (GameState *, int cols, int rows,
                      const cJSON *backgroundMap, const cJSON *middelgroudMap,
                      const cJSON *spriteMap, const cJSON *logicMap);
void destroy_Map (struct Map *);

Display *create_Display (SDL_Renderer *renderer, int pixelWidth,
                         int pixelHeight, int windowWith, int windowHeight);
void load_Display (GameState *);
void destroy_Display (Display *);

TextureAtlas *load_TextureAtlasJSON (GameState *, char *pathJSON);
void destroy_TextureAtlas (TextureAtlas *);

struct ENV_StackItem *create_ENV_StackItem (struct ENV_StackItem *next,
                                            struct ENV *env);
void destroy_ENV_StackItem (struct ENV_StackItem *stackItem);

void init_ENVStack (GameState *game);
void destroy_ENVStack (ENV_Stack *envStack);

// ---- EnviromentStack functions ----
void push_ENV (GameState *game, char *pathJSON);
void pop_ENV (GameState *game);
void updateToRenderFlagsFromStackEnvs (struct ENV_StackItem *item);
void setToRenderFlagFromLowerENV (struct ENV *top, struct ENV *next);

// ---- Convert String to ENUM ----
enum ENV_Type toENVType (GameState *game, char *string);
enum TextureType toTextureType (GameState *game, char *string);
#endif