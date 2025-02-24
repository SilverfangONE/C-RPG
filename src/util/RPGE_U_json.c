#include "RPGE_U_json.h"
#include "cJSON.h"
#include "log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isValueConstInvalidJSON_UTIL(const cJSON *value, char *jsonFieldName, char *pathJSON)
{
    if (value == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error for %s by field %s: %s", pathJSON, jsonFieldName,
                  (error_ptr != NULL) ? error_ptr : "Something went wrong LOL.");
        return true;
    }
    return false;
}

bool isValueInvalidJSON_UTIL(const cJSON *value)
{
    if (value == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL) ? error_ptr : "Something went wrong LOL.");
        return true;
    }
    return false;
}

bool isValueTypeInvalidJSON_UTIL(const cJSON *value, JsonTypeCheckFunc checkType)
{
    if (!checkType(value))
    {
        log_error("JSON Error: %s type %s ist not valid!", value->string, value->type);
        return true;
    }
    return false;
}
// syntax sugar.
bool isValueTypeValidJSON_UTIL(const cJSON *value, JsonTypeCheckFunc checkType)
{
    return !isValueTypeInvalidJSON_UTIL(value, checkType);
}
bool isValueValidJSON_UTIL(const cJSON *value)
{
    return !isValueInvalidJSON_UTIL(value);
}
bool isValueConstValidJSON_UTIL(const cJSON *value, char *jsonFieldName, char *pathJSON)
{
    return !isValueConstInvalidJSON_UTIL(value, jsonFieldName, pathJSON);
}

Matrix *createFromJSON_MATRIX_UTIL(size_t rows, size_t cols, const cJSON *arrayJSON)
{
    if (!isValueTypeInvalidJSON_UTIL(arrayJSON, cJSON_IsArray))
    {
        return NULL;
    }
    Matrix *matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if (!matrix)
    {
        log_error("malloc failed");
        return NULL;
    }
    matrix->vSize.x = cols;
    matrix->vSize.y = rows;

    // set all entrys to null
    int index = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, arrayJSON)
    {
        if (index > cols * rows)
        {
            log_error("ArrayJSONs size is not accordingly to given rows:%d and cols:%d!", rows, cols);
            return NULL;
        }
        if (!isValueTypeInvalidJSON_UTIL(item, cJSON_IsNumber))
        {
            return NULL;
        }
        matrix->data[index++] = item->valueint;
    }
    return matrix;
}

Vec2D jsonToVec2D_UTIL_RPGE(const cJSON *json)
{
    if (json == NULL)
    {
        log_warn("jsonToVec2D_UTIL_RPGE: json is NULL");
        errno = EINVAL;
        return (Vec2D){-1, -1};
    }

    Vec2D vec;

    const cJSON *yJ = NULL;
    const cJSON *xJ = NULL;

    yJ = cJSON_GetObjectItemCaseSensitive(json, "y");
    if (isValueInvalidJSON_UTIL(yJ))
        return (Vec2D){-1, -1};
    if (isValueTypeInvalidJSON_UTIL(yJ, cJSON_IsNumber))
        return (Vec2D){-1, -1};
    vec.y = yJ->valueint;

    xJ = cJSON_GetObjectItemCaseSensitive(json, "x");
    if (isValueInvalidJSON_UTIL(xJ))
        return (Vec2D){-1, -1};
    if (isValueTypeInvalidJSON_UTIL(xJ, cJSON_IsNumber))
        return (Vec2D){-1, -1};
    vec.x = xJ->valueint;

    log_trace("[Created Vec2D {x=%d, y=%d}]", vec.x, vec.y);
    return vec;
}