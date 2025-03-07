#include "engines/mr_upbeat.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gMrUpbeat ((struct MrUpbeatEngineData *)gCurrentEngineData)


/* MR. UPBEAT */


#include "asm/engines/mr_upbeat/asm_08034b14.s"

#include "asm/engines/mr_upbeat/asm_08034bf4.s"

#include "asm/engines/mr_upbeat/asm_08034d6c.s"

#include "asm/engines/mr_upbeat/asm_08034db0.s"

#include "asm/engines/mr_upbeat/asm_08034dd0.s"

#include "asm/engines/mr_upbeat/asm_08034e40.s"

#include "asm/engines/mr_upbeat/asm_08034e84.s"

#include "asm/engines/mr_upbeat/asm_08034eb4.s"

#include "asm/engines/mr_upbeat/asm_08034f18.s"

#include "asm/engines/mr_upbeat/asm_08034f64.s"

#include "asm/engines/mr_upbeat/asm_08034ff4.s"

#include "asm/engines/mr_upbeat/asm_08035094.s"

void func_08035168(void) {
}

#include "asm/engines/mr_upbeat/asm_0803516c.s"

void mr_upbeat_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void mr_upbeat_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), mr_upbeat_gfx_table, 0x2000);
    run_func_after_task(task, mr_upbeat_init_gfx3, 0);
}


void mr_upbeat_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), mr_upbeat_buffered_textures);
    run_func_after_task(task, mr_upbeat_init_gfx2, 0);
}

#include "asm/engines/mr_upbeat/asm_08035254.s"

void mr_upbeat_engine_event_stub(void) {
}

#include "asm/engines/mr_upbeat/asm_08035314.s"

void mr_upbeat_engine_update(void) {
    func_08034eb4();
    func_08035168();
}

void mr_upbeat_engine_stop(void) {
}

void mr_upbeat_cue_spawn(void) {
}

#include "asm/engines/mr_upbeat/asm_08035338.s"

void mr_upbeat_cue_despawn(void) {
}

#include "asm/engines/mr_upbeat/asm_08035358.s"

#include "asm/engines/mr_upbeat/asm_0803538c.s"

#include "asm/engines/mr_upbeat/asm_080353bc.s"

#include "asm/engines/mr_upbeat/asm_080353ec.s"

void mr_upbeat_input_event(void) {
    func_08034ff4();
}

void mr_upbeat_common_beat_animation(void) {
}

void mr_upbeat_common_display_text(void) {
}

void mr_upbeat_common_init_tutorial(void) {
}