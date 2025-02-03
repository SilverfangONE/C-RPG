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

// HASH-MAP
uint32_t jenkins_one_at_a_time_hash(char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}


void initHashMap(struct hashMap* mp, int capacity) {
    mp->capacity = capacity;
    mp->numOfElements = 0;
    mp->arr = (struct node**)malloc(sizeof(struct node*) * mp->capacity);
    return;
}

struct hashFunction(struct hashMap* mp, charÜ)
