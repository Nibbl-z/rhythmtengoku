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

    
    otherMole.sprite = sprite_create(gSpriteHandler, anim_mole_crawl, 0, 50, 100, 0x4000, 1, 0, 0);

    gMolecano->otherMole = otherMole;
    
    
    mole.sprite = sprite_create(gSpriteHandler, anim_mole_crawl, 0, 100, 100, 0x4000, 1, 0, 0);

    gMolecano->mole = mole;
}

// Game Engine Update
void molecano_engine_update(void) {}

// Game Engine Stop
void molecano_engine_stop(void) {}

// Input Event
void molecano_input_event(u32 pressed, u32 released) {}