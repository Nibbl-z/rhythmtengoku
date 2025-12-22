#include "engines/molecano.h"

struct CompressedData *molecano_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable molecano_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &molecano_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &molecano_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* MG Map */ {
        /* Src.  */ &molecano_mg_map,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &molecano_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ molecano_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ molecano_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

struct CueDefinition molecano_slow_cue = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 24,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct MolecanoCue),
    /* Func. Spawn     */ molecano_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ molecano_cue_update,
    /* Func. Despawn   */ molecano_cue_despawn,
    /* Func. Hit       */ molecano_cue_hit,
    /* Func. Barely    */ molecano_cue_barely,
    /* Func. Miss      */ molecano_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

struct CueDefinition molecano_fast_cue = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 12,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct MolecanoCue),
    /* Func. Spawn     */ molecano_cue_spawn,
    /* Spawn Parameter */ 2,
    /* Func. Update    */ molecano_cue_update,
    /* Func. Despawn   */ molecano_cue_despawn,
    /* Func. Hit       */ molecano_cue_hit,
    /* Func. Barely    */ molecano_cue_barely,
    /* Func. Miss      */ molecano_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

struct CueDefinition molecano_slow_stop = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(B_BUTTON),
    /* Total Duration  */ 48,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct MolecanoCue),
    /* Func. Spawn     */ molecano_cue_spawn,
    /* Spawn Parameter */ 3,
    /* Func. Update    */ molecano_cue_update,
    /* Func. Despawn   */ molecano_cue_despawn,
    /* Func. Hit       */ molecano_cue_hit,
    /* Func. Barely    */ molecano_cue_barely,
    /* Func. Miss      */ molecano_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

struct CueDefinition molecano_slow_cue_right = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 24,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct MolecanoCue),
    /* Func. Spawn     */ molecano_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ molecano_cue_update,
    /* Func. Despawn   */ molecano_cue_despawn,
    /* Func. Hit       */ molecano_cue_hit,
    /* Func. Barely    */ molecano_cue_barely,
    /* Func. Miss      */ molecano_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

struct CueDefinition *molecano_cue_index[] = {
    &molecano_slow_cue,
    &molecano_fast_cue,
    &molecano_slow_stop,
    &molecano_slow_cue_right, // this is where it becomes a mess
    END_OF_CUE_INDEX
};

EngineEvent molecano_common_events[] = {
    END_OF_COMMON_EVENT_LIST
};

EngineEvent molecano_engine_events[] = {
    molecano_left_jump_fast,
    molecano_left_jump_slow
};

struct GameEngine molecano_engine = {
    /* Size in Memory */ sizeof(struct MolecanoEngineData),
    /* Start Engine   */ molecano_engine_start,
    /* Update Engine  */ molecano_engine_update,
    /* Stop Engine    */ molecano_engine_stop,
    /* Cue Index      */ molecano_cue_index,
    /* Common Events  */ molecano_common_events,
    /* Engine Events  */ molecano_engine_events,
    /* Input Event    */ molecano_input_event
};