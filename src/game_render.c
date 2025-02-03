#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
    unsigned int ID;
    SDL_Texture* texture;
    char textPath[30];
    int cols;
    int rows;
    int sizeX;
    int sizeY;
} Tilesheet;

typedef struct {
    SDL_Texture* texture; 
    int width;
    int height;
    float scaleX;
    float scaleY;
    SDL_FRect destRect;
} Display;

void loadTilesheet(char* jsonPath, char* imgPath) {
    
}