#include "editor_menu_ui.h"
#include "log.h"
#include <stdlib.h>

struct MenuUI *
createMenuInputAndLabel (char *label, int x, int y)
{
}

struct MenuUI *
settingsMenu ()
{
  // setup;
  struct MenuUI *ui = (struct MenuUI *)malloc (sizeof (struct MenuUI));
  ui->tilesheetLayer->cols = 12;
  ui->tilesheetLayer->rows = 8;
  ui->sizeTileX = 16;
  ui->sizeTileY = 16;
  ui->courser.x = 0;
  ui->courser.y = 0;
  ui->charLayer16bit = createMatrix (8, 12);
  ui->charLayer8bit = createMatrix (8 * 2, 12 * 2);
}

int
lookup8bitFont (char c)
{
  switch (c)
    {
    case '!':
      return 1;
    case '"':
      return 2;
    case '.':
      return 14;
    case '(':
      return 8;
    case ')':
      return 9;
    case '/':
      return 15;
    case 'A':
      return 33;
    case 'B':
      return 34;
    case 'C':
      return 35;
    case 'D':
      return 36;
    case 'E':
      return 37;
    case 'F':
      return 38;
    case 'G':
      return 39;
    case 'H':
      return 40;
    case 'I':
      return 41;
    case 'J':
      return 42;
    case 'K':
      return 43;
    case 'L':
      return 44;
    case 'M':
      return 45;
    case 'N':
      return 46;
    case 'O':
      return 47;
    case 'P':
      return 48;
    case 'Q':
      return 49;
    case 'R':
      return 50;
    case 'S':
      return 51;
    case 'T':
      return 52;
    case 'U':
      return 52;
    case 'V':
      return 52;
    case 'W':
      return 52;
    case 'X':
      return 52;
    case 'Y':
      return 52;
    case 'Z':
      return 52;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      log_info ("TODO: buchstaben lookuptable not defined yet for %s", c);
      break;
    default:
      // Standardfall, falls kein passender Wert gefunden wird
      break;
    }
}