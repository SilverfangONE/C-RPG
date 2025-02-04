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

// ---- LOAD/DESTROY SYSTEMS ----
Matrix* createMatrixJSON(GameState* game, size_t rows, size_t cols, cJSON* arrayJSON);
Matrix* createMatrix(size_t rows, size_t cols);
void destoryMatrix(Matrix* matrix);

void validateValueJSON(GameState* game, cJSON* value);
void validateTypeValueJSON(GameState* game, cJSON* value, int (*checkType)(cJSON*));
#endif 