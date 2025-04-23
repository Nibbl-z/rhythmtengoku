#include "engines/marching_orders.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gMarchingOrders ((struct MarchingOrdersEngineData *)gCurrentEngineData)


/* MARCHING ORDERS */


struct Animation* func_08034100(s32 anim) {
    if (anim < 0) {
        return NULL;
    } else {
        return marching_anim_table[anim][gMarchingOrders->version];
    }
}

void marching_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void marching_init_gfx2(void) {
    s32 task;
    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), marching_gfx_tables[gMarchingOrders->version], 0x2000);
    run_func_after_task(task, marching_init_gfx3, 0);
}

void marching_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), marching_buffered_textures);
    run_func_after_task(task, marching_init_gfx2, 0);
}

void marching_engine_start(u32 version) {
    struct PrintedTextAnim *textAnim;
    struct Marcher *marcher;
    u32 i;
    
    gMarchingOrders->version = version;

    marching_init_gfx1();
    scene_show_obj_layer();

    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 2);
    scene_set_bg_layer_display(BG_LAYER_2, FALSE, 0, 0, 0, 30, 1);
    scene_set_bg_layer_display(BG_LAYER_3, TRUE, 0, 0, 0, 31, 3);

    gMarchingOrders->font = scene_create_obj_font_printer(0x340, 2);
    textAnim = bmp_font_obj_print_l(gMarchingOrders->font, D_0805a670, 1, 0xe);

    gMarchingOrders->unk_40 = sprite_create(gSpriteHandler, textAnim, 0, 0x78, 0x16, 0, 0, 0, 0);

    for (i = 0; i < 4; i++) {
        marcher = &gMarchingOrders->marchers[i];
        marcher->sprite = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_STOP_BEAT), 0, 0x50 + (i * 0x28), 0x78, 0x4800, 1, 0x7f, 0);
        marcher->unk3 = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_HEAD_R), 0x7f, 0x50 + (i * 0x28), 0x78, 0x47f6, 1, 0x7f, 0x8000);
        sprite_attr_set(gSpriteHandler, marcher->unk3, 0x1000000);
        sprite_set_origin_x_y(gSpriteHandler, marcher->sprite, &D_03004b10.BG_OFS[3].x, &D_03004b10.BG_OFS[3].y);
        sprite_set_origin_x_y(gSpriteHandler, marcher->unk3, &D_03004b10.BG_OFS[3].x, &D_03004b10.BG_OFS[3].y);

        marcher->unk4 = 0;
        marcher->unk5 = 0;
        marcher->unk6 = 0;
    }

    gMarchingOrders->unk_45 = 0;
    gMarchingOrders->unk_38 = 0;
    gMarchingOrders->unk_3a = 0;

    gMarchingOrders->unk_42 = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_TUTORIAL_ICONS), 0, 200, 0x82, 0x479c, 0, 0, 0x8000);
    gMarchingOrders->unk_3c = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_COMMANDER), 0x7f, 0x1c, 0x7c, 0x4800, 1, 0x7f, 0);
    gMarchingOrders->unk_3e = 0;
    gMarchingOrders->unk_44 = 0;

    if (version == MARCHING_ORDERS_VER_2_UNUSED) {
        gameplay_set_input_buttons(A_BUTTON | B_BUTTON, 0);
    } else {
        gameplay_set_input_buttons(A_BUTTON | B_BUTTON | DPAD_LEFT | DPAD_RIGHT, 0);
    }
}

void marching_engine_event_stub(void) {
}

#include "asm/engines/marching_orders/asm_080343b8.s"

void func_08034544(u32 arg0) {
    u32 i;
    u32 unk = 3;

    if (arg0 & 0x100) {
        unk = 4;
    }

    arg0 = arg0 & 0xfffffeff;
    
    for (i = 0; i < unk; i++) {
        if (i == 3) {
            if (gMarchingOrders->unk_3a == 0) {
                func_080343b8(&gMarchingOrders->marchers[3], arg0);
                if (arg0 == 7) {
                    gMarchingOrders->unk_38 = 1;
                }
                if (arg0 == 8) {
                    gMarchingOrders->unk_38 = 0;
                }
            }
        } else {
            func_080343b8(&gMarchingOrders->marchers[i], arg0);
        }
    }
}

void func_080345cc(struct Marcher *marcher) {
    s32 x, y;
    s32 unk2;
    
    x = sprite_get_data(gSpriteHandler, marcher->sprite, SPRITE_DATA_X_POS);
    y = sprite_get_data(gSpriteHandler, marcher->sprite, SPRITE_DATA_Y_POS);

    if (marcher->unk5 != 0) {
        unk2 = sprite_get_anim_cel(gSpriteHandler, marcher->sprite);
        x += D_089e5368[unk2][gMarchingOrders->version].x;
        y += D_089e5368[unk2][gMarchingOrders->version].y;
        marcher->unk5++;

        if (marcher->unk6 == 0) {
            if (marcher->unk5 > ticks_to_frames(0x30)) {
                marcher->unk6 = 1;
                sprite_set_playback(gSpriteHandler, marcher->sprite, -1, 0, 0);
                sprite_set_anim_cel(gSpriteHandler, marcher->sprite, 3);
            }
        } else if (unk2 == 0) {
            func_080343b8(marcher, 0);
            return;
        }
    }

    sprite_set_x_y(gSpriteHandler, marcher->unk3, x, y); 
}

void func_080346b0(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        func_080345cc(&gMarchingOrders->marchers[i]);
    }

    if (gMarchingOrders->unk_3a != 0) {
        gMarchingOrders->unk_3a--;
    }
}

