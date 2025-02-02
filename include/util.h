#ifndef UTIL
#define UTIL
#include <stdlib.h>

// USECASE: TILEMAP
typedef struct {
    size_t rows;
    size_t cols;
    int data[];
} DynamicMatrix;
#endif 