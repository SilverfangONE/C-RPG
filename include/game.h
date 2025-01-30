#ifndef GAME
#define GAME

#include <SDL3/SDL.h>	

typedef struct {
	
} GameState;

int processEvents(SDL_Window*, GameState*);
void load(SDL_Window*, GameState*);
void exitGame(SDL_Window* window, GameState* gameState);
#endif