#include "engines/space_dance.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gSpaceDance ((struct SpaceDanceEngineData *)gCurrentEngineData)


/* SPACE DANCE */


struct Animation *space_dance_get_anim(u32 anim) {
    return space_dance_anim_table[anim][gSpaceDance->version];
}

void space_dance_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void space_dance_init_gfx2(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), space_dance_gfx_tables[gSpaceDance->version], 0x2000);
    run_func_after_task(task, space_dance_init_gfx3, 0);
}

void space_dance_init_gfx1(void) {
    u32 data;

    func_0800c604(0);
    data = start_new_texture_loader(get_current_mem_id(), space_dance_buffered_textures);
    run_func_after_task(data, space_dance_init_gfx2, 0);
}

#include "asm/engines/space_dance/asm_0803d0b4.s"

void space_dance_engine_event_stub(void) {
}

#include "asm/engines/space_dance/asm_0803d2c0.s"

#include "asm/engines/space_dance/asm_0803d388.s"

void func_0803d3fc(u32 arg0) {
    gSpaceDance->unk_1a = arg0;
}

void func_0803d408(u32 arg0) {
    gSpaceDance->unk_1b = arg0;
}

#include "asm/engines/space_dance/asm_0803d414.s"

#include "asm/engines/space_dance/asm_0803d460.s"

#include "asm/engines/space_dance/asm_0803d478.s"

#include "asm/engines/space_dance/asm_0803d4bc.s"

void func_0803d4e0(void) {
    gSpaceDance->unk_34 = TRUE;
}

#include "asm/engines/space_dance/asm_0803d4f0.s"

void func_0803d588(u32 arg0) {
    gSpaceDance->unk_35 = arg0;
}

#include "asm/engines/space_dance/asm_0803d598.s"

void space_dance_engine_stop(void) {

}

void space_dance_cue_spawn(struct Cue *cue, struct SpaceDanceCue *info, u32 move) {
    info->pose = move;
}

#include "asm/engines/space_dance/asm_0803d5c4.s"

void space_dance_cue_despawn(struct Cue *cue, struct SpaceDanceCue *info) {
}

#include "asm/engines/space_dance/asm_0803d5e4.s"

#include "asm/engines/space_dance/asm_0803d5f4.s"

#include "asm/engines/space_dance/asm_0803d670.s"

#include "asm/engines/space_dance/asm_0803d6c0.s"

void space_dance_cue_barely(struct Cue *cue, struct SpaceDanceCue *info, u32 pressed, u32 released) {
    space_dance_cue_hit(cue, info, pressed, released);
    func_0803d670(0);
}

#include "asm/engines/space_dance/asm_0803d71c.s"

#include "asm/engines/space_dance/asm_0803d82c.s"

#include "asm/engines/space_dance/asm_0803d83c.s"

#include "asm/engines/space_dance/asm_0803d914.s"

#include "asm/engines/space_dance/asm_0803d9a0.s"

void space_dance_common_init_tutorial(void) {
    
}
