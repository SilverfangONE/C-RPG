#ifndef UTIL
#define UTIL
#include "cJSON.h"
#include "game_components.h"


// USECASE: TILEMAP
typedef struct Matrix {
    size_t rows;
    size_t cols;
    int data[];
} Matrix;

// -------- FUNCTIONS --------
void setMatrixCell(Matrix* matrix, unsigned int x, unsigned int y, int value);
int getMatrixCell(Matrix* matrix, int col, int row);

// ---- LOAD/DESTROY SYSTEMS ----
Matrix* createMatrixJSON(GameState* game, size_t rows, size_t cols, const cJSON* arrayJSON);
Matrix* createMatrix(size_t rows, size_t cols);
void destoryMatrix(Matrix* matrix);

typedef int (*JsonTypeCheckFunc)(const cJSON *const);
void validateValueJSON(GameState* game, cJSON* value);
void validateValueConstJSON(GameState* game, const cJSON* value, char* jsonFieldName, char* pathJSON);
void validateTypeValueJSON(GameState* game, const cJSON* value, JsonTypeCheckFunc checkFunc);
char* readFile(const char* filename);
#endif 