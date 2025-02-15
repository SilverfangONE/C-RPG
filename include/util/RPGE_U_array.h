#ifndef RPGE_U_ARRAY
#define RPGE_U_ARRAY

/**
 * @return NULL if erro occurd
 */
int* copy_Array_UTIL (int* src, int length);
int getCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y);
int setCell_ARRAY2D_UTIL(int* arr, Vec2D vTable, int x, int y, int value);
#endif