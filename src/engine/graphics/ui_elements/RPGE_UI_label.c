#include <stdlib.h>
#include <errno.h>
#include "log.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_math.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_background.h"
#include "RPGE_UI_label.h"
#include "RPGE_UI_text.h"
#include "RPGE_UI_label.h"

Label_UI_RPGE* build_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates) {
    Label_UI_RPGE* label = (Label_UI_RPGE*) malloc(sizeof(Label_UI_RPGE));
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
    strncpy(label->textBuffer, text, sizeof(label->textBuffer) - 1);
    label->textBuffer[sizeof(label->textBuffer)] = '\0';

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
    // 2. create array with padding Boarders around char pads.
    label->vTextTable = (Vec2D) { .x=maxColSize, .y=maxRowSize };
    Vec2D vTable; 
    vTable.x = 2 + maxColSize;
    vTable.y = 2 + maxRowSize;
    label->vTextCoordinates = (Vec2D) {
        .x=vCoordinates.x - asset->vPatchSize.x, 
        .y=vCoordinates.y - asset->vPatchSize.y 
    };
    label->background = build_Background_UI_RPGE(asset, vCoordinates, vTable);
    if (label->background == NULL) return NULL;
    return label;
}

int render_Label_UI_RPGE(SDL_Renderer* renderer, Label_UI_RPGE* label) {
    render_Background_UI_RPGE(renderer, label->background);
    render_Text_UI_RPGE(renderer, label->textBuffer, label->vTextCoordinates, label->vTextTable, label->font);
    return 1;
}