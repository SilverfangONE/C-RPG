#include "util.h"
#include <stdlib.h>
#include "log.h"

Matrix* createMatrix(size_t rows, size_t cols) {
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

void destoryMatrix(Matrix* matrix) {
    free(matrix);
}

// read from json
void fillMatrix(Matrix* matrix, char* pathJSON) {
    // TODO
}

void setMatrixCell(Matrix* matrix, unsigned int x, unsigned int y, int value) {
    matrix->data[y * matrix->cols + x] = value;
}