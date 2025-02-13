#ifndef RPGE_E_SYSTEM_INFOS
#define RPGE_E_SYSTEM_INFOS

#include "RPGE_U_vec.h"

enum SYSTEM_RPGE {
	SNES,
	NES,
	GAME_BOY,
	GAME_BOY_ADVANCED
};

Vec2D getSystemResolution_RPGE(enum SYSTEM_RPGE res);

#endif