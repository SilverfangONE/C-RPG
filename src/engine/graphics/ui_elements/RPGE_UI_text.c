#include "RPGE_UI_text.h"
#include "RPGE_E_time.h"
#include "RPGE_U_string.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RPGE_U_math.h"

// TODO create text component which holds

Text_UI_RPGE* build_Text_UI_RPGE(Assetsheet_RPGE* aFont, Vec2D vTableSize, Vec2D vCoordinates, char* text, enum TextType_UI_RPGE type)
{   
    Text_UI_RPGE* text_UI = malloc(sizeof(Text_UI_RPGE));
    // validate params
    if (text_UI == NULL)
    {
        return NULL;
    }
    if (aFont == NULL) 
    {
        log_error("build_Text_UI_RPGE(): font%s is invalid!", aFont);
        errno = EINVAL;
        return NULL;
    }
    if (vTableSize.x < 1 || vTableSize.y < 1) 
    {
        log_error("build_Text_UI_RPGE(): vTableSize {.x=%d, .y=%d} is invalid!", vTableSize.x, vTableSize.y);
        errno = EINVAL;
        return NULL;
    }
    if (vCoordinates.x < 0 || vCoordinates.y < 0) 
    {
        log_error("build_Text_UI_RPGE(): vCoordinates {.x=%d, .y=%d} is invalid!", vCoordinates.x, vCoordinates.y);
        errno = EINVAL;
        return NULL;
    }
    if (text != NULL || strlen(text) < 1) 
    {
        log_error("build_Text_UI_RPGE(): text {%s} is invalid!", text);
        errno = EINVAL;
        return NULL;
    }
    
    // set values.
    text_UI->font = aFont;
    text_UI->show = true;
    text_UI->vCoordinates = vCoordinates;
    text_UI->vTableSize = vTableSize;
    text_UI->textBuffer = (char*) malloc(sizeof(char) * strlen(text) + 1);
    text_UI->textBuffer[sizeof(text_UI->textBuffer) - 1] = '\0'; 
    strncpys_UTIL(text_UI->textBuffer, text);
    
    // log values.
    log_trace("[text_UI->show = %s}]", (text_UI->show)? "true":"false");
    log_trace("[text_UI->vCoordinates {.x=%d, .y=%d}]", text_UI->vCoordinates.x, text_UI->vCoordinates.y);
    log_trace("[text_UI->vTable {.x=%d, .y=%d}]", text_UI->vTableSize.x, text_UI->vTableSize.y);
    log_trace("[text_UI->textBufferSize = %d]", sizeof(text_UI->textBuffer));
    log_trace("[text_UI->text = %s]", text_UI->textBuffer);
    return text_UI;
}

void destroy_Text_UI_RPGE(Text_UI_RPGE* text_UI) 
{
    free(text_UI->textBuffer);
    free(text_UI);
}

void write_Text_UI_RPGE(Text_UI_RPGE* text_UI, char* text) 
{
    if (sizeof(text_UI->textBuffer - 1) < strlen(text))  
    {
        log_warn("write_Text_UI_RPGE(): given text is bigger than textBuffer size {%d / %d}", strlen(text), sizeof(text_UI->textBuffer) - 1);
    }
    strncpys_UTIL(text_UI->textBuffer, text);
    log_trace("[write_Text_UI_RPGE(): text_UI->textBuffer = {'%s'}]", text_UI->textBuffer);
}

void clear_Text_UI_RPGE(Text_UI_RPGE* text_UI) 
{
    strc_UTIL(text_UI->textBuffer);
}

int render_Text_UI_RPGE(SDL_Renderer* renderer, Text_UI_RPGE* text_UI) 
{
    if (!text_UI->show) 
    {
        return 0;
    } 
    switch(text_UI->type) 
    {
        case TEXT_TYPE_NARROW_RPGE:
            return _render_Text_NARROW_UI_RPGE(renderer, text_UI->textBuffer, text_UI->vCoordinates, text_UI->vTableSize, text_UI->font);
        case TEXT_TYPE_WIDE_RPGE:
            return _render_Text_WIDE_UI_RPGE(renderer, text_UI->textBuffer, text_UI->vCoordinates, text_UI->vTableSize, text_UI->font);
        default:
            log_error("render_Text_UI_RPGE(): type is undifined");
            errno = EINVAL;
            return 1;
    }
}

