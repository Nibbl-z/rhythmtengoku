#include "global.h"
#include "graphics.h"

// [D_088e9f18] <description>
Palette clappy_trio_obj_pal[] = {
    /* PALETTE 00 */ {
        /* 00 */ TO_RGB555(0x18B0F8),
        /* 01 */ TO_RGB555(0x000000),
        /* 02 */ TO_RGB555(0x980008),
        /* 03 */ TO_RGB555(0xF80800),
        /* 04 */ TO_RGB555(0x505800),
        /* 05 */ TO_RGB555(0xF0F818),
        /* 06 */ TO_RGB555(0x18B010),
        /* 07 */ TO_RGB555(0x28F818),
        /* 08 */ TO_RGB555(0x60B8C8),
        /* 09 */ TO_RGB555(0x78E0F8),
        /* 10 */ TO_RGB555(0x0010B8),
        /* 11 */ TO_RGB555(0x2860F8),
        /* 12 */ TO_RGB555(0xC060B0),
        /* 13 */ TO_RGB555(0xF878E0),
        /* 14 */ TO_RGB555(0xA8B0A8),
        /* 15 */ TO_RGB555(0xF8F8F8)
    },
    /* PALETTE 01 */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x000000),
        /* 02 */ TO_RGB555(0x000000),
        /* 03 */ TO_RGB555(0x000000),
        /* 04 */ TO_RGB555(0x000000),
        /* 05 */ TO_RGB555(0x000000),
        /* 06 */ TO_RGB555(0x000000),
        /* 07 */ TO_RGB555(0x000000),
        /* 08 */ TO_RGB555(0x000000),
        /* 09 */ TO_RGB555(0x000000),
        /* 10 */ TO_RGB555(0x000000),
        /* 11 */ TO_RGB555(0x000000),
        /* 12 */ TO_RGB555(0x000000),
        /* 13 */ TO_RGB555(0x000000),
        /* 14 */ TO_RGB555(0x000000),
        /* 15 */ TO_RGB555(0x000000)
    },
    /* PALETTE 02 */ {
        /* 00 */ TO_RGB555(0x606860),
        /* 01 */ TO_RGB555(0x000000),
        /* 02 */ TO_RGB555(0x980008),
        /* 03 */ TO_RGB555(0xF80800),
        /* 04 */ TO_RGB555(0x98A008),
        /* 05 */ TO_RGB555(0xF8F818),
        /* 06 */ TO_RGB555(0x18B010),
        /* 07 */ TO_RGB555(0x28F818),
        /* 08 */ TO_RGB555(0x78E0F8),
        /* 09 */ TO_RGB555(0x0820F8),
        /* 10 */ TO_RGB555(0xF8C050),
        /* 11 */ TO_RGB555(0xF8E088),
        /* 12 */ TO_RGB555(0x80F890),
        /* 13 */ TO_RGB555(0x606860),
        /* 14 */ TO_RGB555(0xA8B0A8),
        /* 15 */ TO_RGB555(0xF8F8F8)
    }
};

