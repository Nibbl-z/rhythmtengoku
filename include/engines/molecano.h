#pragma once

#include "global.h"
#include "engines.h"

#include "games/molecano/graphics/molecano_graphics.h"

// Engine Types:

struct Mole {
    s16 sprite;
    s16 impactSprite;
    u8 jumping;
    s32 jumpx;
};

struct MolecanoEngineData {
    u8 version;
    s32 jumpDuration;
    u8 stopOnNext;
    struct Mole otherMole;
    struct Mole mole;
    struct Cart {
        s16 sprite;
        s16 leftWheel;
        s16 rightWheel;
        u8 moving;
    } cart;
};

// i dont think i need anything?
struct MolecanoCue {
    u8 stop;
};

extern struct CompressedData *molecano_buffered_textures[];
extern struct GraphicsTable molecano_gfx_table[];

extern void molecano_init_gfx3(void);
extern void molecano_init_gfx2(void);
extern void molecano_init_gfx1(void);
extern void molecano_engine_start(u32 version);
extern void molecano_engine_update(void);
extern void molecano_engine_stop(void);
extern void molecano_input_event(u32 pressed, u32 released);
extern void molecano_cue_spawn(struct Cue *, struct MolecanoCue *, u32);
extern void molecano_cue_update(struct Cue *, struct MolecanoCue *, u32, u32);
extern void molecano_cue_despawn(struct Cue *, struct MolecanoCue *);
extern void molecano_cue_hit(struct Cue *, struct MolecanoCue *);
extern void molecano_cue_barely(struct Cue *, struct MolecanoCue *);
extern void molecano_cue_miss(struct Cue *, struct MolecanoCue *);