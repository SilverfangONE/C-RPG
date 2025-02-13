#include "RPGE_E_system_infos.h"
#include "RPGE_U_vec.h"

Vec2D getSystemResolution_RPGE(enum SYSTEM_RPGE res) {
    switch (res) {
        case NES:
            return (Vec2D) { 256, 240};
        case SNES:
            return (Vec2D) { 256, 224};
        case GAME_BOY:
            return (Vec2D) { 160, 144};        
        case GAME_BOY_ADVANCED:
            return (Vec2D) { 240, 160};
    }
    log_warn("Given res isn't available in SYSTEM_RES_RPGE!");
    return (Vec2D) { 0, 0};
}