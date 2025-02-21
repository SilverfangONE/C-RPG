#include "RPGE_D_tmap.h"
#include "RPGE_U_files.h"

Tilemap_G_RPGE* read_TMAP_RPGE(char *path) {
    // first two values. 
    char *fileString = readFile_UTIL(path);
    
    int valueIndex = 0;
    for(int i = 0; i < strnlen(fileString, sizeof(fileString)); i++) {
        if (fileString[i] == '')
        
        
        if (fileString[i] == ' ') {

        }
    }
}