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

// initialize metronome
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

void func_08034e40(void) {
    if (-1 < gMrUpbeat->unk_3c) {
        force_cancel_task(gMrUpbeat->unk_3c);
    }

    gMrUpbeat->unk_3c = palette_fade_out(get_current_mem_id(), 0x14, 1, metronome_pal[2], 0, D_03004b10.objPalette[2]);
}

void func_08034e84(void) {
    func_08034e40();
    sprite_set_anim_cel(gSpriteHandler, gMrUpbeat->sprite, 0);
    play_sound(&s_metro_count1_seqData);
}

#include "asm/engines/mr_upbeat/asm_08034eb4.s"

void func_08034f18(u32 arg0) {
    u32 unk;
    u32 unk2;
    
    struct Metronome *metronome = &gMrUpbeat->metronome;
    
    if (metronome->unk_21 == 0) {
        play_sound(&s_metro_hit_seqData);
        metronome->unk_14 = 0;

        unk = ticks_to_frames(arg0);
        metronome->unk_18 = unk;
        metronome->unk_1c = unk / 2;
        unk2 = metronome->unk_8;
        metronome->unk_8 = metronome->unk_c;
        metronome->unk_c = unk2;

        metronome->unk_20 = metronome->unk_20 ^ 1; // huh
    }
}

// initialize mr upbeat
void func_08034f64(void) {
    struct MrUpbeat *mrUpbeat = &gMrUpbeat->mrUpbeat;
    
    mrUpbeat->sprite = sprite_create(gSpriteHandler, anim_mr_upbeat_l_step, 0x7f, 0x40, 0x40, 0x4800, 1, 0x7f, 0);
    sprite_set_x_y(gSpriteHandler, mrUpbeat->sprite, 0x78, 0x50);

    mrUpbeat->shadow = sprite_create(gSpriteHandler, anim_mr_upbeat_shadow, 1, 0x78, 0x50, 0x4814, 0, 0, 0);
    // these might be enums?
    mrUpbeat->unk_9 = 1;
    mrUpbeat->unk_8 = 2;
    mrUpbeat->unk_10 = 0;
}

#include "asm/engines/mr_upbeat/asm_08034ff4.s"

#include "asm/engines/mr_upbeat/asm_08035094.s"

void func_08035168(void) {
}

void func_0803516c(void) {
    struct MrUpbeat *mrUpbeat = &gMrUpbeat->mrUpbeat;

    sprite_set_anim(gSpriteHandler, mrUpbeat->sprite, mr_upbeat_game_over_anim[gMrUpbeat->unk_52][mrUpbeat->unk_c], 0, 1, 0x7f, 0);

    if (gMrUpbeat->unk_52) {
        gameplay_display_text(&D_0805a674);
        play_sound(&s_intro_pat1_seqData);
    } else {
        gameplay_display_text(&D_0805a684);
        play_sound(&s_gameover_fan_seqData);
    }
}

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

u32 mr_upbeat_cue_update(struct Cue *cue, struct MrUpbeatCue *info, u32 runningTime) {
    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;   
    } else {
        return FALSE;
    }
}

void mr_upbeat_cue_despawn(void) {
}


u32 func_08035358(void) {
    u32 unk;
    
    if (gMrUpbeat->mrUpbeat.unk_9 == 0) {
        unk = FALSE;
        if (gMrUpbeat->metronome.unk_20 == FALSE) { 
            unk = TRUE;
        }
    } else {
        unk = FALSE;
        if (gMrUpbeat->metronome.unk_20 == TRUE) { 
            unk = TRUE;
        }
    }

    return unk;
}

void mr_upbeat_cue_hit(struct Cue *cue, struct MrUpbeatCue *info, u32 pressed, u32 released) {
    struct Metronome *metronome = &gMrUpbeat->metronome;
    
    func_08034ff4();
    if (func_08035358() != FALSE) {
        gameplay_ignore_this_cue_result();
        gameplay_add_cue_result_miss(0);
        func_08035094(metronome->unk_20);
    }
}

void mr_upbeat_cue_barely(struct Cue *cue, struct MrUpbeatCue *info, u32 pressed, u32 released) {
    struct Metronome *metronome = &gMrUpbeat->metronome;
    
    func_08034ff4();
    if (func_08035358() != FALSE) {
        gameplay_ignore_this_cue_result();
        gameplay_add_cue_result_miss(0);
        func_08035094(metronome->unk_20);
    }
}

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