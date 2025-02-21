#include "RPGE_UI_dialog.h"
#include "RPGE_E_keymap.h"
#include "RPGE_E_time.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_UI_background.h"
#include "RPGE_UI_text.h"
#include "RPGE_U_vec.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Dialog_UI_RPGE *build_Dialog_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char *text, Vec2D vCoordinates,
                                     Vec2D vTableSize)
{
    Dialog_UI_RPGE *dialog = malloc(sizeof(Dialog_UI_RPGE));
    if (dialog == NULL)
        return NULL;
    // check fun inputs.
    if (font == NULL)
    {
        // TODO: maybe seg fault ?
        log_error("build_Dialog_UI_RPGE: font%s is invalid", font);
        errno = EINVAL;
        return NULL;
    }
    if (asset == NULL)
    {
        log_error("build_Dialog_UI_RPGE: asset%s is invalid", asset);
        errno = EINVAL;
        return NULL;
    }
    if (text == NULL)
    {
        log_error("build_Dialog_UI_RPGE: text%s is invalid", text);
        errno = EINVAL;
        return NULL;
    }
    if (vCoordinates.x < 1 || vCoordinates.y < 1)
    {
        log_error("build_Dialog_UI_RPGE: vCoordinates {.x=%d, .y=%d} is invalid", vCoordinates.x, vCoordinates.y);
        errno = EINVAL;
        return NULL;
    }
    if (vTableSize.x < 1 || vTableSize.y < 1)
    {
        log_error("build_Dialog_UI_RPGE: vTableSize {.x=%d, .y=%d} is invalid", vTableSize.x, vTableSize.y);
        errno = EINVAL;
        return NULL;
    }

    // calc coordinates.
    dialog->vTextCoordinates = _calc_vTextCoordinates_TEXT_UI_RPGE(asset, vCoordinates);
    log_trace("[dialog->vTextCoordinates {.x=%d, .y=%d}]", dialog->vTextCoordinates.x, dialog->vTextCoordinates.y);
    // makreker text padding

    dialog->vTextTable = _calc_vTextTable_TEXT_NARROW_UI_RPGE(asset, font, vTableSize, (Vec2D){.x = 6, .y = 8},
                                                              (Vec2D){.x = 0, .y = 0}, (Vec2D){.x = 0, .y = 1});
    if (dialog->vTextTable.x < 0 || dialog->vTextTable.y < 0)
    {
        log_error("build_Dialog_UI_RPGE: vTextTable {.x=%d, .y=%d} is invalid calculated", dialog->vTextTable.x,
                  dialog->vTextTable.y);
        errno = EINVAL;
        return NULL;
    }
    log_trace("[dialog->vTextTable {.=x%d, .y=%d}]", dialog->vTextTable, dialog->vTextTable);

    dialog->vIndicatorCoordinates = (Vec2D){
        // make korrekt padding.
        .x = vCoordinates.x + vTableSize.x * asset->vPatchSize.x - asset->vPatchSize.x * 2,
        .y = vCoordinates.y + vTableSize.y * asset->vPatchSize.y - asset->vPatchSize.y * 2,
    };
    log_trace("[dialog->vIndicatorCoordinates {.x=%d, .y=%d}]", dialog->vIndicatorCoordinates.x,
              dialog->vIndicatorCoordinates.y);

    // set values.
    dialog->show = true;
    dialog->nextDisplayCharIndex = 0;
    strncpy(dialog->textBuffer, text, sizeof(dialog->textBuffer) - 1);
    dialog->textBuffer[sizeof(dialog->textBuffer)] = '\0';
    // build dialog window.
    dialog->font = font;
    dialog->background = build_Background_UI_RPGE(asset, vCoordinates, vTableSize);
    // calc displayTextBufferSize.
    dialog->textDisplayBufferSize = dialog->vTextTable.x * dialog->vTextTable.y;
    log_debug("[Created Dialog_UI_RPGE {.textBuffer='%s', .textDisplayBufferSize=%d}]", dialog->textBuffer,
              dialog->textDisplayBufferSize);
    return dialog;
}

void destory_Dialog_UI_RPGE(Dialog_UI_RPGE *dialog)
{
    destroy_Background_UI_RPGE(dialog->background);
    free(dialog);
}

int render_Dialog_UI_RPGE(SDL_Renderer *renderer, Dialog_UI_RPGE *dialog)
{
    // skip if show is false.
    if (!dialog->show)
    {
        return 0;
    }
    // goes on and render text after nextDisplayCharIndex.
    if (render_Background_UI_RPGE(renderer, dialog->background))
        return 1;
    // TODO: maybe crap init data needs to be cleared
    char textDisplayBuffer[dialog->textDisplayBufferSize];
    // fills up textDisplayBuffer.
    // checks also if index is out of bounce of to displayingText in TextBuffer
    for (int i = 0; i < dialog->textDisplayBufferSize && dialog->nextDisplayCharIndex + 1 < strlen(dialog->textBuffer);
         i++)
    {
        textDisplayBuffer[i] = dialog->textBuffer[dialog->nextDisplayCharIndex + i];
    }
    // check builded text buffer.
    if (checkTimer_TIME_RPGE(SYSTEM_TIMER_ID))
    {
        log_trace("[textDisplayBuffer { textBuffer='%s', bufferSize=%d}]", textDisplayBuffer,
                  dialog->textDisplayBufferSize);
    }
    // render text on background.
    if (render_Text_NARROW_UI_RPGE(renderer, textDisplayBuffer, dialog->vTextCoordinates, dialog->vTextTable,
                                   dialog->font))
        return 1;
    // render text scroll indicator.
    // an arrow on the right downer egde some where
    // check if some text hasn't been display yet
    if (dialog->nextDisplayCharIndex + dialog->textDisplayBufferSize < strlen(dialog->textBuffer))
    {
        // marker only gets rendered if ther is more text in the textBuffer which hasn't been displayed yet.
        renderTile_Assetsheet_G_RPGE(renderer, dialog->background->asset,
                                     lookup_BackgroundTiles_UI_RPGE(MENU_ARROW_LEFT), dialog->vIndicatorCoordinates);
    }
    return 0;
}

int update_Dialog_UI_RPGE(Dialog_UI_RPGE *dialog, Keymap_RPGE *keymap)
{
    if (!dialog->show)
        return 0;

    // if enter is pushed for next text.
    if (!keymap->enter)
    {
        return 0;
    }

    // goes on and updates Dialog_UI_RPGE struct.
    dialog->nextDisplayCharIndex += dialog->textDisplayBufferSize;

    log_trace("[Dialog_UI_RPGE: indexBuffer %d / %d]", dialog->nextDisplayCharIndex, strlen(dialog->textBuffer));
    log_trace("[Dialog_UI_RPGE: textDisplayBufferSize %d]", dialog->textDisplayBufferSize);

    // close if no more text needs to be displayed.
    if (dialog->nextDisplayCharIndex >= strlen(dialog->textBuffer))
    {
        // reset.
        dialog->nextDisplayCharIndex = 0;
        dialog->show = false;
    }
    return 0;
}