int getAlphabetIndex_UI_RPGE(char c)
{
    switch (c)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case 'c':
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    case 'h':
        return 7;
    case 'i':
        return 8;
    case 'j':
        return 9;
    case 'k':
        return 10;
    case 'l':
        return 11;
    case 'm':
        return 12;
    case 'n':
        return 13;
    case 'o':
        return 14;
    case 'p':
        return 15;
    case 'q':
        return 16;
    case 'r':
        return 17;
    case 's':
        return 18;
    case 't':
        return 19;
    case 'u':
        return 20;
    case 'v':
        return 21;
    case 'w':
        return 22;
    case 'x':
        return 23;
    case 'y':
        return 24;
    case 'z':
        return 25;
    case 'A':
        return 26;
    case 'B':
        return 27;
    case 'C':
        return 28;
    case 'D':
        return 29;
    case 'E':
        return 30;
    case 'F':
        return 31;
    case 'G':
        return 32;
    case 'H':
        return 33;
    case 'I':
        return 34;
    case 'J':
        return 35;
    case 'K':
        return 36;
    case 'L':
        return 37;
    case 'M':
        return 38;
    case 'N':
        return 39;
    case 'O':
        return 40;
    case 'P':
        return 41;
    case 'Q':
        return 42;
    case 'R':
        return 43;
    case 'S':
        return 44;
    case 'T':
        return 45;
    case 'U':
        return 46;
    case 'V':
        return 47;
    case 'W':
        return 48;
    case 'X':
        return 49;
    case 'Y':
        return 50;
    case 'Z':
        return 51;
    case '0':
        return 52;
    case '1':
        return 53;
    case '2':
        return 54;
    case '3':
        return 55;
    case '4':
        return 56;
    case '5':
        return 57;
    case '6':
        return 58;
    case '7':
        return 59;
    case '8':
        return 60;
    case '9':
        return 61;
    case '!':
        return 62;
    case '?':
        return 63;
    case ':':
        return 64;
    case '-':
        return 65;
    case '_':
        return 66;
    case '[':
        return 67;
    case ']':
        return 68;
    case '(':
        return 69;
    case ')':
        return 70;
    case '|':
        return 71;
    case '@':
        return 72;
    case '#':
        return 73;
    case '&':
        return 74;
    case '*':
        return 75;
    case '+':
        return 76;
    case '=':
        return 77;
    case '/':
        return 78;
    case '\\':
        return 79;
    case '<':
        return 80;
    case '>':
        return 81;
    case '^':
        return 82;
    case '%':
        return 83;
    case '~':
        return 84;
    case '{':
        return 85;
    case '}':
        return 86;
    case '"':
        return 87;
    case '\'':
        return 88;
    case ',':
        return 89;
    case ';':
        return 90;
    case '$':
        return 91;
    case ' ':
        return 92;
    /*
    case 'α': return 85;
    case 'β': return 86;
    case 'δ': return 87;
    case 'Σ': return 88;
    case 'Ω': return 89;
    */
    default:
        return -1; // Zeichen nicht gefunden
    }
}

int getAlphabetSpecialIndex_UI_RPGE(char *letter)
{
    if (strcmp(letter, "\\$a$\\"))
        return 94;
    if (strcmp(letter, "\\$b$\\"))
        return 95;
    if (strcmp(letter, "\\$g$\\"))
        return 96;
    if (strcmp(letter, "\\$s$\\"))
        return 96;
    if (strcmp(letter, "\\$o$\\"))
        return 96;
    return -1;
}

// TODO: create timer failites for gloabl project.
// with something like setTimer(timerID, secs);
// checkTimer(timerID) => returns true if timer alarms. and resets after timer
// destroyTimer(timerID)

