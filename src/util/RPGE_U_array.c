#include <errno.h>
#include <stdlib.h>
#include "RPGE_U_vec.h"
#include "RPGE_U_array.h"

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

int setCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y, int value) {
    if ((x > - 1 && x < vTable.x) && (y > -1 && y < vTable.y)) {
        arr[y * vTable.x + x];   
    }
    log_error("setCell_ARRAY2D_UTIL: X(%d) and Y(%d) dont match vTable{x=%d, y=%d}", x , y, vTable.x, vTable.y);
    errno = EINVAL;
    return -1;
}

int getCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y) {
    if ((x > - 1 && x < vTable.x) && (y > -1 && y < vTable.y)) {
        return arr[y * vTable.x + x];   
    }
    return -1;
}
