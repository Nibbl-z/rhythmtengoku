asm(".section .text \n\
\n\
.syntax unified \n\
\n\
.include \"include/gba.inc\" \n\
\n\
.balign 4, 0 \n\
glabel func_0800046C \n\
/* 0800046c */ PUSH {LR} \n\
/* 0800046e */ LDR R1, =D_03000000 \n\
/* 08000470 */ MOVS R2, 0x0 @ Set R2 to 0x0 \n\
/* 08000472 */ STR R2, [R1] \n\
/* 08000474 */ LDR R1, =D_03000004 \n\
/* 08000476 */ STR R0, [R1] \n\
/* 08000478 */ LDR R0, =D_030046a4 \n\
/* 0800047a */ STR R2, [R0] \n\
/* 0800047c */ BL func_08000598 \n\
/* 08000480 */ POP {R0} \n\
/* 08000482 */ BX R0 \n\
 \n\
.ltorg \n\
");
