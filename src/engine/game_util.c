#include <stdlib.h>
#include "log.h"
#include "cJSON.h"
#include "game_util.h"
#include "game_core.h"

Matrix* createMatrix(size_t rows, size_t cols) {
    Matrix* matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if(!matrix) {
        log_error("malloc failed");
        return NULL;
    }
    matrix->cols = cols;
    matrix->rows = rows;

    // set all entrys to null
    for(int i = 0; i < cols*rows; i++) {
        matrix->data[i] = 0;
    }
    return matrix;
}

Matrix* createMatrixJSON(GameState* game, size_t rows, size_t cols, const cJSON* arrayJSON) {
    validateValueConstJSON(game, arrayJSON);
    validateTypeValueJSON(game, arrayJSON, cJSON_IsArray);
    Matrix* matrix = malloc(sizeof(Matrix) + rows * cols * sizeof(int));
    if(!matrix) {
        log_error("malloc failed");
        exitGame(game);
    }
    matrix->cols = cols;
    matrix->rows = rows;

    // set all entrys to null
    int index = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, arrayJSON) {
        if(index > cols * rows) {
            log_error("ArrayJSONs size is not accordingly to given rows:%d and cols:%d!", rows, cols);
            exitGame(game);
        }
        validateTypeValueJSON(game, item, cJSON_IsNumber);
        matrix->data[index++] = item->valueint;
    }
    return matrix;
}

void destoryMatrix(Matrix* matrix) {
    free(matrix);
}

int getMatrixCell(Matrix* matrix, int col, int row) {
    return matrix->data[row * matrix->cols + col];
}

void setMatrixCell(Matrix* matrix, unsigned int x, unsigned int y, int value) {
    matrix->data[y * matrix->cols + x] = value;
}

void validateValueConstJSON(GameState* game, const cJSON* value) {
    if(value == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        exitGame(game);
    }
}

void validateValueJSON(GameState* game, cJSON* value) {
    if(value == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        log_error("JSON Parsing Error: %s", (error_ptr != NULL)?error_ptr:"Something went wrong LOL.");
        exitGame(game);
    }
}

void validateTypeValueJSON(GameState* game, const cJSON* value, JsonTypeCheckFunc checkType) {
    if(!checkType(value)) {
        log_error("JSON Error: %s type %s ist not valid!", value->string, value->type);
        exitGame(game);
    }
}

// Funktion zum Lesen der JSON-Datei als String
char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Fehler: Datei %s konnte nicht geöffnet werden!\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (!content) {
        printf("Fehler: Speicher konnte nicht allokiert werden!\n");
        fclose(file);
        return NULL;
    }

    fread(content, 1, length, file);
    content[length] = '\0'; // Null-terminieren
    fclose(file);
    return content;
}
