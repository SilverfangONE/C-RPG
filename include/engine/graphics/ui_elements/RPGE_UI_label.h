#ifndef RPGE_UI_LABEL
#define RPGE_UI_LABEL

#include "log.h"
#include <stdlib.h>
#include <errno.h>
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"
#include "RPGE_UI_label.h"
#include "RPGE_U_math.h"

typedef struct LABEL_UI_RPGE {
    char* text;
    Assetsheet_RPGE* font;
    Vec2D vTable;
    Vec2D vCoordinates;
    BACKGROUND_UI_RPGE* background;
} LABEL_UI_RPGE;

LABEL_UI_RPGE* create_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text) {
    LABEL_UI_RPGE* label = (LABEL_UI_RPGE*) malloc(sizeof(LABEL_UI_RPGE));
    if (label == NULL) return NULL;
    if (font == NULL) {
        log_error("create_Label_UI_RPGE: Font is invalid!");
        errno = EINVAL;
        return NULL;
    }
    label->font = font;
    if (text == NULL || strlen(text) == 0) {
        log_error("create_Label_UI_RPGE: Text is invalid!");
        errno = EINVAL;
        return NULL;
    }
    // build text. box
    // 1. determine size of char patches.
    if (asset == NULL) {
        log_error("create_Label_UI_RPGE: Asset is invalid!");
        errno = EINVAL;
        return NULL;
    }
    int maxRowSize = 1;
    int maxColSize = 1;
    int count = 0;
    for (int i = 0; i < strlen(text) + 1; i++) {
        if('\n' == text[i]) {
            maxColSize =  max_UTIL(maxColSize, count);
            maxRowSize++;
            count = 0;
            continue;
        }
        count++;
    }
    maxColSize = max_UTIL(maxColSize, count);
    // 2. create array with padding around char pads.

    return label;
}
#endif