#include <errno.h>
#include <stdlib.h>
#include "log.h"
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
        arr[y * vTable.x + x] = value;
        return 0;   
    }
    log_error("setCell_ARRAY2D_UTIL: X(%d) and Y(%d) dont match vTable{x=%d, y=%d}", x , y, vTable.x, vTable.y);
    errno = EINVAL;
    return 1;
}

int getCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y) {
    if ((x > - 1 && x < vTable.x) && (y > -1 && y < vTable.y)) {
        return arr[y * vTable.x + x];   
    }
    return -1;
}

int* create_ARRAY2D_UTIL(Vec2D vTable, int defaultValue) {
    if (vTable.x == 0 || vTable.y == 0) {
        log_error("create_ARRAY2D_UTIL: vTable(x=%d, y=%d) is invalid!", vTable.x, vTable.y);
        errno = EINVAL;
        return NULL;
    }
    int* arr = (int*)malloc(sizeof(int) * (vTable.x * vTable.y));
    if (arr == NULL) return NULL;
    for (int y = 0; y < vTable.y; y++) {
        for (int x = 0; x < vTable.x; x++) {
            setCell_ARRAY2D_UTIL(arr, vTable, x, y, defaultValue);
        }
    }
    return arr;
}
