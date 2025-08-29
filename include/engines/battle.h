#pragma once

#include "global.h"
#include "engines.h"

#include "games/battle/graphics/battle_graphics.h"

// Engine Enums:

#define BATTLE_PROJECTILE_AMOUNT 40

enum ProjectileBehaviour {
    PROJECTILE_DROPLET,
    PROJECTILE_SPARK_LEFT,
    PROJECTILE_SPARK_UP,
    PROJECTILE_SPARK_RIGHT
};

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
    struct Soul {
        s16 sprite;
        u8 damageBuffer;
    } soul;
    struct Projectile {
        u8 active;
        s16 sprite;
        u8 scaleX;
        u8 scaleY;
        u8 offsetX;
        u8 offsetY;
        u8 behaviour;
        s16 value1;
        s16 value2;
        s16 value3;
    } projectiles[BATTLE_PROJECTILE_AMOUNT];
    s16 buttonSprites[5];
    s16 menuSoulSprite;
    s16 fightIndicator;
    s16 fightTiming;
    u8 highlightedAction;
    u8 selectedAction;
    u8 isFighting;
    s16 enemyDamageSprite;
    s16 battlerDamageSprite;
    s16 dialogueBubbleSprite;
    s16 menuActionSprite;
    u8 dialogueTimer;
    u8 attackDamage;
    u8 bgScrollTimer;

    u8 projSpawnTimer;

    s16 healthbarSprite;
    struct TextPrinter *textPrinter;
};

extern struct CompressedData *battle_buffered_textures[];
extern struct GraphicsTable battle_gfx_table[];
extern struct Animation *battle_btn_animations[5][2];
extern struct Animation *dialogue_animations[3];
extern struct Animation *action_icons[6];

extern void battle_init_gfx3(void);
extern void battle_init_gfx2(void);
extern void battle_init_gfx1(void);
extern void battle_engine_start(u32 version);
extern void battle_engine_update(void);
extern void battle_engine_stop(void);
extern void battle_input_event(u32 pressed, u32 released);