#include <errno.h>
#include <stdlib.h>
#include "RPGE_U_vec.h"

int* copy_Array_UTIL (int* src, int length) {
    if (src == NULL) {
        errno = EINVAL;
        return NULL;
    }
    int* arr = (int*) malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        arr[i] = src[i];
    }
    return arr;
}