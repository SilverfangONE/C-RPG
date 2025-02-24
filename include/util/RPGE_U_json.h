#ifndef RPGE_U_JSON
#define RPGE_U_JSON

#include <stdbool.h>
#include "cJSON.h"
#include "RPGE_U_matrix.h"

typedef int (*JsonTypeCheckFunc)(const cJSON *const);
Matrix* createFromJSON_MATRIX_UTIL(size_t rows, size_t cols, const cJSON* arrayJSON);
bool isValueConstValidJSON_UTIL(const cJSON* value, char* jsonFieldName, char* pathJSON);
bool isValueConstInvalidJSON_UTIL(const cJSON* value, char* jsonFieldName, char* pathJSON);
bool isValueTypeValidJSON_UTIL(const cJSON* value, JsonTypeCheckFunc checkType);
bool isValueTypeInvalidJSON_UTIL(const cJSON* value, JsonTypeCheckFunc checkFunc);
bool isValueInvalidJSON_UTIL(const cJSON* value);
bool isValueValidJSON_UTIL(const cJSON* value);
Vec2D jsonToVec2D_UTIL_RPGE(const cJSON* json) ;
#endif