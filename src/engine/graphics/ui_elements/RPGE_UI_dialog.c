#include "log.h"
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "RPGE_UI_text.h"
#include "RPGE_UI_background.h"
#include "RPGE_E_keymap.h"
#include "RPGE_UI_dialog.h"

Dialog_UI_RPGE* build_Dialog_UI_RPGE(Assetsheet_RPGE *font, Assetsheet_RPGE *asset, char* text, Vec2D vCoordinates, Vec2D vTextTable) 
{
    Dialog_UI_RPGE* dialog = malloc(sizeof(Dialog_UI_RPGE));
    if (dialog == NULL) return NULL;
    // check fun inputs.
    if (font == NULL) {
        // TODO: maybe seg fault ?
        log_error("build_Dialog_UI_RPGE: font%s is invalid", font);
        errno = EINVAL;
        return NULL;
    }
    if (asset == NULL) {
        log_error("build_Dialog_UI_RPGE: asset%s is invalid", asset);
        errno = EINVAL;
        return NULL;
    }
    if (text == NULL) {
        log_error("build_Dialog_UI_RPGE: text%s is invalid", text);
        errno = EINVAL;
        return NULL;
    }
    if (vCoordinates.x < 1 || vCoordinates.y < 1) {
        log_error("build_Dialog_UI_RPGE: vCoordinates {.x=%d, .y=%d} is invalid", vCoordinates.x, vCoordinates.y);
        errno = EINVAL;
        return NULL;
    }
    if (vTextTable.x < 1 || vTextTable.y < 1) {
        log_error("build_Dialog_UI_RPGE: vTableSize {.x=%d, .y=%d} is invalid", vTextTable.x, vTextTable.y);
        errno = EINVAL;
        return NULL;
    }

    // calc coordinates.
    dialog->vTextCoordinates = (Vec2D) { 
        .x=vCoordinates.x + font->vPatchSize.x, 
        .y=vCoordinates.y + font->vPatchSize.y 
    };
    log_trace("[dialog->vTextCoordinates {.x=%d, .y=%d}]", dialog->vTextCoordinates.x, dialog->vTextCoordinates.y);
    // makreker text padding
    Vec2D vTableSize = (Vec2D) {.x=vTextTable.x + 2, .y=vTextTable.y + 2 + 1};
    dialog->vIndicatorCoordinates = (Vec2D) {
        // make korrekt padding.
        .x=vCoordinates.x + vTableSize.x * asset->vPatchSize.x - asset->vPatchSize.x,
        .y=vCoordinates.y + vTableSize.y * asset->vPatchSize.y - asset->vPatchSize.y,
    };
    log_trace("[dialog->vIndicatorCoordinates {.x=%d, .y=%d}]", vTableSize.x, vTableSize.y);
    
    // set values.
    dialog->show = true;
    dialog->nextDisplayCharIndex = 0;    
    strncpy(dialog->textBuffer, text, sizeof(dialog->textBuffer) - 1);
    dialog->textBuffer[sizeof(dialog->textBuffer)] = '\0';
    dialog->vTextTable = vTextTable;
    // build dialog window.
    dialog->font = font;
    dialog->background = build_Background_UI_RPGE(asset, vCoordinates, vTableSize);
    log_debug("[Created Dialog_UI_RPGE]");
    return dialog;
}

void destory_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog) 
{
    destroy_Background_UI_RPGE(dialog->background);
    free(dialog);
}

int render_Dialog_UI_RPGE(SDL_Renderer* renderer, Dialog_UI_RPGE* dialog)
{
    // skip if show is false.
    if (!dialog->show) {
        return 0;
    }
    // goes on and render text after nextDisplayCharIndex.
    if (render_Background_UI_RPGE(renderer, dialog->background)) return 1;
    // TODO: maybe crap init data needs to be cleared 
    char textDisplayBuffer[dialog->textDisplayBufferSize];
    // fills up textDisplayBuffer.
    // checks also if index is out of bounce of to displayingText in TextBuffer
    for (int i = 0; i < dialog->textDisplayBufferSize && dialog->nextDisplayCharIndex + 1 < strlen(dialog->textBuffer); i++) {
        textDisplayBuffer[i] = dialog->textBuffer[dialog->nextDisplayCharIndex + i];
    }
    // render text on background.
    log_warn("render_Dialog_UI_RPGE: ello");
    if (render_Text_UI_RPGE(renderer, textDisplayBuffer, dialog->vTextCoordinates, dialog->vTextTable, dialog->font)) return 1;
    
    // render text scroll indicator.
    // an arrow on the right downer egde some where
    // check if some text hasn't been display yet
    if (dialog->nextDisplayCharIndex + getDisplayBufferSize_Dialog_UI_RPGE(dialog) >= strlen(dialog->textBuffer)) {
        // marker only gets rendered if ther is more text in the textBuffer which hasn't been displayed yet.
        renderTile_Assetsheet_G_RPGE(renderer, dialog->background->asset, lookup_BackgroundTiles_UI_RPGE(MENU_ARROW_DOWN), dialog->vIndicatorCoordinates);
    }
    return 0;
}

int getDisplayBufferSize_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog) 
{
    return dialog->vTextTable.x * dialog->vTextTable.y;
}

int update_Dialog_UI_RPGE(Dialog_UI_RPGE* dialog, Keymap_RPGE* keymap) 
{
    // if enter is pushed for next text.
    if(!keymap->enter) 
    {
        return 0;
    }

    // goes on and updates Dialog_UI_RPGE struct.
    dialog->nextDisplayCharIndex =+ getDisplayBufferSize_Dialog_UI_RPGE(dialog);
    
    // close if no more text needs to be displayed.
    if (dialog->nextDisplayCharIndex >= strlen(dialog->textBuffer)) 
    {
        dialog->show = false;
    }
    return 0;
}
