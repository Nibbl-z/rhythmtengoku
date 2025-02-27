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

#include "asm/engines/tram_and_pauline/asm_08040434.s"

#include "asm/engines/tram_and_pauline/asm_080404c4.s"

#include "asm/engines/tram_and_pauline/asm_08040718.s"

#include "asm/engines/tram_and_pauline/asm_080409cc.s"

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

#include "asm/engines/tram_and_pauline/asm_08040b24.s"

#include "asm/engines/tram_and_pauline/asm_08040b58.s"

#include "asm/engines/tram_and_pauline/asm_08040bd4.s"
