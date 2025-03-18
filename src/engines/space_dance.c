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

void func_0803d2c0(u32 arg0) {
    u32 i;
    
    play_sound(space_dancer_sounds[arg0]);

    for (i = 0; i < 4; i++) {
        if (i != 3 || 2 < arg0) {       
            sprite_set_anim(gSpriteHandler, gSpaceDance->dancers[i], space_dance_get_anim(space_dancer_anim_map[arg0]), 0, 1, 0x7f, 0);
            gSpaceDance->unk_e[i] = ticks_to_frames(0x14);
        }
    }

    if (gSpaceDance->unk_1a != 0 && gSpaceDance->unk_1c == 0) {
        sprite_set_anim(gSpriteHandler,  gSpaceDance->unk_16, space_dance_get_anim(space_gramps_anim_map[arg0]), 0, 1, 0x7f, 0);
        gSpaceDance->unk_18 = ticks_to_frames(0x14);
    }
}

void func_0803d388(void) {
    struct Animation *anim;
    u32 i;

    for (i = 0; i < 4; i++) {
        if (gSpaceDance->unk_e[i] != 0) {
            gSpaceDance->unk_e[i]--;
        }
    }

    if (gSpaceDance->unk_18 != 0) {
        gSpaceDance->unk_18--;
    }

    if (gSpaceDance->unk_1c != 0) {
        gSpaceDance->unk_1c--;

        if (gSpaceDance->unk_1c == 0) {
            anim = space_dance_get_anim(3);
            sprite_set_anim(gSpriteHandler, gSpaceDance->unk_16, anim, 0x7f, 1, 0x7f, 0);
        }
    } 
}
void func_0803d3fc(u32 arg0) {
    gSpaceDance->unk_1a = arg0;
}

void func_0803d408(u32 arg0) {
    gSpaceDance->unk_1b = arg0;
}

void func_0803d414(u32 arg0) {
    struct Animation *anim;
    
    if (gSpaceDance->unk_18 == 0) {
        gSpaceDance->unk_1c = 0;
        anim = space_dance_get_anim(space_gramps_anim_map[arg0]);
        sprite_set_anim(gSpriteHandler, gSpaceDance->unk_16, anim, 0, 1, 0, 0);
    }
}


void func_0803d460(u32 arg0) {
    gSpaceDance->unk_28 = arg0;
    gSpaceDance->unk_29 = arg0 / 256;
}

// update bg scroll maybe?
void func_0803d478(void) {
    gSpaceDance->unk_20 += gSpaceDance->unk_28;
    gSpaceDance->unk_24 += gSpaceDance->unk_29;

    D_03004b10.BG_OFS[1].x = gSpaceDance->unk_20 >> 2;
    D_03004b10.BG_OFS[1].y = gSpaceDance->unk_24 >> 2;
    D_03004b10.BG_OFS[2].x = gSpaceDance->unk_20 >> 2;
    D_03004b10.BG_OFS[2].y = gSpaceDance->unk_24 >> 2;
} 

void func_0803d4bc(u32 arg0) {
    sprite_set_anim_cel(gSpriteHandler, gSpaceDance->unk_2c, arg0);
}

void func_0803d4e0(void) {
    gSpaceDance->unk_34 = TRUE;
}

void func_0803d4f0(void) {
    struct Animation *anim;
    
    if (gSpaceDance->unk_34 != 0) {
        anim = space_dance_get_anim(0x10);
        sprite_create(gSpriteHandler, anim, 0, gSpaceDance->unk_30, gSpaceDance->unk_32, 0x48d2, 1, 0, 3);
        gSpaceDance->unk_30 -= 0x18;
        gSpaceDance->unk_32 += 6;

        sprite_set_visible(gSpriteHandler, gSpaceDance->unk_2e, TRUE);
        sprite_set_x_y(gSpriteHandler, gSpaceDance->unk_2e, gSpaceDance->unk_30, gSpaceDance->unk_32);

        if (gSpaceDance->unk_30 < -0x10) {
            gSpaceDance->unk_34 = 0;
        } 
    }
}

void func_0803d588(u32 arg0) {
    gSpaceDance->unk_35 = arg0;
}

void space_dance_engine_update(void) {
    func_0803d388();
    func_0803d478();
    func_0803d4f0();

    if (gSpaceDance->unk_36 != 0) {
        gSpaceDance->unk_36--;
    }
}

void space_dance_engine_stop(void) {

}

void space_dance_cue_spawn(struct Cue *cue, struct SpaceDanceCue *info, u32 move) {
    info->pose = move;
}

