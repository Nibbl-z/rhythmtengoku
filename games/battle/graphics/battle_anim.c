#include "global.h"
#include "graphics.h"

#include "battle_anim_cells.inc.c"

// [D_088c9a60] Play-Yan Blink
struct Animation anim_play_yan_stand[] = {
    /* 000 */ { battle_cel000, 4 },
    /* End */ END_ANIMATION
};

// [D_088c9b08] Electric Fish Idle
struct Animation anim_battle_fish[] = {
    /* 000 */ { battle_cel021, 4 },
    /* 001 */ { battle_cel022, 4 },
    /* 002 */ { battle_cel023, 4 },
    /* 003 */ { battle_cel024, 4 },
    /* 004 */ { battle_cel025, 4 },
    /* 005 */ { battle_cel026, 4 },
    /* End */ END_ANIMATION
};