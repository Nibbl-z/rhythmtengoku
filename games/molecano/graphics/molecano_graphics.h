#pragma once

#include "global.h"
#include "graphics.h"

/* MOLECANO - ANIMATIONS */

extern struct Animation anim_mole_jump[];
extern struct Animation anim_mole_land[];
extern struct Animation anim_mole_stop[];
extern struct Animation anim_mole_flip_jump[];
extern struct Animation anim_mole_flip_land[];
extern struct Animation anim_mole_flip_stop[];
extern struct Animation anim_cart_stop[];
extern struct Animation anim_cart_left[];
extern struct Animation anim_cart_right[];
extern struct Animation anim_wheel_spin[];

/* NIGHT WALK - COMPRESSED GRAPHICS */

extern struct CompressedData molecano_obj;
extern struct CompressedData molecano_bg_tiles;
extern struct CompressedData molecano_bg_map;
extern struct CompressedData molecano_mg_map;
/* NIGHT WALK - PALETTES */

extern Palette molecano_pal[];
extern Palette molecano_bg_pal[];
