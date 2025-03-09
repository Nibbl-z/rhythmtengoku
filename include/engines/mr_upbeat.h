#pragma once

#include "global.h"
#include "engines.h"

// shared?
#include "games/metronome/graphics/metronome_graphics.h"

// Engine Types:
struct MrUpbeatEngineData {
    u8 version;
    u8 pad[0x3];
    struct MrUpbeat {
        s16 sprite;
        s16 shadow;
        u8 unk_8;
        u8 unk_9;
        u16 unk_10;
        u8 unk_c;
    } mrUpbeat;
    struct Metronome {
        struct AffineSprite *sprite;
        u32 unk_4;
        u32 unk_8;
        u32 unk_c;
        u32 unk_10;
        u32 unk_14;
        u32 unk_18;
        u32 unk_1c;
        u8 unk_20;
        u8 unk_21;
    } metronome;
    s16 sprite; // 34
    u32 unk_38; // 38
    s32 unk_3c; // 3c
    // 54
    u8 pad2[0xd];
    u16 unk_4e; // 4c
    u16 unk_50; // 4e
    u8 unk_52;
};
struct MrUpbeatCue {
    /* add fields here */
};


// Engine Data:
extern const char D_0805a674[];
extern const char D_0805a684[];


// Engine Definition Data:
extern struct Animation *mr_upbeat_trip_anim[];
extern struct Animation *mr_upbeat_game_over_anim[][4];
extern struct CompressedGraphics *mr_upbeat_buffered_textures[];
extern struct GraphicsTable mr_upbeat_gfx_table[];


// Functions:
// extern ? func_08034b14(?);
// extern ? func_08034bf4(?);
extern void func_08034d6c(); // Engine Event 0x03 (?)
extern void func_08034db0(); // Engine Event 0x04 (?)
// extern ? func_08034dd0(?);
// extern ? func_08034e40(?);
extern void func_08034e84(); // Engine Event 0x02 (?)
// extern ? func_08034eb4(?);
extern void func_08034f18(); // Engine Event 0x00 (?)
// extern ? func_08034f64(?);
// extern ? func_08034ff4(?);
// extern ? func_08035094(?);
// extern ? func_08035168(?);
extern void func_0803516c(); // Engine Event 0x05 (?)
extern void mr_upbeat_init_gfx3(void); // Graphics Init. 3
extern void mr_upbeat_init_gfx2(void); // Graphics Init. 2
extern void mr_upbeat_init_gfx1(void); // Graphics Init. 1
extern void mr_upbeat_engine_start(u32 version); // Game Engine Start
extern void mr_upbeat_engine_event_stub(void); // Engine Event 0x06 (STUB)
extern void func_08035314(u32 arg0); // Engine Event 0x01 (?)
extern void mr_upbeat_engine_update(void); // Game Engine Update
extern void mr_upbeat_engine_stop(void); // Game Engine Stop
extern void mr_upbeat_cue_spawn(void); // Cue - Spawn
extern u32  mr_upbeat_cue_update(struct Cue *, struct MrUpbeatCue *, u32 runningTime); // Cue - Update
extern void mr_upbeat_cue_despawn(void); // Cue - Despawn
// extern ? func_08035358(?);
extern void mr_upbeat_cue_hit(struct Cue *, struct MrUpbeatCue *, u32 pressed, u32 released); // Cue - Hit
extern void mr_upbeat_cue_barely(struct Cue *, struct MrUpbeatCue *, u32 pressed, u32 released); // Cue - Barely
extern void mr_upbeat_cue_miss(void); // Cue - Miss
extern void mr_upbeat_input_event(void); // Input Event
extern void mr_upbeat_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void mr_upbeat_common_display_text(void); // Common Event 1 (Display Text, Unimplemented)
extern void mr_upbeat_common_init_tutorial(void); // Common Event 2 (Init. Tutorial, Unimplemented)
