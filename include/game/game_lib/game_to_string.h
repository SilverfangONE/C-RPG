#ifndef GAME_TO_STRING
#define GAME_TO_STRING

#include "game_components.h"

// printing debug level.
void printGameState(GameState* gameState, int LOG_LEVEL);
void printEnviromentStack(struct EnviromentStack* stack, int LOG_LEVEL);
void printEnviroment(struct Enviroment* env, int LOG_LEVEL);
void printDisplay(Display* display, int LOG_LEVEL);
void printTextureAtlas(TextureAtlas* textureAtlas, int LOG_LEVEL);
void printMap(struct Map* map, int LOG_LEVEL);
void printSub(struct Sub* sub, int LOG_LEVEL);
void printConstants(int LOG_LEVEL); 

char* gameStateToString(GameState* gameState);
char* enviromentStackToString(struct EnviromentStack* stack);
char* enviromentToString(struct Enviroment* env);
char* subToString(struct Sub* sub);
char* mapToString(struct Map* map);
char* displayToString(Display* display);
char* textureAtlasToString(TextureAtlas* textureAtlas);
char* enviromentTypeToString (enum EnviromentType type);
char* textureTypeToString (enum TextureType type);
char* constantsToString ();
#endif