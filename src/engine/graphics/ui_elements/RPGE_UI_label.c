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

Label_UI_RPGE *build_Label_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char *text, Vec2D vCoordinates,
                                   enum TextType_UI_RPGE textType)
{
    Label_UI_RPGE *label = (Label_UI_RPGE *)malloc(sizeof(Label_UI_RPGE));
    // validate values.
    if (label == NULL)
        return NULL;
    if (text == NULL || strlen(text) == 0)
    {
        log_error("create_Label_UI_RPGE(): Text is invalid!");
        errno = EINVAL;
        return NULL;
    }
    // set values.
    label->text_UI = build_Text_UI_RPGE(font, _calc_vTextTableV2_TEXT_UI_RPGE(text), _calc_vTextCoordinates_TEXT_UI_RPGE(asset, vCoordinates), text, textType);
    label->background = build_Background_from_Text_UI_RPGE(label->text_UI, asset, vCoordinates, (Vec2D) { 0, 0}, (Vec2D) { 0, 0});
    if (label->background == NULL)
    {
        return NULL;
    }
    label->show = true;
    // log values.
    log_debug("[Created Label_UI_RPGE {text='%s'}]", label->text_UI->textBuffer);
    return label;
}

int render_Label_UI_RPGE(SDL_Renderer *renderer, Label_UI_RPGE *label)
{
    if (!label->show)
    {
        return 0;
    }
    if (render_Background_UI_RPGE(renderer, label->background))
    {
        return 1;
    }
    if (render_Text_UI_RPGE(renderer, label->text_UI))
    {
        return 1;
    }
    return 0;
}

void destory_Label_UI_RPGE(Label_UI_RPGE *label)
{
    destroy_Background_UI_RPGE(label->background);
    free(label);
}