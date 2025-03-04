#include "engines/tram_and_pauline.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gTramPauline ((struct TramPaulineEngineData *)gCurrentEngineData)


/* TRAM & PAULINE */

void tram_pauline_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void tram_pauline_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), tram_pauline_gfx_tables[gTramPauline->version], 0x2000);
    run_func_after_task(task, tram_pauline_init_gfx3, 0);
}

void tram_pauline_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), tram_pauline_buffered_textures);
    run_func_after_task(task, tram_pauline_init_gfx2, 0);
}

#include "asm/engines/tram_and_pauline/asm_0803fd10.s"

#include "asm/engines/tram_and_pauline/asm_08040064.s"

#include "asm/engines/tram_and_pauline/asm_080400d0.s"

#include "asm/engines/tram_and_pauline/asm_0804016c.s"

#include "asm/engines/tram_and_pauline/asm_08040314.s"


void func_08040434(u32 arg0) { 
    gTramPauline->unk = arg0;
    
    switch (arg0) {
        case 0:
            sprite_set_x_y(gSpriteHandler, gTramPauline->unk2, 0x50, 0x40);
            break;
        case 1:
            sprite_set_x_y(gSpriteHandler, gTramPauline->unk2, 0xa0, 0x40);
            break;
        case 2:
            sprite_set_x_y(gSpriteHandler, gTramPauline->unk2, 0x78, 0x40);
            break;
        case 3:
            sprite_set_x_y(gSpriteHandler, gTramPauline->unk2, 0x78, 0x40);
            sprite_set_visible(gSpriteHandler, gTramPauline->unk3, FALSE);
            break;
    }
}

#include "asm/engines/tram_and_pauline/asm_080404c4.s"

#include "asm/engines/tram_and_pauline/asm_08040718.s"

void tram_pauline_engine_update() {
    s32 unk;
    s32 unk2;
    s16 pos;
    
    func_08040718();

    // this is probably the curtains opening thing
    
    if (gTramPauline->version != 1) {
        return;
    }

    if (gTramPauline->curtainScroll > 0x9fff) {
        return;
    }

    unk = ticks_to_frames(0xc0);
    gTramPauline->curtainScroll += 0xa000 / unk;

    pos = gTramPauline->curtainScroll * 0x100 >> 0x10;
    
    scene_set_bg_layer_pos(BG_LAYER_1, 0, pos);
}

void tram_pauline_engine_stop(void) {
}

void tram_pauline_cue_spawn(struct Cue *cue, struct TramPaulineCue *info, u32 character) {
    info->unk = character;
}

#include "asm/engines/tram_and_pauline/asm_08040a20.s"

void tram_pauline_cue_despawn(struct Cue *cue, struct TramPaulineCue *info) {
}

#include "asm/engines/tram_and_pauline/asm_08040a84.s"

void tram_pauline_cue_barely(struct Cue *cue, struct TramPaulineCue *info, u32 pressed, u32 released) {
    func_08040314(info->unk);
    beatscript_enable_loops();
}

void tram_pauline_cue_miss(struct Cue *cue, struct TramPaulineCue *info) {
    beatscript_enable_loops();
}

void tram_pauline_input_event(u32 pressed, u32 released) {
}

void tram_pauline_common_beat_animation(void) {
    u8 i;
    
    for (i = 0; i <= 1; i++) {
        if (gTramPauline->foxes[i].unk <= 1) {
           gTramPauline->foxes[i].unk4 = 0;
        }
    }
}

#include "asm/engines/tram_and_pauline/asm_08040b58.s"

#include "asm/engines/tram_and_pauline/asm_08040bd4.s"
