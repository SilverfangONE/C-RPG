#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL3/SDL.h>	

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

struct Tilesheet {
    unsigned int ID;
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
};

typedef struct {
	unsigned int ID;
	SDL_Texture* texture;
	char textPath[50];
	int cols;
	int rows;
	int tileSizeX;
	int tileSizeY;
} Tileset;

struct Spritesheet {};
struct UIElement {};

#endif