// [D_088e9f78] <description>
Palette clappy_trio_bg_pal_0 = {
    /* 00 */ TO_RGB555(0x000000),
    /* 01 */ TO_RGB555(0xA8B0F0),
    /* 02 */ TO_RGB555(0xF8F8B0),
    /* 03 */ TO_RGB555(0xF0F080),
    /* 04 */ TO_RGB555(0xE8E050),
    /* 05 */ TO_RGB555(0xE0D818),
    /* 06 */ TO_RGB555(0x10C8E8),
    /* 07 */ TO_RGB555(0x28E0F8),
    /* 08 */ TO_RGB555(0x60E8F8),
    /* 09 */ TO_RGB555(0x88F0F8),
    /* 10 */ TO_RGB555(0xB0F8F8),
    /* 11 */ TO_RGB555(0xD8F8F8),
    /* 12 */ TO_RGB555(0x989010),
    /* 13 */ TO_RGB555(0x383838),
    /* 14 */ TO_RGB555(0xF8F8F8),
    /* 15 */ TO_RGB555(0x000000)
};
Palette clappy_trio_bg_pal_1 = {
    /* 00 */ TO_RGB555(0xB8B8B8),
    /* 01 */ TO_RGB555(0x000000),
    /* 02 */ TO_RGB555(0x000000),
    /* 03 */ TO_RGB555(0x404040),
    /* 04 */ TO_RGB555(0x181818),
    /* 05 */ TO_RGB555(0xA0A0A0),
    /* 06 */ TO_RGB555(0x000000),
    /* 07 */ TO_RGB555(0x000000),
    /* 08 */ TO_RGB555(0x000000),
    /* 09 */ TO_RGB555(0x000000),
    /* 10 */ TO_RGB555(0x000000),
    /* 11 */ TO_RGB555(0x000000),
    /* 12 */ TO_RGB555(0x000000),
    /* 13 */ TO_RGB555(0x000000),
    /* 14 */ TO_RGB555(0xA8B0A8),
    /* 15 */ TO_RGB555(0xF8F8F8)
};
Palette clappy_trio_bg_pal_2 = {
    /* 00 */ TO_RGB555(0x000000),
    /* 01 */ TO_RGB555(0x000000),
    /* 02 */ TO_RGB555(0x000000),
    /* 03 */ TO_RGB555(0x000000),
    /* 04 */ TO_RGB555(0x000000),
    /* 05 */ TO_RGB555(0x000000),
    /* 06 */ TO_RGB555(0x000000),
    /* 07 */ TO_RGB555(0x000000),
    /* 08 */ TO_RGB555(0x000000),
    /* 09 */ TO_RGB555(0x000000),
    /* 10 */ TO_RGB555(0x000000),
    /* 11 */ TO_RGB555(0x000000),
    /* 12 */ TO_RGB555(0x000000),
    /* 13 */ TO_RGB555(0x000000),
    /* 14 */ TO_RGB555(0x000000),
    /* 15 */ TO_RGB555(0x000000)
};
Palette clappy_trio_bg_pal_3 = {
    /* 00 */ TO_RGB555(0x606860),
    /* 01 */ TO_RGB555(0x000000),
    /* 02 */ TO_RGB555(0x101010),
    /* 03 */ TO_RGB555(0x404040),
    /* 04 */ TO_RGB555(0x000000),
    /* 05 */ TO_RGB555(0xE8E8E8),
    /* 06 */ TO_RGB555(0x000000),
    /* 07 */ TO_RGB555(0x000000),
    /* 08 */ TO_RGB555(0x000000),
    /* 09 */ TO_RGB555(0x000000),
    /* 10 */ TO_RGB555(0xC8C8C8),
    /* 11 */ TO_RGB555(0xF8F8F8),
    /* 12 */ TO_RGB555(0x000000),
    /* 13 */ TO_RGB555(0x606860),
    /* 14 */ TO_RGB555(0xA8B0A8),
    /* 15 */ TO_RGB555(0xF8F8F8)
};
Palette clappy_trio_bg_pal_4 = {
    /* 00 */ TO_RGB555(0x000000),
    /* 01 */ TO_RGB555(0x000000),
    /* 02 */ TO_RGB555(0x000000),
    /* 03 */ TO_RGB555(0x000000),
    /* 04 */ TO_RGB555(0xF8F8F8),
    /* 05 */ TO_RGB555(0xA8A8A8),
    /* 06 */ TO_RGB555(0x808080),
    /* 07 */ TO_RGB555(0x909090),
    /* 08 */ TO_RGB555(0xA8A8A8),
    /* 09 */ TO_RGB555(0xB8B8B8),
    /* 10 */ TO_RGB555(0xC8C8C8),
    /* 11 */ TO_RGB555(0xD8D8D8),
    /* 12 */ TO_RGB555(0x000000),
    /* 13 */ TO_RGB555(0x000000),
    /* 14 */ TO_RGB555(0xE8E8E8),
    /* 15 */ TO_RGB555(0x000000)
};

