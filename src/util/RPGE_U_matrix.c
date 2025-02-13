#include <stdlib.h>
#include "log.h"
#include "RPGE_U_matrix.h"

Matrix* create_MATRIX_UTIL(size_t rows, size_t cols) {
    Matrix* matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if(!matrix) {
        log_error("malloc failed");
        return NULL;
    }
    matrix->cols = cols;
    matrix->rows = rows;

    // set all entrys to null
    for(int i = 0; i < cols*rows; i++) {
        matrix->data[i] = 0;
    }
    return matrix;
}

void destory_MATRIX_UTIL(Matrix* matrix) {
    free(matrix);
}

int getCell_MATRIX_UTIL(Matrix* matrix, int col, int row) {
    return matrix->data[row * matrix->cols + col];
}

void setCell_MATRIX_UTIL(Matrix* matrix, unsigned int x, unsigned int y, int value) {
    matrix->data[y * matrix->cols + x] = value;
}
