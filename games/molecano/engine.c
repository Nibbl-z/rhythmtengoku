#include "engines/molecano.h"

struct CompressedData *molecano_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable molecano_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &molecano_obj,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &molecano_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &molecano_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ molecano_pal,
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

struct CueDefinition *molecano_cue_index[] = {
    END_OF_CUE_INDEX
};

EngineEvent molecano_common_events[] = {
    END_OF_COMMON_EVENT_LIST
};

EngineEvent molecano_engine_events[] = {

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