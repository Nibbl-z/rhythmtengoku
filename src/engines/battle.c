#include "engines/battle.h"
#include "src/text_printer.h"

// For readability.
#define gBattle ((struct BattleEngineData *)gCurrentEngineData)

enum ActionSelectionEnum {
    ACTION_FIGHT,
    ACTION_ACT,
    ACTION_ITEM,
    ACTION_SPARE,
    ACTION_DEFEND,
    ACTION_NONE
};

enum BattleStateEnum {
    STATE_CHOOSING,
    STATE_DIALOGUE,
    STATE_BATTLEBOX
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
    struct Soul *soul;

    gBattle->version = version;
    battle_init_gfx1();
    scene_set_bg_layer_display(BG_LAYER_3, TRUE, 0, 0, 0, 29, 1);
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 30, 1);
    scene_set_bg_layer_display(BG_LAYER_1, FALSE, 0, 0, 0, 28, 1);

    gBattle->selectedAction = ACTION_NONE;

    battler = &gBattle->battler; 
    battler->sprite = sprite_create(gSpriteHandler, anim_play_yan_stand, 0, 40, 90, 0x4800, 1, 0, 0);
    battler->health = 100;

    enemy = &gBattle->enemy;
    enemy->sprite = sprite_create(gSpriteHandler, anim_battle_fish, 0, 182, 120, 0x4800, 1, 0, 0);
    enemy->health = 250;

    soul = &gBattle->soul;
    soul->sprite = sprite_create(gSpriteHandler, anim_soul, 0, 117, 61, 0x4950, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, soul->sprite, FALSE);

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

    gBattle->menuSoulSprite = sprite_create(gSpriteHandler, anim_soul, 0, 5, 136, 0x4802, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->menuSoulSprite, FALSE);

    gBattle->fightIndicator = sprite_create(gSpriteHandler, anim_fight_indicator, 0, 16, 128, 0x4805, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->fightIndicator, FALSE);

    gBattle->fightTiming = sprite_create(gSpriteHandler, anim_fight_timing, 0, 100, 129, 0x4700, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->fightTiming, FALSE);

    gBattle->enemyDamageSprite = sprite_create(gSpriteHandler, anim_miss, 0, 210, 72, 0x4810, 0, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->enemyDamageSprite, FALSE);

    gBattle->dialogueBubbleSprite = sprite_create(gSpriteHandler, anim_dialogue_bzzt, 0, 146, 70, 0x4900, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->dialogueBubbleSprite, FALSE);

    gBattle->menuActionSprite = sprite_create(gSpriteHandler, action_icons[ACTION_NONE], 0, 69, 114, 0x4900, 1, 0, 0); 
    sprite_set_visible(gSpriteHandler, gBattle->menuActionSprite, FALSE);
}

void battle_fight_select(void) {
    gBattle->selectedAction = ACTION_FIGHT;
    text_printer_set_string(gBattle->textPrinter, " Biribiriuo");
    sprite_set_visible(gSpriteHandler, gBattle->menuSoulSprite, TRUE);
}

void battle_fight(void) {
    text_printer_set_string(gBattle->textPrinter, "");
    sprite_set_visible(gSpriteHandler, gBattle->menuSoulSprite, FALSE);
    sprite_set_visible(gSpriteHandler, gBattle->fightIndicator, TRUE);
    sprite_set_visible(gSpriteHandler, gBattle->fightTiming, TRUE);

    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 31, 1);
    gBattle->isFighting = TRUE;

    sprite_set_anim(gSpriteHandler, gBattle->menuActionSprite, action_icons[ACTION_FIGHT], 0, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gBattle->menuActionSprite, TRUE);

    sprite_set_visible(gSpriteHandler, gBattle->buttonSprites[0], FALSE);
    sprite_set_visible(gSpriteHandler, gBattle->buttonSprites[1], FALSE);
    sprite_set_visible(gSpriteHandler, gBattle->buttonSprites[2], FALSE);
    sprite_set_visible(gSpriteHandler, gBattle->buttonSprites[3], FALSE);
    sprite_set_visible(gSpriteHandler, gBattle->buttonSprites[4], FALSE);
}

// Update Choosing

