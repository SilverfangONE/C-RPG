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
	SDL_Texture* tileset;
	enum RoomType type;
	char* tilesetPath;
} Room;


// ---- RENDER_SYSTEM ----
typedef struct {
	SDL_Texture* texture;
	int width;
	int height;
	int scaleX;
	int scaleY;
} Display;


// ---- GAME SYSTEM ----
typedef struct {
	Room room;
	Display display;
} GameState;

// ---- GAME RENDER ---- 
void renderGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer);
void renderTile(SDL_Renderer* renderer, SDL_Texture* tilesetTexture, int tileIndex, int x, int y);

// ---- GAME SYSTEM ----
void processEvents(GameState*, SDL_Window*);
void loopGame(GameState*, SDL_Window*, SDL_Renderer*);
void updateGame(GameState*);

// ---- PRINT STRUCTS ----



// ---- LOAD/DESTROY SYSTEMS ----
void loadGame(GameState**, SDL_Window**, SDL_Renderer**);
void loadRoom(GameState*, SDL_Window*, SDL_Renderer* renderer, char* tilesetTexturePath, enum RoomType type);
void exitGame(GameState*, SDL_Window*);
void destoryRoom(Room* room);
void destoryGameState(GameState*);



#endif