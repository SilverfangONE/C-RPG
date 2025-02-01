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
	SDL_Texture* tilesetTexture;
	enum RoomType type;
} Room;


// ---- RENDER_SYSTEM ----



// ---- GAME SYSTEM ----
typedef struct {
	Room room;
	SDL_Texture* display;
} GameState;

void destoryRoom(Room* room);
void loadRoom(GameState*, SDL_Window*, SDL_Renderer* renderer, char* tilesetTexturePath, enum RoomType type);

void processEvents(GameState*, SDL_Window*);

void destoryGameState(GameState*);
void loadGame(GameState**, SDL_Window**, SDL_Renderer**);
void exitGame(GameState*, SDL_Window*);

void loopGame(GameState*, SDL_Window*, SDL_Renderer*);
void updateGame(GameState*);

void renderGame(GameState* gameState, SDL_Window* window, SDL_Renderer* renderer);
void renderTile(SDL_Renderer* renderer, SDL_Texture* tilesetTexture, int tileIndex, int x, int y);

#endif