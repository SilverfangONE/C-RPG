#include "RPGE_UI_label.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_UI_background.h"
#include "RPGE_UI_label.h"
#include "RPGE_UI_text.h"
#include "RPGE_U_vec.h"
#include "log.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

Label_UI_RPGE *build_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char *text, Vec2D vCoordinates)
{
    Label_UI_RPGE *label = (Label_UI_RPGE *)malloc(sizeof(Label_UI_RPGE));
    if (label == NULL)
        return NULL;
    if (font == NULL)
    {
        log_error("create_Label_UI_RPGE: Font is invalid!");
        errno = EINVAL;
        return NULL;
    }
    label->font = font;

    if (text == NULL || strlen(text) == 0)
    {
        log_error("create_Label_UI_RPGE: Text is invalid!");
        errno = EINVAL;
        return NULL;
    }
    strncpy(label->textBuffer, text, sizeof(label->textBuffer) - 1);
    label->textBuffer[sizeof(label->textBuffer)] = '\0';

    // build text. box
    // 1. determine size of char patches.
    if (asset == NULL)
    {
        log_error("create_Label_UI_RPGE: Asset is invalid!");
        errno = EINVAL;
        return NULL;
    }

    // 2. create array with padding Boarders around char pads.
    label->vTextTable = _calc_vTextTable_TEXT_UI_RPGE(text);
    if (label->vTextTable.x < 0 || label->vTextTable.y < 0)
    {
        log_error("build_Dialog_UI_RPGE: vTextTable {.x=%d, .y=%d} is invalid calculated", label->vTextTable.x,
                  label->vTextTable.y);
        errno = EINVAL;
        return NULL;
    }
    log_trace("[label->vTextTable {.x=%d, .y=%d}]", label->vTextTable.x, label->vTextTable.y);

    label->vTextCoordinates = _calc_vTextCoordinates_TEXT_UI_RPGE(asset, vCoordinates);
    if (label->vTextCoordinates.x < 0 || label->vTextCoordinates.y < 0)
    {
        log_error("build_Dialog_UI_RPGE: vTextCoordinates {.x=%d, .y=%d} is invalid calculated",
                  label->vTextCoordinates.x, label->vTextCoordinates.y);
        errno = EINVAL;
        return NULL;
    }
    log_trace("[label->vTextCoordinates {.x=%d, .y=%d}]", label->vTextCoordinates.x, label->vTextCoordinates.y);

    Vec2D vTableSize = _calc_vTableSize_TEXT_NARROW_UI_RPGE(asset, font, label->vTextTable, (Vec2D){0, 0},
                                                            (Vec2D){0, 0}, (Vec2D){6, 8});
    if (vTableSize.x < 0 || vTableSize.y < 0)
    {
        log_error("build_Dialog_UI_RPGE: vTableSize {.x=%d, .y=%d} is invalid calculated", vTableSize.x, vTableSize.y);
        errno = EINVAL;
        return NULL;
    }
    log_trace("[label->vTableSize {.x=%d, .y=%d}]", vTableSize.x, vTableSize.y);

    label->background = build_Background_UI_RPGE(asset, vCoordinates, vTableSize);
    if (label->background == NULL)
        return NULL;
    label->show = true;
    log_debug("[Created Label_UI_RPGE {text='%s'}]", label->textBuffer);
    return label;
}

int render_Label_UI_RPGE(SDL_Renderer *renderer, Label_UI_RPGE *label)
{
    if (label->show)
    {
        if (render_Background_UI_RPGE(renderer, label->background))
        {
            return 1;
        }
        if (render_Text_NARROW_UI_RPGE(renderer, label->textBuffer, label->vTextCoordinates, label->vTextTable,
                                       label->font))
        {
            return 1;
        }
        return 0;
    }
}

void destory_Label_UI_RPGE(Label_UI_RPGE *label)
{
    destroy_Background_UI_RPGE(label->background);
    free(label);
}