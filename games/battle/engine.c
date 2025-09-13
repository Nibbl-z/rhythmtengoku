#include "engines/battle.h"

struct Animation *battle_btn_animations[][2] = {
    { anim_fight_btn, anim_fight_btn_selected },
    { anim_act_btn, anim_act_btn_selected },
    { anim_item_btn, anim_item_btn_selected },
    { anim_spare_btn, anim_spare_btn_selected },
    { anim_defend_btn, anim_defend_btn_selected }
};

struct Animation *dialogue_animations[3] = {
    anim_dialogue_bzzt,
    anim_dialogue_blub,
    anim_dialogue_buble
};

struct Animation *action_icons[6] = {
    anim_action_icon_fight,
    anim_action_icon_act,
    anim_action_icon_item,
    anim_action_icon_spare,
    anim_action_icon_defend,
    anim_action_icon_face,
};

struct CompressedData *battle_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e3384] Graphics Table
struct GraphicsTable battle_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &battle_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &battle_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &battle_overlay,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &battle_overlay_selected,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &battle_box,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &battle_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ battle_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ battle_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

struct CueDefinition *battle_cue_index[] = {
    END_OF_CUE_INDEX
};

EngineEvent battle_common_events[] = {
    END_OF_COMMON_EVENT_LIST
};

EngineEvent battle_engine_events[] = {
    battle_set_win_script,
    battle_set_death_script
};

struct GameEngine battle_engine = {
    /* Size in Memory */ sizeof(struct BattleEngineData),
    /* Start Engine   */ battle_engine_start,
    /* Update Engine  */ battle_engine_update,
    /* Stop Engine    */ battle_engine_stop,
    /* Cue Index      */ battle_cue_index,
    /* Common Events  */ battle_common_events,
    /* Engine Events  */ battle_engine_events,
    /* Input Event    */ battle_input_event
};
