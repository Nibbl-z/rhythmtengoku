#include "engines/battle.h"
#include "src/text_printer.h"

// For readability.
#define gBattle ((struct BattleEngineData *)gCurrentEngineData)

enum ActionSelectionEnum {
    ACTION_FIGHT,
    ACTION_ACT,
    ACTION_ITEM,
    ACTION_SPARE,
    ACTION_DEFEND
};

struct Animation *get_battle_btn_animations(u32 selection, u32 isSelected) {
    return battle_btn_animations[selection][isSelected];
}

// Graphics Init. 3
void battle_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

// Graphics Init. 2
void battle_init_gfx2(void) {
    s32 task;
    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), battle_gfx_table, 0x2000);
    run_func_after_task(task, battle_init_gfx3, 0);
}

// Graphics Init. 1
void battle_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), battle_buffered_textures);
    run_func_after_task(task, battle_init_gfx2, 0);
}

// Game Engine Init.
void battle_engine_start(u32 version) {
    struct Battler *battler;
    struct Enemy *enemy;

    gBattle->version = version;
    battle_init_gfx1();
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 29, 1);
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 30, 1);
    battler = &gBattle->battler; 
    battler->sprite = sprite_create(gSpriteHandler, anim_play_yan_stand, 0, 40, 90, 0x4800, 1, 0, 0);

    enemy = &gBattle->enemy;
    enemy->sprite = sprite_create(gSpriteHandler, anim_battle_fish, 0, 182, 120, 0x4800, 1, 0, 0);

    gBattle->textPrinter = text_printer_create_new(get_current_mem_id(), 4, 200, 30);
    text_printer_set_x_y(gBattle->textPrinter, 10, 140);
    text_printer_set_colors(gBattle->textPrinter, 1);
    text_printer_set_string(gBattle->textPrinter, "* Biribiriuo blocks the way!");
    text_printer_set_layer(gBattle->textPrinter, 0x4f00);

    gBattle->buttonSprites[0] = sprite_create(gSpriteHandler, get_battle_btn_animations(ACTION_FIGHT, TRUE), 0, 73, 111, 0x4801, 1, 0, 0);
    gBattle->buttonSprites[1] = sprite_create(gSpriteHandler, get_battle_btn_animations(ACTION_ACT, FALSE), 0, 89, 111, 0x4801, 1, 0, 0);
    gBattle->buttonSprites[2] = sprite_create(gSpriteHandler, get_battle_btn_animations(ACTION_ITEM, FALSE), 0, 105, 111, 0x4801, 1, 0, 0);
    gBattle->buttonSprites[3] = sprite_create(gSpriteHandler, get_battle_btn_animations(ACTION_SPARE, FALSE), 0, 121, 111, 0x4801, 1, 0, 0);
    gBattle->buttonSprites[4] = sprite_create(gSpriteHandler, get_battle_btn_animations(ACTION_DEFEND, FALSE), 0, 137, 111, 0x4801, 1, 0, 0); 
}

// Game Engine Update
void battle_engine_update(void) {
    gBattle->bgScrollTimer += 1;

    if (gBattle->bgScrollTimer == 20) {
        gBattle->bgScrollTimer = 0;
        D_03004b10.BG_OFS[2].x += 1;
        D_03004b10.BG_OFS[2].y += 1;
    }

    text_printer_update(gBattle->textPrinter);

    // Action Selection

    if (D_03004afc & DPAD_RIGHT && gBattle->selectedAction < ACTION_DEFEND) {
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->selectedAction], get_battle_btn_animations(gBattle->selectedAction, FALSE), 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->selectedAction + 1], get_battle_btn_animations(gBattle->selectedAction + 1, TRUE), 0, 0, 0, 0);
        
        gBattle->selectedAction++;

        play_sound(&s_menu_cursor1_seqData);
    }

    if (D_03004afc & DPAD_LEFT && gBattle->selectedAction > ACTION_FIGHT) {
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->selectedAction], get_battle_btn_animations(gBattle->selectedAction, FALSE), 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->selectedAction - 1], get_battle_btn_animations(gBattle->selectedAction - 1, TRUE), 0, 0, 0, 0);

        gBattle->selectedAction--;

        play_sound(&s_menu_cursor1_seqData);
    }

    if (D_03004afc & A_BUTTON) {
        play_sound(&s_menu_kettei2_seqData);
    }
}

// Game Engine Stop
void battle_engine_stop(void) {
}

// Input Event
void battle_input_event(u32 pressed, u32 released) {
    
}