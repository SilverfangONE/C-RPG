#ifndef RPGE_E_DISPLAY
#define RPGE_E_DISPLAY

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"

enum SYSTEM_RPGE {
	SNES,
	NES,
	GAME_BOY,
	GAME_BOY_ADVANCED
};

typedef struct Display_RPGE {
	SDL_Texture* texture;
	int width;
	int height;
	float scaleX;
	float scaleY;
	SDL_FRect destRect;
} Display_RPGE;

void destroy_Display_RPGE(Display_RPGE*);
Display_RPGE* create_Display_RPGE(SDL_Renderer*, enum SYSTEM_RPGE, const int, const int);


Vec2D getSystemResolution_RPGE(enum SYSTEM_RPGE res);
#endif