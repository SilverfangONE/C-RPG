#ifndef RPGE_U_JSON
#define RPGE_U_JSON

#include <stdbool.h>
#include "cJSON.h"
#include "RPGE_U_matrix.h"

typedef int (*JsonTypeCheckFunc)(const cJSON *const);
Matrix* createFromJSON_MATRIX_UTIL(size_t rows, size_t cols, const cJSON* arrayJSON);
bool isValueValidJSON_UTIL(cJSON* value);
bool isValueConstValidJSON_UTIL(const cJSON* value, char* jsonFieldName, char* pathJSON);
bool isValueTypeValidJSON_UTIL(const cJSON* value, JsonTypeCheckFunc checkFunc);

#endif