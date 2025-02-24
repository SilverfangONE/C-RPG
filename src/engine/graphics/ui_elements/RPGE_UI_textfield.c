#include "RPGE_UI_textfield.h"
#include "RPGE_E_time.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_UI_text.h"

#include "log.h"

#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

static const int DEFAULT_TEXT_TILE_Y = 8;
static const int DEFAULT_TEXT_TILE_X = 6;

Vec2D getAlphabetSubTileVec2D_UI_RPGE(char c)
{
    switch (c)
    {
    case 'i':
        return (Vec2D){.x = 3, .y = DEFAULT_TEXT_TILE_Y};
    default:
        return (Vec2D){.x = DEFAULT_TEXT_TILE_X, .y = DEFAULT_TEXT_TILE_Y};
    }
}

TextField_UI_RPGE *build_TextField_UI_RPGE(Assetsheet_RPGE *asset, char *text, Vec2D vCor)
{
    TextField_UI_RPGE *textField = (TextField_UI_RPGE *)malloc(sizeof(TextField_UI_RPGE));
    // NULL CHECKS.
    if (textField == NULL)
    {
        return NULL;
    }
    if (text == NULL || strnlen(text, sizeof(textField->textBuffer) - 1) < 1)
    {
        log_error("build_TextField_UI_RPGE(): text {'%s'} is invalid", text);
        errno = EINVAL;
        return NULL;
    }
    if (asset == NULL)
    {
        log_error("build_TextField_UI_RPGE(): asset is NULL");
        errno = EINVAL;
        return NULL;
    }

    textField->font = asset;

    strncpy(textField->textBuffer, text, sizeof(textField->textBuffer) - 1);
    textField->textBuffer[sizeof(textField->textBuffer) - 1] = '\0';

    textField->vCor = vCor;

    // calc.
    int row = 0;
    int colMax = 0;
    int col = 0;
    Vec2D vPixelMax = {.x = 0, .y = DEFAULT_TEXT_TILE_Y};
    int xPixel = 0;

    for (int l = 0; l < strnlen(textField->textBuffer, sizeof(textField->textBuffer) - 1); l++)
    {
        if (textField->textBuffer[l] == '\n')
        {
            // increment loop counter
            row++;
            vPixelMax.y += DEFAULT_TEXT_TILE_Y;
            // Übernehme den größten wert.
            colMax = (colMax < col) ? col : colMax;
            vPixelMax.x += (vPixelMax.x < xPixel) ? xPixel : vPixelMax.x;
            // reset loop counter
            col = 0;
            xPixel = 0;
        }
        xPixel += getAlphabetSubTileVec2D_UI_RPGE(textField->textBuffer[l]).x;
        col++;
    }

    // set results.
    textField->vPixelSize = vPixelMax;
    textField->vTable = (Vec2D){.x = col, .y = row};

    return textField;
}

void destroy_TextField_UI_RPGE(TextField_UI_RPGE *text_UI_RPGE)
{
    free(text_UI_RPGE);
}

int render_TextField_UI_RPGE(SDL_Renderer *renderer, TextField_UI_RPGE *text_UI_RPGE)
{
    // NULL CHECKS.
    if (text_UI_RPGE == NULL)
    {
        log_error("render_TextField_UI_RPGE(): text_UI_RPGE is NULL");
        errno = EINVAL;
        return 1;
    }
    if (renderer == NULL)
    {
        log_error("render_TextField_UI_RPGE(): renderer is NULL");
        errno = EINVAL;
        return 1;
    }

    // log
    if (checkTimer_TIME_RPGE(SYSTEM_TIMER_ID))
    {
        log_warn("TableSize: %d", text_UI_RPGE->vTable.x * text_UI_RPGE->vTable.y);
    }

    Vec2D vSubTileOffset = {.x = 0, .y = 0};
    Vec2D vSubPatchSize = {.x = 6, .y = 8};
    SDL_FRect dest;
    dest.w = vSubPatchSize.x;
    dest.h = vSubPatchSize.y;
    int yTable = 0;
    int xTable = 0;

    int xPixelCor = 0;

    // iterate of textBuffer and look up right corosponding sprites to given chars.
    for (int literal = 0; literal < strlen(text_UI_RPGE->textBuffer); literal++)
    {
        if (xTable >= text_UI_RPGE->vTable.x)
        {
            xPixelCor = 0;
            xTable = 0;
            yTable++;
        }
        // render literal.
        int index;
        switch (text_UI_RPGE->textBuffer[literal])
        {
        // new line.
        case '\n':
            if (xTable != 0)
            {
                xPixelCor = 0;
                xTable = 0;
                yTable++;
            }
            continue;
        // TODO: add special chars in stlye like <$name$>
        case '\\':
            char sp[6];
            strncpy(sp, text_UI_RPGE->textBuffer + literal, 6);
            int spi = getAlphabetSpecialIndex_UI_RPGE(sp);
            if (spi > -1)
            {
                index = spi;
                literal = +6;
                break;
            }
        // lookup default chars.
        default:
            index = getAlphabetIndex_UI_RPGE(text_UI_RPGE->textBuffer[literal]);
            if (index < 0)
            {
                errno = EINVAL;
                return 1;
            }
        }

        xPixelCor += getAlphabetSubTileVec2D_UI_RPGE(text_UI_RPGE->textBuffer[literal]).x;

        // calc base coordinate
        Vec2D vCor = {.x = text_UI_RPGE->vCor.x + xPixelCor, .y = text_UI_RPGE->vCor.y + yTable * dest.h};

        renderTileV2_Assetsheet_G_RPGE(renderer, text_UI_RPGE->font, index, vCor, vSubPatchSize, vSubTileOffset);

        if (checkTimer_TIME_RPGE(SYSTEM_TIMER_ID))
        {
            log_warn("Literal : %c", text_UI_RPGE->textBuffer[literal]);
            log_info("Literals : %s | lastIndex = %d | length = %d", text_UI_RPGE->textBuffer, literal,
                     strnlen(text_UI_RPGE->textBuffer, sizeof(text_UI_RPGE->textBuffer) - 1));
        }

        xTable++;
    }

    // timer shit
    return 0;
}