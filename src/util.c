#include "util.h"
#include <stdlib.h>
#include "log.h"

DynamicMatrix* createDynMatrix(size_t rows, size_t cols) {
    DynamicMatrix* matrix = malloc(sizeof(DynamicMatrix) + rows * cols * sizeof(int));
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

void destoryDynMatrix(DynamicMatrix* matrix) {
    free(destoryDynMatrix);
}

// read from json
void fillDynMatrix(DynamicMatrix* matrix, char* pathJSON) {
    // TODO
}

void setDynMatrixCell(DynamicMatrix* matrix, unsigned int x, unsigned int y, int value) {
    matrix->data[y * matrix->cols + x] = value;
}