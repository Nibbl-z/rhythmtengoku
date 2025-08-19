#include "engines/battle.h"
#include "src/text_printer.h"

// For readability.
#define gBattle ((struct BattleEngineData *)gCurrentEngineData)

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
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);
    battler = &gBattle->battler; 
    battler->sprite = sprite_create(gSpriteHandler, anim_play_yan_stand, 0, 40, 90, 0x4800, 1, 0, 0);

    enemy = &gBattle->enemy;
    enemy->sprite = sprite_create(gSpriteHandler, anim_battle_fish, 0, 182, 120, 0x4800, 1, 0, 0);

    gBattle->textPrinter = text_printer_create_new(get_current_mem_id(), 4, 200, 30);
    text_printer_set_x_y(gBattle->textPrinter, 10, 120);
    text_printer_set_colors(gBattle->textPrinter, 3);
    text_printer_set_string(gBattle->textPrinter, "* Biribiriuo blocks the way!");
    text_printer_set_layer(gBattle->textPrinter, 0x4f00);
}

// Game Engine Update
void battle_engine_update(void) {
    gBattle->bgScrollTimer += 1;

    if (gBattle->bgScrollTimer == 20) {
        gBattle->bgScrollTimer = 0;
        D_03004b10.BG_OFS[1].x += 1;
        D_03004b10.BG_OFS[1].y += 1;
    }

    text_printer_update(gBattle->textPrinter);
}

// Game Engine Stop
void battle_engine_stop(void) {
}

// Input Event
void battle_input_event(u32 pressed, u32 released) {
}