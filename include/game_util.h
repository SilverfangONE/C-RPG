#ifndef UTIL
#define UTIL
#include <stdlib.h>

// USECASE: TILEMAP
typedef struct Matrix {
    size_t rows;
    size_t cols;
    int data[];
} Matrix;

// HASH-MAP
typedef enum {
    UNSIGNED_INT_TYPE,
    INT_TYPE,
    STRING_TYPE,
    FLOAT_TYPE,
} ValueType, KeyType;

struct Node {
    void* key;
    void* value;
    struct node* next;
};

struct HashMap {
    int numOfElements, capacity;
    node** arr;
    ValueType valueType;
    KeyType keyType;
};

#endif 