// TODO hier findet ein segementaion fault statt vorischt !!!!!
// TODO binde den timer ein !
int _render_Text_WIDE_UI_RPGE(SDL_Renderer *renderer, char *textBuffer, Vec2D vCoordinates, Vec2D vTable,
                             Assetsheet_RPGE *font)
{
    SDL_FRect dest;
    dest.w = font->vPatchSize.x;
    dest.h = font->vPatchSize.y;
    int yTable = 0;
    int xTable = 0;
    // iterate of textBuffer and look up right corosponding sprites to given chars.
    for (int literal = 0; literal < strlen(textBuffer) && literal < vTable.x * vTable.y; literal++)
    {
        if (xTable >= vTable.x)
        {
            xTable = 0;
            yTable++;
        }
        // render literal.
        int index;
        switch (textBuffer[literal])
        {
        // new line.
        case '\n':
            if (xTable != 0)
            {
                xTable = 0;
                yTable++;
            }
            continue;
        // TODO: add special chars in stlye like <$name$>
        case '\\':
            char sp[6];
            strncpy(sp, textBuffer + literal, 6);
            int spi = getAlphabetSpecialIndex_UI_RPGE(sp);
            if (spi > -1)
            {
                index = spi;
                literal = +6;
                break;
            }
        // lookup default chars.
        default:
            index = getAlphabetIndex_UI_RPGE(textBuffer[literal]);
            if (index < 0)
            {
                errno = EINVAL;
                return 1;
            }
        }
        Vec2D cor = {.x = vCoordinates.x + xTable * dest.w, .y = vCoordinates.y + yTable * dest.h};
        renderTile_Assetsheet_G_RPGE(renderer, font, index, cor);
        // logging after timer shit
        if (checkTimer_TIME_RPGE(10))
        {
            log_info("[Index=%d | literal: %c]", index, textBuffer[literal]);
            log_info("[INDEX=%d | xTable=%d, yTable=%d | Vec2D {.x=%d, .y=%d}]", index, xTable, yTable, cor.x, cor.y);
        }
        xTable++;
    }
    // timer shit
    return 0;
}

/**
 * currently only for 8 bit font which accuatly has an offset x wise with 2 pixel
 */
int _render_Text_NARROW_UI_RPGE(SDL_Renderer *renderer, char *textBuffer, Vec2D vCoordinates, Vec2D vTable,
                               Assetsheet_RPGE *font)
{
    Vec2D vSubTileOffset = {.x = 0, .y = 0};
    Vec2D vSubPatchSize = {.x = 6, .y = 8};
    SDL_FRect dest;
    dest.w = vSubPatchSize.x;
    dest.h = vSubPatchSize.y;
    int yTable = 0;
    int xTable = 0;
    // iterate of textBuffer and look up right corosponding sprites to given chars.
    for (int literal = 0; literal < strlen(textBuffer) && literal < vTable.x * vTable.y; literal++)
    {
        if (xTable >= vTable.x)
        {
            xTable = 0;
            yTable++;
        }
        // render literal.
        int index;
        switch (textBuffer[literal])
        {
        // new line.
        case '\n':
            if (xTable != 0)
            {
                xTable = 0;
                yTable++;
            }
            continue;
        // TODO: add special chars in stlye like <$name$>
        case '\\':
            char sp[6];
            strncpy(sp, textBuffer + literal, 6);
            int spi = getAlphabetSpecialIndex_UI_RPGE(sp);
            if (spi > -1)
            {
                index = spi;
                literal = +6;
                break;
            }
        // lookup default chars.
        default:
            index = getAlphabetIndex_UI_RPGE(textBuffer[literal]);
            if (index < 0)
            {
                errno = EINVAL;
                return 1;
            }
        }
        Vec2D vCor = {.x = vCoordinates.x + xTable * dest.w, .y = vCoordinates.y + yTable * dest.h};
        renderTileV2_Assetsheet_G_RPGE(renderer, font, index, vCor, vSubPatchSize, vSubTileOffset);
        // logging after timer shit
        if (checkTimer_TIME_RPGE(10))
        {
            log_info("[Index=%d | literal: %c]", index, textBuffer[literal]);
            log_info("[INDEX=%d | xTable=%d, yTable=%d | Vec2D {.x=%d, .y=%d}]", index, xTable, yTable, vCor.x, vCor.y);
        }
        xTable++;
    }
    // timer shit
    return 0;
}

static bool checkMenuAssetAndFontAsset_TEXT_NARROW_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font)
{
    if (!(asset->vPatchSize.x == font->vPatchSize.x && asset->vPatchSize.y == font->vPatchSize.y))
    {
        log_error("_calc_vTextTable_TEXT_WIDE_UI_RPGE(): asset->vPatchSize != font->vPatchSize, tilesizes need to "
                  "match to calc vTextTable (WIDE)");
        return true;
    }
    return false;
}

