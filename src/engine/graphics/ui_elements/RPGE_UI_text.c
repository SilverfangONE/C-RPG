#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "RPGE_U_vec.h"
#include "RPGE_G_assetsheet.h"
#include "RPGE_UI_text.h"

int getAlphabetIndex_UI_RPGE(char letter) {
    switch (letter) {
        // Kleinbuchstaben a-z (0-25)
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        case 'i': return 8;
        case 'j': return 9;
        case 'k': return 10;
        case 'l': return 11;
        case 'm': return 12;
        case 'n': return 13;
        case 'o': return 14;
        case 'p': return 15;
        case 'q': return 16;
        case 'r': return 17;
        case 's': return 18;
        case 't': return 19;
        case 'u': return 20;
        case 'v': return 21;
        case 'w': return 22;
        case 'x': return 23;
        case 'y': return 24;
        case 'z': return 25;

        // Großbuchstaben A-Z (26-51)
        case 'A': return 26;
        case 'B': return 27;
        case 'C': return 28;
        case 'D': return 29;
        case 'E': return 30;
        case 'F': return 31;
        case 'G': return 32;
        case 'H': return 33;
        case 'I': return 34;
        case 'J': return 35;
        case 'K': return 36;
        case 'L': return 37;
        case 'M': return 38;
        case 'N': return 39;
        case 'O': return 40;
        case 'P': return 41;
        case 'Q': return 42;
        case 'R': return 43;
        case 'S': return 44;
        case 'T': return 45;
        case 'U': return 46;
        case 'V': return 47;
        case 'W': return 48;
        case 'X': return 49;
        case 'Y': return 50;
        case 'Z': return 51;

        // Satzzeichen (52+)
        case '.': return 52;
        case ',': return 53;
        case '!': return 54;
        case '?': return 55;
        case ';': return 56;
        case ':': return 57;
        case '-': return 58;
        case '_': return 59;
        case '(': return 60;
        case ')': return 61;
        case '[': return 62;
        case ']': return 63;
        case '{': return 64;
        case '}': return 65;
        case '"': return 66;
        case '\'': return 67;
        case '@': return 68;
        case '#': return 69;
        case '&': return 70;
        case '*': return 71;
        case '+': return 72;
        case '=': return 73;
        case '/': return 74;
        case '\\': return 75;
        case '|': return 76;
        case '<': return 77;
        case '>': return 78;
        case '^': return 79;
        case '%': return 80;
        case '$': return 81;
      
        // Zahlen 0-9 (82-91)
        case '0': return 82;
        case '1': return 83;
        case '2': return 84;
        case '3': return 85;
        case '4': return 86;
        case '5': return 87;
        case '6': return 88;
        case '7': return 89;
        case '8': return 90;
        case '9': return 91;
        
        // Ergänzung zu Satzzeichen (92 - 93 )
        case ' ': return 92;
        case '~': return 93;
        
        default: return -1; // Ungültige Eingabe
    }
}

int getAlphabetSpecialIndex_UI_RPGE(char* letter) {
    if (strcmp(letter, "\\$a$\\")) return 94;
    if (strcmp(letter, "\\$b$\\")) return 95;
    if (strcmp(letter, "\\$g$\\")) return 96;
    if (strcmp(letter, "\\$s$\\")) return 96;
    if (strcmp(letter, "\\$o$\\")) return 96;
    return -1;
}

int render_Text_UI_RPGE(SDL_Renderer* renderer, char* text, Vec2D vCoordinates, Vec2D vTable, Assetsheet_RPGE* font) {
    SDL_FRect dest;
    SDL_FRect src;
    dest.w = font->vPatchSize.x; 
    dest.h = font->vPatchSize.y;
    src.w = font->vPatchSize.x;
    src.h = font->vPatchSize.y; 
    int yTable = 0;
    int xTable = 0;
    for (int literal = 0; literal < strlen(text) && literal < vTable.x * vTable.y; literal++) {
        if (xTable >= vTable.x) {
            xTable = 0;
            yTable++;            
        }
        // render literal.
        int index; 
        if (text[literal] == '\n') {
            xTable = 0;
            yTable++;
            continue;
        }
        if (text[literal] == '\\') {
            char sp[6];
            strncpy(sp, text + literal, 6);
            int spi = getAlphabetSpecialIndex_UI_RPGE(sp);
            if (spi > -1) {
                index = spi;
                literal =+ 6;
            } else {
                index = getAlphabetIndex_UI_RPGE(text[literal]);
                if (index < 0 ) {
                    errno = EINVAL;
                    return 1;
                }
            }
        }

        Vec2D cor = {.x=vCoordinates.x + xTable * dest.w, .y=vCoordinates.y + yTable * dest.h};
        int renderTile_Assetsheet_G_RPGE(renderer, asset, index, cor);
        
        xTable++;
    }
    return 0;
}