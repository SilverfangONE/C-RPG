#include <stdlib.h>
#include "log.h"
#include "RPGE_U_vec.h"
#include "RPGE_U_array.h"
#include "RPGE_U_matrix.h"

Matrix* create_MATRIX_UTIL_RPGE(size_t rows, size_t cols) {
    Matrix* matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if(!matrix) {
        log_error("malloc failed");
        return NULL;
    }
    matrix->vSize =  (Vec2D) { rows, cols};

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
    return getCell_ARRAY2D_UTIL(matrix->data, matrix->vSize, col, row);
}

int setCell_MATRIX_UTIL(Matrix* matrix, unsigned int x, unsigned int y, int value) {
    return setCell_ARRAY2D_UTIL(matrix->data, matrix->vSize, x, y, value);
}

