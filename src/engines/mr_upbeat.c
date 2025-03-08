#include "engines/mr_upbeat.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gMrUpbeat ((struct MrUpbeatEngineData *)gCurrentEngineData)


/* MR. UPBEAT */


#include "asm/engines/mr_upbeat/asm_08034b14.s"

#include "asm/engines/mr_upbeat/asm_08034bf4.s"

void func_08034d6c(void) {
    gMrUpbeat->unk_4e++;

    if (99 < gMrUpbeat->unk_4e) {
        gMrUpbeat->unk_4e = 99;
    }

    if (gMrUpbeat->unk_4e > gMrUpbeat->unk_50) {
        gMrUpbeat->unk_50 = gMrUpbeat->unk_4e;
        gMrUpbeat->unk_52 = 1;
    }

    func_08034bf4();
}

// save highscore?

void func_08034db0(void) {
    D_030046a8->data.unk294[0] = gMrUpbeat->unk_50;
}



void func_08034dd0(void) {
    struct Metronome *metronome = &gMrUpbeat->metronome;
    metronome->sprite = create_affine_sprite(anim_metronome_pendulum, 0, 0x78, 0x90, 0x480a, 0x100, 0, 1, 0, 0, 0);
    metronome->unk_4 = 0;
    metronome->unk_10 = 0x168;
    metronome->unk_18 = 0;
    metronome->unk_14 = 0;
    metronome->unk_20 = 0;
    metronome->unk_8 = 0x400;
    metronome->unk_c = 0;
    metronome->unk_21 = 0;

    affine_sprite_set_rotation(metronome->sprite, (s16)metronome->unk_10);
}

#include "asm/engines/mr_upbeat/asm_08034e40.s"

void func_08034e84(void) {
    func_08034e40();
    sprite_set_anim_cel(gSpriteHandler, gMrUpbeat->sprite, 0);
    play_sound(&s_metro_count1_seqData);
}

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

void mr_upbeat_engine_start(u32 version) {
    struct TextPrinter *textPrinter;
    
    gMrUpbeat->version = version;
    mr_upbeat_init_gfx1();
    scene_show_obj_layer();
    func_08034f64();
    func_08034dd0();
    func_08034b14();

    gMrUpbeat->sprite = sprite_create(gSpriteHandler, anim_mr_upbeat_beep, 0x7f, 0x78, 0x1e, 0x4864, 1, 0x7f, 0x8000);
    
    gMrUpbeat->unk_3c = 0xFFFFFFFF;
    func_08034e40();
    gMrUpbeat->unk_38 = 0;

    textPrinter = text_printer_create_new(get_current_mem_id(), 1, 0xf0, 0x1e);
    text_printer_set_x_y(textPrinter, 0, 100);
    text_printer_set_layer(textPrinter, 0x4800);
    text_printer_center_by_content(textPrinter, TRUE);
    text_printer_set_palette(textPrinter, 0);
    text_printer_set_colors(textPrinter, 0);
    gameplay_set_text_printer(textPrinter);
    gameplay_set_input_buttons(A_BUTTON, 0);
}

void mr_upbeat_engine_event_stub(void) {
}

void func_08035314(u32 arg0) {
    gMrUpbeat->unk_38 = arg0;
}

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

void mr_upbeat_cue_miss(void) {
    func_08035094(gMrUpbeat->metronome.unk_20);
}

void mr_upbeat_input_event(void) {
    func_08034ff4();
}

void mr_upbeat_common_beat_animation(void) {
}

void mr_upbeat_common_display_text(void) {
}

void mr_upbeat_common_init_tutorial(void) {
}