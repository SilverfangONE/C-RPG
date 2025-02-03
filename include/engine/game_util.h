#ifndef UTIL
#define UTIL
#include <stdlib.h>

// USECASE: TILEMAP
typedef struct Matrix {
    size_t rows;
    size_t cols;
    int data[];
} Matrix;

// -------- FUNCTIONS --------
void setMatrixCell(Matrix* matrix, unsigned int x, unsigned int y, int value);
void fillMatrix(Matrix* matrix, cJSON* json);

// ---- LOAD/DESTROY SYSTEMS ----
Matrix* createMatrix(size_t rows, size_t cols);
void destoryMatrix(Matrix* matrix);

#endif 