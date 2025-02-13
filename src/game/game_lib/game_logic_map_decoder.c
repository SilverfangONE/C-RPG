/*

#include "game_logic_map_decoder.h"
#include "game_util.h"
#include "game_components.h"

// AB STATUS CODE 100 - 199 TRIGGER;
const int SPAWN_PLAYER = 101;
const int LOAD_SUB = 101;
const int LOAD_ENV = 102;
const int ITEM = 200;

void decodeLogicMap(Matrix* matrix, int col, int row) {
    int cell = getMatrixCell(matrix, col, row);
    if(!cell) {
        return;
    }
    switch(cell) {
        case SPAWN_PLAYER:
    }
}


*/