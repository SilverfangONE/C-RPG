#ifndef UTIL
#define UTIL
#include <stdlib.h>

// USECASE: TILEMAP
typedef struct {
    size_t rows;
    size_t cols;
    int data[];
} DynamicMatrix;

// HASH-MAP
struct node {
    char* key;
    char* value;
    struct node* next;
};

struct hashMap {
    int numOfElements, capacity;
    struct node** arr;
};

#endif 