u32 space_dance_cue_update(struct Cue *cue, struct SpaceDanceCue *info, u32 runningTime, u32 duration) {
    if (runningTime > ticks_to_frames(0x30) ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void space_dance_cue_despawn(struct Cue *cue, struct SpaceDanceCue *info) {
}

void func_0803d5e4(void) {
    gameplay_set_input_buttons(A_BUTTON | DPAD_DOWN | DPAD_RIGHT, 0);
}

void space_dance_cue_hit(struct Cue *cue, struct SpaceDanceCue *info, u32 pressed, u32 released) {
    s16 sprite = gSpaceDance->dancers[3];
    struct Animation *anim = space_dance_get_anim(space_dance_cue_anim_map[info->pose]);
    
    sprite_set_anim(gSpriteHandler, sprite, anim, 0, 1, 0x7f, 0);
    
    gSpaceDance->unk_e[3] = ticks_to_frames(0x14);
    
    gameplay_set_input_buttons(0, 0);

    schedule_function_call(get_current_mem_id(), func_0803d5e4, 0, ticks_to_frames(0x14));
}

void func_0803d670(u32 arg0) {
    struct Animation *anim;
    
    if (gSpaceDance->unk_1c == 0) {
        anim = space_dance_get_anim(0x1c);
        sprite_set_anim(gSpriteHandler, gSpaceDance->unk_16, anim, arg0, 1, 0x7f, 0);
        gSpaceDance->unk_1c = ticks_to_frames(0x24);
    }
}

void func_0803d6c0(u32 arg0) {
    struct Animation *anim = space_dance_get_anim(0x1b);
    sprite_set_anim(gSpriteHandler, gSpaceDance->unk_16, anim, arg0, 1, 0x7f, 0);

    gSpaceDance->unk_1c = ticks_to_frames(0x24);
}

void space_dance_cue_barely(struct Cue *cue, struct SpaceDanceCue *info, u32 pressed, u32 released) {
    space_dance_cue_hit(cue, info, pressed, released);
    func_0803d670(0);
}

void space_dance_cue_miss(struct Cue *cue, struct SpaceDanceCue *info) {
    s16 playerSprite = gSpaceDance->dancers[3];
    
    sprite_set_anim(gSpriteHandler, playerSprite, space_dance_get_anim(8), 0, 1, 0x7f, 0);
    gSpaceDance->unk_e[3] = ticks_to_frames(0x14);

    sprite_create(gSpriteHandler, space_dance_get_anim(0xD), 0, 200, D_089e6ebc[info->pose], 0x4819, 1, 0, 3);
    
    gameplay_set_input_buttons(0, 0);
    schedule_function_call(get_current_mem_id(), func_0803d5e4, 0, ticks_to_frames(0x10));
    
    func_0803d6c0(0);
    beatscript_enable_loops();

    stop_sound(&s_space_kou_right_seqData);
    stop_sound(&s_space_kou_down_seqData);
    stop_sound(&s_space_kou_punch_seqData);
    stop_sound(&s_space_ikeo_right_seqData);
    stop_sound(&s_space_ikeo_down_seqData);
    stop_sound(&s_space_ikeo_punch_seqData);
    play_sound(&s_witch_donats_seqData);
}


void func_0803d82c(void) {
    gameplay_set_input_buttons(A_BUTTON | DPAD_DOWN | DPAD_RIGHT, 0);
}

void space_dance_input_event(u32 pressed, u32 released) {
    struct Animation *poseAnim = NULL;

    if (pressed & A_BUTTON) {
        poseAnim = space_dance_get_anim(1);
    }

    if (pressed & DPAD_RIGHT) {
        poseAnim = space_dance_get_anim(0);
    }

    if (pressed & DPAD_DOWN) {
        poseAnim = space_dance_get_anim(2);
    }

    if (poseAnim != NULL) {
        sprite_set_anim(gSpriteHandler, gSpaceDance->dancers[3], poseAnim, 0, 1, 0x7f, 0);
        gSpaceDance->unk_e[3] = ticks_to_frames(0x14);

        gameplay_set_input_buttons(0, 0);
        schedule_function_call(get_current_mem_id(), func_0803d82c, 0, ticks_to_frames(0x14));

        play_sound(&s_tebyoushi_pati_seqData);

        if (gSpaceDance->unk_35 != 0 && gSpaceDance->unk_36 == 0) {
            play_sound_w_pitch_volume(&s_warai_solo_seqData, 0x40, 0);
            gSpaceDance->unk_36 = ticks_to_frames(0x30);
        }
    }

    beatscript_enable_loops();
}

void space_dance_common_beat_animation(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        if (gSpaceDance->unk_e[i] == 0) {
            sprite_set_anim(gSpriteHandler, gSpaceDance->dancers[i], space_dance_get_anim(7), 0, 1, 0x7f, 0);
        }
    }

    if (gSpaceDance->unk_18 == 0 && gSpaceDance->unk_1b != 0 && gSpaceDance->unk_1c == 0) {
        sprite_set_anim(gSpriteHandler, gSpaceDance->unk_16, space_dance_get_anim(3), 0, 1, 0x7f, 0);
    }
}

void space_dance_common_display_text(const char *text) {
    struct PrintedTextAnim *textAnim;
    
    if (text == NULL) {
        sprite_set_visible(gSpriteHandler, gSpaceDance->unk_1e, FALSE);
    } else {
        delete_bmp_font_obj_text_anim(gSpaceDance->unk, gSpaceDance->unk_1e);
        textAnim = bmp_font_obj_print_c(gSpaceDance->unk, text, 1, 0xc);
        
        sprite_set_anim(gSpriteHandler, gSpaceDance->unk_1e, textAnim, 0, 0, 0, 0);
        sprite_set_visible(gSpriteHandler, gSpaceDance->unk_1e, TRUE);
    }
}

void space_dance_common_init_tutorial(void) {
}
