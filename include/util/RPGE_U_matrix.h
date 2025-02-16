#ifndef RPGE_U_MATRIX
#define RPGE_U_MATRIX

#include <stdlib.h>
#include "RPGE_U_vec.h"

typedef struct Matrix {
    Vec2D vSize;
    int data[];
} Matrix;

int setCell_MATRIX_UTIL(Matrix* matrix, unsigned int x, unsigned int y, int value);
int getCell_MATRIX_UTIL(Matrix* matrix, int col, int row);
Matrix* create_MATRIX_UTIL(size_t rows, size_t cols);
int destory_MATRIX_UTIL(Matrix* matrix);


#endif