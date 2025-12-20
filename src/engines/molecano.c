#include "engines/molecano.h"

// For readability.
#define gMolecano ((struct MolecanoEngineData *)gCurrentEngineData)

// Graphics Init. 3
void molecano_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

// Graphics Init. 2
void molecano_init_gfx2(void) {
    s32 task;
    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), molecano_gfx_table, 0x2000);
    run_func_after_task(task, molecano_init_gfx3, 0);
}

// Graphics Init. 1
void molecano_init_gfx1(void) {
    s32 task;
    
    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), molecano_buffered_textures);
    run_func_after_task(task, molecano_init_gfx2, 0);
}

// Game Engine Init.
void molecano_engine_start(u32 version) {
    struct Mole otherMole;
    struct Mole mole;
    
    gMolecano->version = version;
    molecano_init_gfx1();

    
    otherMole.sprite = sprite_create(gSpriteHandler, anim_mole_flip_stop, 0, 60, 100, 0x4000, 1, 0, 0);
    otherMole.jumpx = 0;
    otherMole.jumping = FALSE;

    gMolecano->otherMole = otherMole;
    
    mole.sprite = sprite_create(gSpriteHandler, anim_mole_stop, 0, 150, 100, 0x4000, 1, 0, 0);
    mole.jumpx = 0;
    mole.jumping = FALSE;

    gMolecano->mole = mole;

    gMolecano->jumpDuration = ticks_to_frames(24);
}

// Game Engine Update
void molecano_engine_update(void) {
    s16 yMod;
    u32 x;
    struct Mole *mole = &gMolecano->mole;
    struct Mole *otherMole = &gMolecano->otherMole;
    s32 jumpDuration = gMolecano->jumpDuration;

    if (mole->jumping == TRUE) {
        sprite_set_anim(gSpriteHandler, mole->sprite, anim_mole_jump, 0, 0, 0, 0);
        mole->jumpx += 1;
        
        sprite_set_y(gSpriteHandler, mole->sprite, 100 + ((mole->jumpx) * (mole->jumpx - jumpDuration)) / ((jumpDuration * jumpDuration) / 150));
       
        if (mole->jumpx > jumpDuration) {
            mole->jumping = FALSE;
            mole->jumpx = 0;
            sprite_set_y(gSpriteHandler, mole->sprite, 100);
        }
    }

    if (otherMole->jumping == TRUE) {
        otherMole->jumpx += 1;
        
        sprite_set_y(gSpriteHandler, otherMole->sprite, 100 + ((otherMole->jumpx) * (otherMole->jumpx - jumpDuration)) / ((jumpDuration * jumpDuration) / 150));
        sprite_set_anim(gSpriteHandler, otherMole->sprite, anim_mole_flip_jump, 0, 0, 0, 0);
        if (otherMole->jumpx > jumpDuration) {
            mole->jumping = TRUE;
            sprite_set_anim(gSpriteHandler, otherMole->sprite, anim_mole_flip_land, 0, 0, 0, 0);
            otherMole->jumping = FALSE;
            otherMole->jumpx = 0;
            sprite_set_y(gSpriteHandler, otherMole->sprite, 100);
        }
    }
}

// Game Engine Stop
void molecano_engine_stop(void) {}

// Input Event
void molecano_input_event(u32 pressed, u32 released) {
    
}

void molecano_cue_spawn(struct Cue *cue, struct MolecanoCue *data, u32 type) {
    // 1 - "1, 2" normal input
    // 2 - "1 2 3 4" normal
    // 3 - "1, 2" stop
    // 4 - "1 2 3 4" stop
    // this is horrible, there mightbe a better way to do it, but idc rn:P

    if (type == 1 || type == 2) {
        data->stop = FALSE;
    } else {
        data->stop = TRUE;
    }

    gMolecano->jumpDuration = ticks_to_frames(type % 2 == 0 ? 12 : 24);
    gMolecano->otherMole.jumpx = 0;
    gMolecano->otherMole.jumping = TRUE;
}

void molecano_cue_update(struct Cue *cue, struct MolecanoCue *data, u32 runningTime, u32 duration) {

}
void molecano_cue_despawn(struct Cue *cue, struct MolecanoCue *data) {

}
void molecano_cue_hit(struct Cue *cue, struct MolecanoCue *data) {
    if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_stop, 0, 0, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_land, 0, 0, 0, 0);
    }
    
}
void molecano_cue_barely(struct Cue *cue, struct MolecanoCue *data) {
     if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_stop, 0, 0, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_land, 0, 0, 0, 0);
    }
}
void molecano_cue_miss(struct Cue *cue, struct MolecanoCue *data) {
 if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_stop, 0, 0, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_land, 0, 0, 0, 0);
    }
}