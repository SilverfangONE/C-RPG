#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "log.h"
#include "cJSON.h"
#include "RPGE_U_json.h"

bool isValueConstValidJSON_UTIL(const cJSON* value, char* jsonFieldName, char* pathJSON) {
    if(value == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error for %s by field %s: %s", pathJSON, jsonFieldName, (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        return false;
    }
    return true;
}

bool isValueValidJSON_UTIL(cJSON* value) {
    if(value == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        return false;
    }
    return true;
}

bool isValueTypeValidJSON_UTIL(const cJSON* value, JsonTypeCheckFunc checkType) {
    if(!checkType(value)) {
        log_error("JSON Error: %s type %s ist not valid!", value->string, value->type);
        return false;
    }
    return true;
}

Matrix* createFromJSON_MATRIX_UTIL(size_t rows, size_t cols, const cJSON* arrayJSON) {
    if(!isValueTypeValidJSON_UTIL( arrayJSON, cJSON_IsArray)) {
        return NULL;
    }
    Matrix* matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if(!matrix) {
        log_error("malloc failed");
        return NULL;
    }
    matrix->cols = cols;
    matrix->rows = rows;

    // set all entrys to null
    int index = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, arrayJSON) {
        if(index > cols * rows) {
            log_error("ArrayJSONs size is not accordingly to given rows:%d and cols:%d!", rows, cols);
            return NULL;
        }
        if(!isValueTypeValidJSON_UTIL(item, cJSON_IsNumber)) {
            return NULL;
        }
        matrix->data[index++] = item->valueint;
    }
    return matrix;
}