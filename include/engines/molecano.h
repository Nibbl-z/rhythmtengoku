#pragma once

#include "global.h"
#include "engines.h"

#include "games/molecano/graphics/molecano_graphics.h"

// Engine Types:

struct Mole {
    s16 sprite;
    s16 impactSprite;
    
};

struct MolecanoEngineData {
    u8 version;
    struct Mole otherMole;
    struct Mole mole;
    struct Cart {
        s16 sprite;
    };
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