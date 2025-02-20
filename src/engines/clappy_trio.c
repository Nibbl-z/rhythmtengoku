#include "engines/clappy_trio.h"
#include "src/text_printer.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gClappyTrio ((struct ClappyTrioEngineData *)gCurrentEngineData)


/* THE CLAPPY TRIO */


#include "asm/engines/clappy_trio/asm_08030384.s"

#include "asm/engines/clappy_trio/asm_080303a4.s"

#include "asm/engines/clappy_trio/asm_0803050c.s"

#include "asm/engines/clappy_trio/asm_0803051c.s"

#include "asm/engines/clappy_trio/asm_0803055c.s"

#include "asm/engines/clappy_trio/asm_08030588.s"

#include "asm/engines/clappy_trio/asm_0803068c.s"

#include "asm/engines/clappy_trio/asm_0803074c.s"

#include "asm/engines/clappy_trio/asm_0803080c.s"

void func_0803088c(u32 volume) {
    gClappyTrio->lionClapVolume = volume;
}

void func_08030898(u8 enable) {
    gClappyTrio->grayscale = enable;
}

#include "asm/engines/clappy_trio/asm_080308a4.s"

#include "asm/engines/clappy_trio/asm_080308b8.s"

#include "asm/engines/clappy_trio/asm_080308bc.s"

#include "asm/engines/clappy_trio/asm_080308d4.s"

#include "asm/engines/clappy_trio/asm_080308f0.s"

#include "asm/engines/clappy_trio/asm_080308f4.s"

#include "asm/engines/clappy_trio/asm_080309a8.s"

#include "asm/engines/clappy_trio/asm_080309f4.s"

#include "asm/engines/clappy_trio/asm_08030a10.s"

#include "asm/engines/clappy_trio/asm_08030a60.s"

void clappy_trio_common_display_text(char *text) {
    text_printer_set_string(gClappyTrio->textPrinter, text);
}

void func_08030bf0(u32 enabled) {
    sprite_set_visible(gSpriteHandler, gClappyTrio->unk, enabled);
}

#include "asm/engines/clappy_trio/asm_08030c14.s"
