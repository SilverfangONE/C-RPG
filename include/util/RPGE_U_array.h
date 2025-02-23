#ifndef RPGE_U_ARRAY
#define RPGE_U_ARRAY

#include "RPGE_U_vec.h"

/**
 * @return NULL if erro occurd
 */
int* copy_Array_UTIL (int* src, int length);
int getCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y);
int setCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y, int value);
int* create_ARRAY2D_UTIL(Vec2D vTable, int defaultValue);
void setNull_ArrayPtr_UTIL (void** arrPtr, int length);
#endif