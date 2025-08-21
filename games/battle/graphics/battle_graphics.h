#pragma once

#include "global.h"
#include "graphics.h"

/* BATTLE - ANIMATIONS */

extern struct Animation anim_play_yan_stand[];
extern struct Animation anim_battle_fish[];
extern struct Animation anim_fight_btn[];
extern struct Animation anim_fight_btn_selected[];


/* BATTLE - COMPRESSED GRAPHICS */

extern struct CompressedData battle_bg_tiles;
extern struct CompressedData battle_bg_map;
extern struct CompressedData battle_overlay;
extern struct CompressedData battle_obj; 

extern Palette battle_obj_pal[];
extern Palette battle_bg_pal[];