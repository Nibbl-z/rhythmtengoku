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
    struct Cart cart;

    scene_show_obj_layer(); // Init. BG Layers
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 29, 2); // Init. BG1
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 30, 2); // Init. BG2 ?

    gameplay_set_input_buttons(A_BUTTON | B_BUTTON, 0);
    
    gMolecano->version = version;
    molecano_init_gfx1();
    
    otherMole.sprite = sprite_create(gSpriteHandler, anim_mole_flip_stop, 0, 65, 80, 0x4000, 1, 0, 0);
    otherMole.jumpx = 0;
    otherMole.jumping = FALSE;

    gMolecano->otherMole = otherMole;
    
    mole.sprite = sprite_create(gSpriteHandler, anim_mole_stop, 0, 145, 80, 0x4000, 1, 0, 0);
    mole.jumpx = 0;
    mole.jumping = FALSE;

    cart.sprite = sprite_create(gSpriteHandler, anim_cart_stop, 0, 77, 112, 0x3000, 0, 0, 0);
    cart.leftWheel = sprite_create(gSpriteHandler, anim_wheel_spin, 0, 82, 114, 0x2999, 0, 0, 0);
    cart.rightWheel = sprite_create(gSpriteHandler, anim_wheel_spin, 0, 146, 114, 0x2999, 0, 0, 0);
    cart.moving = FALSE;

    gMolecano->cart = cart;
    gMolecano->mole = mole;

    gMolecano->stopJump = FALSE;

    gMolecano->jumpDuration = ticks_to_frames(24);
}

// Game Engine Update
void molecano_engine_update(void) {
    s16 yMod;
    u32 x;
    struct Mole *mole = &gMolecano->mole;
    struct Mole *otherMole = &gMolecano->otherMole;
    struct Cart *cart = &gMolecano->cart;
    s32 jumpDuration = gMolecano->jumpDuration;

    if (mole->jumping == TRUE) { 
        mole->jumpx += 1;
        
        sprite_set_y(gSpriteHandler, mole->sprite, 80 + ((mole->jumpx) * (mole->jumpx - jumpDuration)) / ((jumpDuration * jumpDuration) / 150));
       
        if (mole->jumpx > jumpDuration) {
            mole->jumping = FALSE;
            mole->jumpx = 0;
            sprite_set_y(gSpriteHandler, mole->sprite, 80);

            if (gMolecano->stopOnNext) {
                play_sound_w_pitch_volume(&s_hanabi_pon_seqData, 0xd0, 0);
                sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_jump, 0, 1, 0, 0);
                otherMole->jumping = TRUE;
                otherMole->jumpx = 0;
                gMolecano->stopOnNext = FALSE;
                gMolecano->stopJump = TRUE;
            }
        }
    }

    if (otherMole->jumping == TRUE) {
        otherMole->jumpx += 1;
        
        sprite_set_y(gSpriteHandler, otherMole->sprite, 80 + ((otherMole->jumpx) * (otherMole->jumpx - jumpDuration)) / ((jumpDuration * jumpDuration) / 150));
        
        if (otherMole->jumpx > jumpDuration) {
            sprite_set_anim(gSpriteHandler, otherMole->sprite, gMolecano->stopJump ? anim_mole_flip_stop : anim_mole_flip_land, 0, 1, 0, 0);
            play_sound(&s_f_boxing_just_hati_seqData);
            if (!gMolecano->stopJump) {
                mole->jumping = TRUE;
                cart->moving = TRUE;
                sprite_set_anim(gSpriteHandler, mole->sprite, anim_mole_jump, 0, 1, 0, 0);
                sprite_set_anim(gSpriteHandler, cart->sprite, anim_cart_left, 0, 1, 0, 0);
                sprite_set_anim(gSpriteHandler, cart->leftWheel, anim_wheel_spin, 0, 1, 0, 0);
                sprite_set_anim(gSpriteHandler, cart->rightWheel, anim_wheel_spin, 0, 1, 0, 0);
                sprite_set_anim_speed(gSpriteHandler, cart->leftWheel, INT_TO_FIXED(1.0));
                sprite_set_anim_speed(gSpriteHandler, cart->rightWheel, INT_TO_FIXED(1.0));
            } else {
                gMolecano->stopJump = FALSE;
                cart->moving = FALSE;
                sprite_set_anim(gSpriteHandler, cart->sprite, anim_cart_stop, 0, 1, 0, 0);

                sprite_set_anim_speed(gSpriteHandler, cart->leftWheel, INT_TO_FIXED(0.0));
                sprite_set_anim_speed(gSpriteHandler, cart->rightWheel, INT_TO_FIXED(0.0));
            }

            otherMole->jumping = FALSE;
            otherMole->jumpx = 0;
            sprite_set_y(gSpriteHandler, otherMole->sprite, 80);
        }
    }

    if (cart->moving) { 
        D_03004b10.BG_OFS[1].x += gMolecano->fast ? 6 : 2;
        D_03004b10.BG_OFS[2].x += gMolecano->fast ? 3 : 1;
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
        gMolecano->stopOnNext = FALSE;
    } else {
        data->stop = TRUE;
        gMolecano->stopOnNext = TRUE;
        play_sound_w_pitch_volume(&s_hanabi_pon_seqData, 0xd0, 0);
        return;
    }

    if (type == 2 || type == 4) {
        gMolecano->fast = TRUE;
    } else {
        gMolecano->fast = FALSE;
    }

    gMolecano->jumpDuration = ticks_to_frames(type % 2 == 0 ? 12 : 24);
    gMolecano->otherMole.jumpx = 0;
    gMolecano->otherMole.jumping = TRUE;
    sprite_set_anim(gSpriteHandler, gMolecano->otherMole.sprite, anim_mole_flip_jump, 0, 1, 0, 0);
}

void molecano_cue_update(struct Cue *cue, struct MolecanoCue *data, u32 runningTime, u32 duration) {

}
void molecano_cue_despawn(struct Cue *cue, struct MolecanoCue *data) {

}
void molecano_cue_hit(struct Cue *cue, struct MolecanoCue *data) {
    play_sound(&s_f_boxing_just_hati_seqData);
    if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 0, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 1, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->cart.sprite, anim_cart_right, 0, 1, 0, 0);
    }
    
}
void molecano_cue_barely(struct Cue *cue, struct MolecanoCue *data) {
    play_sound(&s_witch_donats_seqData);
     if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 1, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 1, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->cart.sprite, anim_cart_right, 0, 1, 0, 0);
    }
}
void molecano_cue_miss(struct Cue *cue, struct MolecanoCue *data) {
    play_sound(&s_witch_donats_seqData);
    if (data->stop) {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_stop, 0, 1, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, gMolecano->mole.sprite, anim_mole_land, 0, 1, 0, 0);
        sprite_set_anim(gSpriteHandler, gMolecano->cart.sprite, anim_cart_right, 0, 1, 0, 0);
    }
}