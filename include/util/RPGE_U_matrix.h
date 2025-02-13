#ifndef RPGE_U_MATRIX
#define RPGE_U_MATRIX

#include <stdlib.h>

typedef struct Matrix {
    size_t rows;
    size_t cols;
    int data[];
} Matrix;

void setCell_MATRIX_UTIL(Matrix* matrix, unsigned int x, unsigned int y, int value);
int getCell_MATRIX_UTIL(Matrix* matrix, int col, int row);
Matrix* create_MATRIX_UTIL(size_t rows, size_t cols);
void destory_MATRIX_UTIL(Matrix* matrix);

#endif