// calc from vTableSize with vPatchSize.
Vec2D _calc_vTextTable_TEXT_WIDE_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTableSize,
                                         Vec2D vPaddingHorizontal, Vec2D vPaddingVertical)
{
    // check if tilesize is the same asset == font
    if (checkMenuAssetAndFontAsset_TEXT_NARROW_UI_RPGE(asset, font))
    {
        return (Vec2D){.x = -1, .y = -1};
    }
    return (Vec2D){.x = vTableSize.x - 2 - (vPaddingHorizontal.x + vPaddingHorizontal.y),
                   .y = vTableSize.y - 2 - (vPaddingVertical.x + vPaddingVertical.y)};
}

Vec2D _calc_vTextTable_TEXT_NARROW_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTableSize,
                                           Vec2D vSubPatchSize, Vec2D vPaddingHorizontal, Vec2D vPaddingVertical)
{
    log_info("[_calc_vTextTable_TEXT_NARROW_UI_RPGE(): vTableSize {.x=%d, .y=%d}]", vTableSize.x, vTableSize.y);
    // check if tilesize is the same asset == font
    if (checkMenuAssetAndFontAsset_TEXT_NARROW_UI_RPGE(asset, font))
    {
        return (Vec2D){.x = -1, .y = -1};
    }
    return (Vec2D){
        .x =
            ((vTableSize.x - 2 - (vPaddingHorizontal.x + vPaddingHorizontal.y)) * font->vPatchSize.x) / vSubPatchSize.x,
        .y = ((vTableSize.y - 2 - (vPaddingVertical.x + vPaddingVertical.y)) * font->vPatchSize.y) / vSubPatchSize.y};
}

Vec2D _calc_vTableSize_TEXT_WIDE_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTextTable,
                                         Vec2D vPaddingHorizontal, Vec2D vPaddingVertical, Vec2D vSubPatchSize)
{
    // check if tilesize is the same asset == font
    if (checkMenuAssetAndFontAsset_TEXT_NARROW_UI_RPGE(asset, font))
    {
        return (Vec2D){.x = -1, .y = -1};
    }
    return (Vec2D){.x = vTextTable.x + 2 + (vPaddingHorizontal.x + vPaddingHorizontal.y),
                   .y = vTextTable.y + 2 + (vPaddingVertical.x + vPaddingVertical.y)};
}

Vec2D _calc_vTableSize_TEXT_NARROW_UI_RPGE(Assetsheet_RPGE *asset, Assetsheet_RPGE *font, Vec2D vTextTable,
                                           Vec2D vPaddingHorizontal, Vec2D vPaddingVertical, Vec2D vSubPatchSize)
{
    // check if tilesize is the same asset == font
    if (checkMenuAssetAndFontAsset_TEXT_NARROW_UI_RPGE(asset, font))
    {
        return (Vec2D){.x = -1, .y = -1};
    }

    int xPreTable = vTextTable.x * vSubPatchSize.x / font->vPatchSize.x;
    if (vTextTable.x * vSubPatchSize.x % font->vPatchSize.x != 0) {
        xPreTable++;
    }

    int yPreTable = vTextTable.y * vSubPatchSize.y / font->vPatchSize.y;

    return (Vec2D){
        .x = xPreTable + 2 + (vPaddingHorizontal.x + vPaddingHorizontal.y),
        .y = yPreTable + 2 + (vPaddingVertical.x + vPaddingVertical.y)
    };
}

Vec2D _calc_vTextTable_TEXT_UI_RPGE(char *textBuffer)
{
    int maxRowSize = 1;
    int maxColSize = 1;
    int count = 0;
    for (int i = 0; i < strlen(textBuffer); i++)
    {
        if ('\n' == textBuffer[i])
        {
            maxColSize = max_UTIL(maxColSize, count);
            maxRowSize++;
            count = 0;
            continue;
        }
        count++;
    }
    maxColSize = max_UTIL(maxColSize, count);
    // 2. create array with padding Boarders around char pads.
    log_trace("[_calc_vTextTable_TEXT_UI_RPGE: {.x=%d, .y=%d}]", maxColSize, maxRowSize);
    return (Vec2D){.x = maxColSize, .y = maxRowSize};
}

Vec2D _calc_vTextCoordinates_TEXT_UI_RPGE(Assetsheet_RPGE* asset, Vec2D vCoordinates) {
    return (Vec2D){.x = vCoordinates.x + asset->vPatchSize.x, .y = vCoordinates.y + asset->vPatchSize.y};
}