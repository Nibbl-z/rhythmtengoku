#pragma once

#include "global.h"
#include "engines.h"

#include "games/battle/graphics/battle_graphics.h"

// Engine Types:
struct BattleEngineData {
    u8 version;
    u8 state;
    struct Battler {
        s16 sprite;
        u8 health;
    } battler;
    struct Enemy {
        s16 sprite;
        u8 health;
    } enemy;
    s16 buttonSprites[5];
    s16 menuSoulSprite;
    s16 fightIndicator;
    s16 fightTiming;
    u8 highlightedAction;
    u8 selectedAction;
    u8 isFighting;
    s16 enemyDamageSprite;
    u8 attackDamage;
    u8 bgScrollTimer;
    struct TextPrinter *textPrinter;
};

extern struct CompressedData *battle_buffered_textures[];
extern struct GraphicsTable battle_gfx_table[];
extern struct Animation *battle_btn_animations[5][2];

extern void battle_init_gfx3(void);
extern void battle_init_gfx2(void);
extern void battle_init_gfx1(void);
extern void battle_engine_start(u32 version);
extern void battle_engine_update(void);
extern void battle_engine_stop(void);
extern void battle_input_event(u32 pressed, u32 released);