void func_080346e0(u32 arg0) {
    if (gMarchingOrders->unk_3e) {
        return;
    }
    
    switch(arg0) {
        case 0:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->unk_3c, func_08034100(MARCHING_ANIM_COMMANDER), 1, 1, 0x7f, 0);
            gMarchingOrders->unk_3e = ticks_to_frames(8);
            break;
        case 1:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->unk_3c, func_08034100(MARCHING_ANIM_COMMANDER), 0, 1, 0x7f, 0);
            sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_ANGRY_PUFF), 0, 0x1e, 0x28, 0x480a, 1, 0, 3);
            play_sound(&s_guntai_ikari_seqData);
            gMarchingOrders->unk_3e = ticks_to_frames(0x18);
            break;
        case 2:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->unk_3c, func_08034100(MARCHING_ANIM_COMMANDER_ANNOYED), 0, 1, 0x7f, 0);
            gMarchingOrders->unk_3e = ticks_to_frames(0x18);
            break;
    }
}

void func_080347c0(s32 arg0) {
    if (arg0 < 0) {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->unk_42, FALSE);
    } else {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->unk_42, TRUE);
        sprite_set_anim_cel(gSpriteHandler, gMarchingOrders->unk_42, arg0);
    }
}

void func_0803481c(void) {
    gMarchingOrders->unk_44 = 1;
}

// this is that conveyer thing at the end right
void func_0803482c(void) {
    if (gMarchingOrders->unk_44) {
        D_03004b10.BG_OFS[3].x--;
    }
}

void func_08034850(u8 arg0) {
    gMarchingOrders->unk_45 = arg0;
}

void marching_engine_update(void) {
    func_080346b0();
    func_0803482c();

    if (gMarchingOrders->unk_3e != 0) {
        gMarchingOrders->unk_3e--;
    }
}

void marching_engine_stop(void) {
}

void marching_cue_spawn(struct Cue *cue, struct MarchingOrdersCue *info, u32 command) {
    info->command = command;
}

u32 marching_cue_update(struct Cue *cue, struct MarchingOrdersCue *info, u32 runningTime, u32 released) {
    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void marching_cue_despawn(struct Cue *cue, struct MarchingOrdersCue *info) {
}

void marching_cue_hit(struct Cue *cue, struct MarchingOrdersCue *info, u32 pressed, u32 released) {
    struct Marcher *player = &gMarchingOrders->marchers[3];
    
    switch (info->command) {
        case 0:
            play_sound(gMarchingOrders->unk_38 ? &s_guntai_foot2_seqData : &s_guntai_foot1_seqData);   
            func_0803494c();
            break;
        case 1:
            func_08034988();
            break;
        case 2:
            func_080349ac();
            break;
        case 3:
            if (player->unk5) {
                play_sound(gMarchingOrders->unk_38 ? &s_guntai_foot2_seqData : &s_guntai_foot1_seqData);   
                func_080349d0();
            }
            break;
    }
}

void marching_cue_barely(struct Cue *cue, struct MarchingOrdersCue *info, u32 pressed, u32 released) {
    marching_cue_hit(cue, info, pressed, released);
    func_080346e0(2);
}

void marching_cue_miss(struct Cue *cue, struct MarchingOrdersCue *info) {
    beatscript_enable_loops();
    func_080346e0(1);
}

// probably the determining of which stepping animation to play
// and unk_38 is which foot to step
void func_0803494c(void) {
    u32 unk;

    if (gMarchingOrders->unk_38) {
        unk = 8;
    } else {
        unk = 7;
    }

    func_080343b8(&gMarchingOrders->marchers[3], unk);

    gMarchingOrders->unk_38 ^= 1;
    gMarchingOrders->unk_3a = ticks_to_frames(0xc);
}

void func_08034988(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 3);
    gMarchingOrders->unk_3a = ticks_to_frames(0xc);
}

void func_080349ac(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 4);
    gMarchingOrders->unk_3a = ticks_to_frames(0xc);
}

void func_080349d0(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 1);
    gMarchingOrders->unk_3a = ticks_to_frames(0xc);
}

void marching_input_event(u32 pressed, u32 released) {
    struct Marcher *player = &gMarchingOrders->marchers[3];
    
    if (pressed & A_BUTTON) {
        func_0803494c();
    }

    if (pressed & B_BUTTON && player->unk5) {
        func_080349d0();
    }

    if (pressed & DPAD_LEFT) {
        func_08034988();
    }    

    if (pressed & DPAD_RIGHT) {
        func_080349ac();
    }

    beatscript_enable_loops();
    func_080346e0(1);
}

void marching_common_beat_animation(void) {
}

void marching_common_display_text(const char *text) {
    struct PrintedTextAnim *textAnim;
    
    if (text == NULL) {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->unk_40, FALSE);
        scene_hide_bg_layer(BG_LAYER_2);
    } else {
        textAnim = bmp_font_obj_print_c(gMarchingOrders->font, text, 1, 0xc);
        delete_bmp_font_obj_text_anim(gMarchingOrders->font, gMarchingOrders->unk_40);
        sprite_set_anim(gSpriteHandler, gMarchingOrders->unk_40, textAnim, 0, 0, 0, 0);
        sprite_set_visible(gSpriteHandler, gMarchingOrders->unk_40, TRUE);
        scene_show_bg_layer(BG_LAYER_2);
    }
}

void marching_common_init_tutorial(void) {
}

void func_08034ae4(u32 arg0) {
    struct MarchingSfxData *sfx = &marching_sfx_table[gMarchingOrders->version][arg0];
    
    play_sound_w_pitch_volume(sfx->sound, sfx->volume, sfx->pitch);
}
