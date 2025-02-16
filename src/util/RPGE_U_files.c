#include "RPGE_U_files.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile_UTIL(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        log_error("Fehler: Datei %s konnte nicht geöffnet werden!\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (!content)
    {
        log_error("Fehler: Speicher konnte nicht allokiert werden!\n");
        fclose(file);
        return NULL;
    }

    fread(content, 1, length, file);
    content[length] = '\0'; // Null-terminieren
    fclose(file);
    return content;
}
