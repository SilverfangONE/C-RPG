#include "RPGE_U_string.h"
#include <string.h>

void strncpys_UTIL (char* dest, char* src)
{
    strncpy(dest, src, sizeof(dest) - 1);
    dest[sizeof(dest)] = '\0';
}

void strc_UTIL (char* string)
{
    if (string == NULL)
    {
        log_trace("strc_UTIL(): string is NULL");
        return;
    }
    for (int i = 0; i < strlen(string); i++) 
    {  
        string[i] = 0;
    }
}