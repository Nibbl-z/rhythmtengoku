#pragma once

#include "global.h"
#include "graphics.h"

/* BATTLE - ANIMATIONS */

extern struct Animation anim_play_yan_stand[];
extern struct Animation anim_battle_fish[];
extern struct Animation anim_fight_btn[];
extern struct Animation anim_fight_btn_selected[];

extern struct Animation anim_act_btn[];
extern struct Animation anim_act_btn_selected[];

extern struct Animation anim_item_btn[];
extern struct Animation anim_item_btn_selected[];

extern struct Animation anim_spare_btn[];
extern struct Animation anim_spare_btn_selected[];

extern struct Animation anim_defend_btn[];
extern struct Animation anim_defend_btn_selected[];

extern struct Animation anim_soul[];

extern struct Animation anim_fight_indicator[];
extern struct Animation anim_fight_timing[];
extern struct Animation anim_miss[];
extern struct Animation anim_75[];
extern struct Animation anim_50[];
extern struct Animation anim_25[];


/* BATTLE - COMPRESSED GRAPHICS */

extern struct CompressedData battle_bg_tiles;
extern struct CompressedData battle_bg_map;
extern struct CompressedData battle_overlay;
extern struct CompressedData battle_obj; 

extern Palette battle_obj_pal[];
extern Palette battle_bg_pal[];