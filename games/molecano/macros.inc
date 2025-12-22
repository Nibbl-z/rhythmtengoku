@ Load Game: Molecano

.macro load_molecano
    .set CUE_SLOW, 0x00
    .set CUE_FAST, 0x01
    .set CUE_STOP, 0x02
    load_game molecano_engine, 0
.endm

@ Run Game Event
.macro molecano_event event, args
    game_event molecano_engine, \event, \args
.endm

.macro molecano_left_mole_fast
    molecano_event 0, 0
.endm

.macro molecano_left_mole_slow
    molecano_event 1, 0
.endm