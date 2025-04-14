#include "engines/drum_live_menu.h"

// For readability.
#define gDrumLiveMenu ((struct DrumLiveMenuEngineData *)gCurrentEngineData)


/* LIVE MENU */


void drum_live_menu_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void drum_live_menu_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), drum_live_menu_gfx_table, 0x2000);
    run_func_after_task(task, drum_live_menu_init_gfx3, 0);
}

void drum_live_menu_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), drum_live_menu_buffered_textures);
    run_func_after_task(task, drum_live_menu_init_gfx2, 0);
}

void drum_live_menu_engine_start(u32 version) {
    struct TextPrinter *printer;
    u32 i;
    s16 sprite;
    u32 unk;
    
    gDrumLiveMenu->version = version;

    drum_live_menu_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, FALSE, 0, 0, 0, 0x1d, 0x8001);

    printer = text_printer_create_new(get_current_mem_id(), 8, 0x94, 0x1e);
    text_printer_set_x_y(printer, 0x5c, 0x28);
    text_printer_set_layer(printer, 0x4800);
    text_printer_center_by_content(printer, FALSE);
    text_printer_set_palette(printer, 4);
    text_printer_set_colors(printer, 0);
    text_printer_set_x_controller(printer, &gDrumLiveMenu->unk14);
    gameplay_set_text_printer(printer);
    gameplay_set_text_advance_icon(1);
    func_08036e10(0);

    gDrumLiveMenu->printer = printer;

    for (i = 0; i < 3; i++) {
        sprite = sprite_create(gSpriteHandler, anim_drum_live_menu_poster, i, 8, i * 0x100 + 0x20, 0x4a00, 0, 0, 0);
        sprite_set_origin_x_y(gSpriteHandler, sprite, 0, &D_03004b10.BG_OFS[1].y);
    }

    gDrumLiveMenu->unk16 = sprite_create(gSpriteHandler, anim_drum_live_menu_arrow_up, 0, 0x2c, 0x50, 0x800, 1, 0, 0x8000);
    gDrumLiveMenu->unk18 = sprite_create(gSpriteHandler, anim_drum_live_menu_arrow_down, 0, 0x2c, 0x50, 0x800, 1, 0, 0x8000);

    sprite_set_origin_x_y(gSpriteHandler, gDrumLiveMenu->unk16, 0, &gDrumLiveMenu->unk14);
    sprite_set_origin_x_y(gSpriteHandler, gDrumLiveMenu->unk18, 0, &gDrumLiveMenu->unk14);

    gDrumLiveMenu->unk1a = sprite_create(gSpriteHandler, anim_drum_live_menu_start_icon, 0, 0xf0, 0xa0, 0x800, 1, 0, 0x8000);
    
    gDrumLiveMenu->unk8 = 0;
    gDrumLiveMenu->unk9 = 0;
    gDrumLiveMenu->unka = 0x14;
    gDrumLiveMenu->unk10 = 0;
    gDrumLiveMenu->unkc = 0;
    gDrumLiveMenu->unk14 = 0;

    gameplay_set_input_buttons(0, 0);
}

void drum_live_menu_engine_event_stub(void) {
}

void func_08036e10(u32 arg0) {
    gameplay_display_text(drum_live_menu_poster_desc[arg0]);
}

void func_08036e28(void) {
    u32 unk;
    
    if (gDrumLiveMenu->unk9 == 0) {
        return;
    }

    unk = gDrumLiveMenu->unk8;
    
    if (D_03004afc & DPAD_UP && unk != 0) {
        unk--;
        play_sound(&s_keytoy_count2_seqData);
    }

    if (D_03004afc & DPAD_DOWN && unk < 2) {
        unk++;
        play_sound(&s_keytoy_count1_seqData);
    }

    if (gDrumLiveMenu->unk8 != unk) {
        gDrumLiveMenu->unk8 = unk;
        func_08036e10(unk);

        gDrumLiveMenu->unk10 = unk << 0x10;
        gDrumLiveMenu->unka = 0x28;

        sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk1a, FALSE);
        sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk16, FALSE);
        sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk18, FALSE);
    }
}

