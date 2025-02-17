#include "RPGE_UI_text.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_U_vec.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int counter = 0;
static int displayAll = 600; // 5 sec

int render_Text_UI_RPGE(SDL_Renderer *renderer, char *textBuffer, Vec2D vCoordinates, Vec2D vTable,
                        Assetsheet_RPGE *font)
{
    SDL_FRect dest;
    SDL_FRect src;
    dest.w = font->vPatchSize.x;
    dest.h = font->vPatchSize.y;
    src.w = font->vPatchSize.x;
    src.h = font->vPatchSize.y;
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
        if (counter == displayAll)
        {
            log_info("[Index=%d | literal: %c]", index, textBuffer[literal]);
            log_info("[INDEX=%d | xTable=%d, yTable=%d | Vec2D {.x=%d, .y=%d}]", index, xTable, yTable, cor.x, cor.y);
        }
        xTable++;
    }
    // timer shit
    if (counter == displayAll)
    {
        counter = 0;
    }
    else
    {
        counter++;
    }
    return 0;
}