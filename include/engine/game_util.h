#ifndef UTIL
#define UTIL
#include <stdlib.h>

// USECASE: TILEMAP
typedef struct Matrix {
    size_t rows;
    size_t cols;
    int data[];
} Matrix;
#endif 