void func_08036ec8(void) {
    s32 unk;
    s32 unk2;

    unk = gDrumLiveMenu->unk10 - gDrumLiveMenu->unkc;
    unk2 = unk;
    
    if (unk < 0) {
        unk2 = -unk;    
    }
    
    if (unk2 < 0x200) {
        gDrumLiveMenu->unkc = gDrumLiveMenu->unk10;
    } else {
        gDrumLiveMenu->unkc += (unk * 0x20) >> 8;
    }

    D_03004b10.BG_OFS[1].y = gDrumLiveMenu->unkc >> 8;
    gDrumLiveMenu->unk14 = (gDrumLiveMenu->unkc >> 8) + gDrumLiveMenu->unk8 * -0x100;
}

void func_08036f18(void) {
    if (gDrumLiveMenu->unk9 == 0) {
        return;
    }

    if (gDrumLiveMenu->unka == 0) {
        return;
    }

    gDrumLiveMenu->unka--;

    if (gDrumLiveMenu->unka != 0) {
        return;
    }

    sprite_set_anim_cel(gSpriteHandler, gDrumLiveMenu->unk16, 1);
    sprite_set_anim_cel(gSpriteHandler, gDrumLiveMenu->unk18, 1);

    if (gDrumLiveMenu->unk8 != 0) {
        sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk16, TRUE);
    }

    if (gDrumLiveMenu->unk8 < 2) {
        sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk18, TRUE);
    }

    sprite_set_visible(gSpriteHandler, gDrumLiveMenu->unk1a, TRUE);
}

void func_08036f94(void) {
    gDrumLiveMenu->unk9 = 1;
    set_pause_beatscript_scene(TRUE);
}

void func_08036fac(void) {
    if (gDrumLiveMenu->unk9) {
        if (gDrumLiveMenu->unka == 0 && D_03004afc & A_BUTTON) {
            gDrumLiveMenu->unk9 = 0;

            gameplay_set_inter_engine_variable(0, gDrumLiveMenu->unk8);
            set_pause_beatscript_scene(FALSE);
            play_sound(&s_menu_kettei2_seqData);
        }
    }
}

void func_08036ff4(void) {
    if (gDrumLiveMenu->unk9) {
        if (gDrumLiveMenu->unka == 0) {
            if (D_03004afc & B_BUTTON) {
                gDrumLiveMenu->unk9 = 0;
                set_next_scene(get_scene_trans_target(get_current_scene_trans_target()));
                gameplay_skip_tutorial();

                play_sound(&s_menu_cancel3_seqData);
            }
        }
    }
}

void drum_live_menu_engine_update(void) {
    func_08036fac();
    func_08036ff4();
    func_08036e28();
    func_08036ec8();
    func_08036f18();
}

void drum_live_menu_engine_stop(void) {
}

void drum_live_menu_cue_spawn(struct Cue *cue, struct DrumLiveMenuCue *info) {
}

u32 drum_live_menu_cue_update(struct Cue *cue, struct DrumLiveMenuCue *info, u32 runningTime, u32 duration) {
    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void drum_live_menu_cue_despawn(struct Cue *cue, struct DrumLiveMenuCue *info) {
}

void drum_live_menu_cue_hit(struct Cue *cue, struct DrumLiveMenuCue *info, u32 pressed, u32 released) {
}

void drum_live_menu_cue_barely(struct Cue *cue, struct DrumLiveMenuCue *info, u32 pressed, u32 released) {
}

void drum_live_menu_cue_miss(struct Cue *cue, struct DrumLiveMenuCue *info) {
}

void drum_live_menu_input_event(u32 pressed, u32 released) {
}

void drum_live_menu_common_beat_animation(void) {
}

void drum_live_menu_common_display_text(void) {
}

void drum_live_menu_common_init_tutorial(void) {
}
