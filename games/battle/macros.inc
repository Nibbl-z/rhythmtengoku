.macro load_battle_labels
    @ Game Events
    .set SET_WIN_SCRIPT,    0x00
    .set SET_DEATH_SCRIPT,  0x01
    .set EXPLODE_SOUL,      0x02
.endm

@ Load Game: Battle
.macro load_battle
    load_battle_labels
    load_game battle_engine, 0
.endm

/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro battle_event event, args
    game_event battle_engine, \event, \args
.endm

@ [Event 0x00] Set Win Script
.macro battle_set_win_script script
    battle_event SET_WIN_SCRIPT, \script
.endm

@ [Event 0x01] Set Death Script
.macro battle_set_death_script script
    battle_event SET_DEATH_SCRIPT, \script
.endm

@ [Event 0x01] Explode Soul
.macro battle_explode_soul
    battle_event EXPLODE_SOUL
.endm