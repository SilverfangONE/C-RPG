#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL3/SDL.h>	

// -------- STRUCTS --------
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

// -------- FUNCTIONS --------
void renderTileFromRoom(GameState* game, int tileIndex, int x, int y);
void renderGame(GameState* game);
Tileset* lookupTileset(GameState* game, unsigned int tilesetID);
Tileset** getTilesetSaveSlot(GameState* game);

// ---- LOAD/DESTROY SYSTEMS ----
void loadTileset(GameState* game, char* tilesetTexturePath, int tileSizeX, int tileSizeY, int cols, int rows, unsigned int ID);
void loadDisplay(GameState* game);
void destroyUIElement(struct UIElement* uiEl);
void destroyDisplay(Display* display);
void destroyTilesheet(Tilesheet *tilesheet);
void destroySpritesheet(Spritesheet*);

#endif