void battle_update_choosing(void) {
    s16 attackX = 0;
    u8 damage = 0;
    // Update Attack

    if (gBattle->isFighting) {
        sprite_set_x(gSpriteHandler, gBattle->fightTiming, sprite_get_x(gSpriteHandler, gBattle->fightTiming) - 1);

        if (sprite_get_x(gSpriteHandler, gBattle->fightTiming) <= 1) {
            gBattle->selectedAction = ACTION_NONE;
            gBattle->isFighting = FALSE;
            gBattle->state = STATE_DIALOGUE;
            gBattle->dialogueTimer = 0;

            sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_miss, 0, 1, 0, 2);
            sprite_set_anim(gSpriteHandler, gBattle->menuActionSprite, action_icons[ACTION_NONE], 0, 1, 0, 0);

            return;
        }

        if (D_03004afc & A_BUTTON) {
            gBattle->selectedAction = ACTION_NONE;
            gBattle->isFighting = FALSE;
            gBattle->state = STATE_DIALOGUE;
            
            attackX = sprite_get_x(gSpriteHandler, gBattle->fightTiming);

            if (attackX >= 15 && attackX < 21) { // Critical hit
                sprite_set_x(gSpriteHandler, gBattle->fightTiming, 17);
                sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_75, 0, 1, 0, 2);
                damage = 75;

            } else if (attackX < 15 && attackX >= 11) { // Hitting slightly past critical
                sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_25, 0, 1, 0, 2);
                damage = 25;

            } else if (attackX >= 21 && attackX < 26) { // 50 damage
                sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_50, 0, 1, 0, 2);
                damage = 50;

            } else if (attackX >= 26 && attackX < 32) { // 25 damage
                sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_25, 0, 1, 0, 2);
                damage = 25;

            } else if (attackX >= 32 || attackX < 11) { // MISS!!!
                sprite_set_anim(gSpriteHandler, gBattle->enemyDamageSprite, anim_miss, 0, 1, 0, 2);
            }

            sprite_set_visible(gSpriteHandler, gBattle->enemyDamageSprite, TRUE);
            sprite_set_anim(gSpriteHandler, gBattle->menuActionSprite, action_icons[ACTION_NONE], 0, 1, 0, 0);

            gBattle->enemy.health -= damage; 

            return;
        }
    }

    // Action Selection

    if (D_03004afc & DPAD_RIGHT && gBattle->highlightedAction < ACTION_DEFEND && gBattle->selectedAction == ACTION_NONE) {
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->highlightedAction], get_battle_btn_animations(gBattle->highlightedAction, FALSE), 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->highlightedAction + 1], get_battle_btn_animations(gBattle->highlightedAction + 1, TRUE), 0, 0, 0, 0);
        
        gBattle->highlightedAction++;

        play_sound(&s_menu_cursor1_seqData);
    }

    if (D_03004afc & DPAD_LEFT && gBattle->highlightedAction > ACTION_FIGHT && gBattle->selectedAction == ACTION_NONE) {
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->highlightedAction], get_battle_btn_animations(gBattle->highlightedAction, FALSE), 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gBattle->buttonSprites[gBattle->highlightedAction - 1], get_battle_btn_animations(gBattle->highlightedAction - 1, TRUE), 0, 0, 0, 0);

        gBattle->highlightedAction--;

        play_sound(&s_menu_cursor1_seqData);
    }


    if (D_03004afc & A_BUTTON && gBattle->selectedAction != ACTION_NONE) {
        play_sound(&s_menu_kettei2_seqData);

        switch (gBattle->highlightedAction)
        {
            case ACTION_FIGHT:
                battle_fight();
                break;
            
            default:
                break;
        }
    }

    if (D_03004afc & A_BUTTON && gBattle->selectedAction == ACTION_NONE) {
        play_sound(&s_menu_kettei2_seqData);

        switch (gBattle->highlightedAction)
        {
            case ACTION_FIGHT:
                battle_fight_select();
                break;
            default:
                break;
        }
    }

    if (D_03004afc & B_BUTTON && gBattle->selectedAction != ACTION_NONE) {
        gBattle->selectedAction = ACTION_NONE;
        play_sound(&s_menu_cancel3_seqData);
        text_printer_set_string(gBattle->textPrinter, "* Biribiriuo blocks the way!");
        sprite_set_visible(gSpriteHandler, gBattle->menuSoulSprite, FALSE);
        sprite_set_visible(gSpriteHandler, gBattle->fightIndicator, FALSE);
        sprite_set_visible(gSpriteHandler, gBattle->fightTiming, FALSE);
    }
}

void battle_update_dialogue(void) {
    if (gBattle->dialogueTimer > 60) {
        sprite_set_visible(gSpriteHandler, gBattle->dialogueBubbleSprite, TRUE);
        sprite_set_visible(gSpriteHandler, gBattle->fightIndicator, FALSE);
        sprite_set_visible(gSpriteHandler, gBattle->fightTiming, FALSE);
        
        if (D_03004afc & A_BUTTON) {
            sprite_set_visible(gSpriteHandler, gBattle->dialogueBubbleSprite, FALSE);
            scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 28, 1);
            sprite_set_visible(gSpriteHandler, gBattle->soul.sprite, TRUE);
            gBattle->state = STATE_BATTLEBOX;
        }
    } else {
        sprite_set_anim(gSpriteHandler, gBattle->dialogueBubbleSprite, dialogue_animations[agb_random(3)], 0, 1, 0, 0);
        gBattle->dialogueTimer++;
    }
}

void battle_update_battlebox(void) {
    s16 x = sprite_get_x(gSpriteHandler, gBattle->soul.sprite);
    s16 y = sprite_get_y(gSpriteHandler, gBattle->soul.sprite);

    if (D_03004ac0 & DPAD_LEFT && x > 89) {
        sprite_set_x(gSpriteHandler, gBattle->soul.sprite, x - 1);
    }

    if (D_03004ac0 & DPAD_RIGHT && x < 144) {
        sprite_set_x(gSpriteHandler, gBattle->soul.sprite, x + 1);
    }

    if (D_03004ac0 & DPAD_UP && y > 33) {
        sprite_set_y(gSpriteHandler, gBattle->soul.sprite, y - 1);
    }

    if (D_03004ac0 & DPAD_DOWN && y < 88) {
        sprite_set_y(gSpriteHandler, gBattle->soul.sprite, y + 1);
    }
}

// Game Engine Update
void battle_engine_update(void) {
    gBattle->bgScrollTimer += 1;

    if (gBattle->bgScrollTimer == 20) {
        gBattle->bgScrollTimer = 0;
        D_03004b10.BG_OFS[3].x += 1;
        D_03004b10.BG_OFS[3].y += 1;
    }

    text_printer_update(gBattle->textPrinter);

    switch(gBattle->state) {
        case STATE_CHOOSING:
            battle_update_choosing();
            break;
        case STATE_DIALOGUE:
            battle_update_dialogue();
            break;
        case STATE_BATTLEBOX:
            battle_update_battlebox();
            break;
    }
}

// Game Engine Stop
void battle_engine_stop(void) {
}

// Input Event
void battle_input_event(u32 pressed, u32 released) {
    
}