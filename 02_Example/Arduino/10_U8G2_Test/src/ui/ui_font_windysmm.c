/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /Users/oliviabriggs/Desktop/assets/subset-x12y12pxMaruMinya.ttf -o /Users/oliviabriggs/Desktop/assets/ui_font_windysmm.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_WINDYSMM
#define UI_FONT_WINDYSMM 1
#endif

#if UI_FONT_WINDYSMM

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xf9, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x52, 0xbe, 0xa5, 0x2b, 0xea, 0x50,

    /* U+0024 "$" */
    0x23, 0xe9, 0x47, 0x14, 0xbe, 0x20,

    /* U+0025 "%" */
    0x4d, 0x6c, 0xa2, 0x29, 0xb5, 0x90,

    /* U+0026 "&" */
    0x64, 0xa5, 0x44, 0xd6, 0x52, 0x68,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x29, 0x49, 0x24, 0x48, 0x80,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x4a, 0x0,

    /* U+002A "*" */
    0x25, 0x5d, 0x52, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0x60,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x44, 0x22, 0x11, 0x8, 0x84, 0x0,

    /* U+0030 "0" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+0031 "1" */
    0x3c, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x74, 0x62, 0x11, 0x11, 0x10, 0xf8,

    /* U+0033 "3" */
    0x74, 0x42, 0x13, 0x4, 0x31, 0x70,

    /* U+0034 "4" */
    0x19, 0x4a, 0x94, 0xc7, 0xe1, 0x8,

    /* U+0035 "5" */
    0xfc, 0x21, 0xe8, 0x84, 0x31, 0x70,

    /* U+0036 "6" */
    0x74, 0x61, 0xe8, 0xc6, 0x31, 0x70,

    /* U+0037 "7" */
    0xf0, 0x42, 0x21, 0x10, 0x88, 0x40,

    /* U+0038 "8" */
    0x74, 0x63, 0x17, 0x46, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0x63, 0x18, 0xbc, 0x22, 0x60,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x40, 0x6,

    /* U+003C "<" */
    0x12, 0x48, 0x84, 0x21,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x84, 0x21, 0x12, 0x48,

    /* U+003F "?" */
    0xf0, 0x42, 0x22, 0x10, 0x4, 0x20,

    /* U+0040 "@" */
    0x74, 0x6f, 0x9c, 0xda, 0x2e,

    /* U+0041 "A" */
    0x74, 0x63, 0x18, 0xfe, 0x31, 0x88,

    /* U+0042 "B" */
    0xf4, 0x63, 0x1f, 0x46, 0x31, 0xf0,

    /* U+0043 "C" */
    0x74, 0x63, 0x8, 0x42, 0x31, 0x70,

    /* U+0044 "D" */
    0xf4, 0x63, 0x18, 0xc6, 0x31, 0xf0,

    /* U+0045 "E" */
    0x7c, 0x21, 0xf, 0xc2, 0x10, 0x78,

    /* U+0046 "F" */
    0x7c, 0x21, 0xf, 0xc2, 0x10, 0x80,

    /* U+0047 "G" */
    0x7c, 0x21, 0xb, 0xc6, 0x31, 0x78,

    /* U+0048 "H" */
    0x8c, 0x63, 0x1f, 0xc6, 0x31, 0x88,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0xc6, 0x31, 0x70,

    /* U+004B "K" */
    0x8c, 0x65, 0x4c, 0x52, 0x51, 0x88,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0x78,

    /* U+004D "M" */
    0x8c, 0x77, 0x58, 0xc6, 0x31, 0x88,

    /* U+004E "N" */
    0x8c, 0x73, 0x59, 0xc6, 0x31, 0x88,

    /* U+004F "O" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+0050 "P" */
    0xf4, 0x63, 0x18, 0xfa, 0x10, 0x80,

    /* U+0051 "Q" */
    0x74, 0x63, 0x18, 0xf6, 0x52, 0x68,

    /* U+0052 "R" */
    0xf4, 0x63, 0x19, 0x72, 0x51, 0x88,

    /* U+0053 "S" */
    0x7c, 0x21, 0x7, 0x4, 0x21, 0xf0,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x20,

    /* U+0055 "U" */
    0x8c, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+0056 "V" */
    0x8c, 0x63, 0x15, 0x29, 0x44, 0x20,

    /* U+0057 "W" */
    0x8c, 0x6b, 0x5a, 0xd5, 0x4a, 0x50,

    /* U+0058 "X" */
    0x8c, 0x54, 0xa2, 0x29, 0x51, 0x88,

    /* U+0059 "Y" */
    0x8c, 0x62, 0xa5, 0x10, 0x84, 0x20,

    /* U+005A "Z" */
    0xf8, 0x44, 0x44, 0x22, 0x10, 0xf8,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x93, 0x80,

    /* U+005C "\\" */
    0x84, 0x10, 0x82, 0x10, 0x42, 0x8, 0x40,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x27, 0x80,

    /* U+005E "^" */
    0x22, 0xa2,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x70, 0x5f, 0x18, 0xc5, 0xe0,

    /* U+0062 "b" */
    0x84, 0x3d, 0x18, 0xc6, 0x31, 0xf0,

    /* U+0063 "c" */
    0x74, 0x61, 0x8, 0x45, 0xc0,

    /* U+0064 "d" */
    0x8, 0x5f, 0x18, 0xc6, 0x31, 0x78,

    /* U+0065 "e" */
    0x74, 0x63, 0xe8, 0x45, 0xc0,

    /* U+0066 "f" */
    0x3a, 0x11, 0xf4, 0x21, 0x8, 0x40,

    /* U+0067 "g" */
    0x7c, 0x63, 0x18, 0xbc, 0x2e,

    /* U+0068 "h" */
    0x84, 0x2d, 0x98, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0x60, 0x30, 0x42, 0x10, 0x84, 0xf8,

    /* U+006A "j" */
    0x18, 0x1c, 0x10, 0x84, 0x21, 0x8b, 0x80,

    /* U+006B "k" */
    0x84, 0x27, 0x4c, 0x52, 0x51, 0x88,

    /* U+006C "l" */
    0xc1, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+006D "m" */
    0xd5, 0x6b, 0x5a, 0xd6, 0xa0,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x74, 0x63, 0x18, 0xc5, 0xc0,

    /* U+0070 "p" */
    0xf4, 0x63, 0x18, 0xfa, 0x10,

    /* U+0071 "q" */
    0x7c, 0x63, 0x18, 0xbc, 0x21,

    /* U+0072 "r" */
    0xbe, 0x21, 0x8, 0x42, 0x0,

    /* U+0073 "s" */
    0x7c, 0x20, 0xe0, 0x87, 0xc0,

    /* U+0074 "t" */
    0x42, 0x3e, 0x84, 0x21, 0x8, 0x38,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x8c, 0x63, 0x15, 0x28, 0x80,

    /* U+0077 "w" */
    0x8c, 0x6b, 0x5a, 0xa9, 0x40,

    /* U+0078 "x" */
    0x8c, 0x54, 0x45, 0x46, 0x20,

    /* U+0079 "y" */
    0x8c, 0x63, 0x17, 0x84, 0x3e,

    /* U+007B "{" */
    0x34, 0x44, 0x48, 0x44, 0x44, 0x30,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0xc2, 0x22, 0x21, 0x22, 0x22, 0xc0,

    /* U+007E "~" */
    0x6c, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 96, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 11, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 17, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 23, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 29, .adv_w = 96, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 30, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 44, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 48, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 96, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 50, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 64, .adv_w = 96, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 74, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 80, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 86, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 92, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 98, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 104, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 110, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 116, .adv_w = 96, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 117, .adv_w = 96, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 123, .adv_w = 96, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 126, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 130, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 136, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 141, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 147, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 153, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 159, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 165, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 171, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 177, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 183, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 189, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 195, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 201, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 207, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 213, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 219, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 225, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 231, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 237, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 243, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 249, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 255, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 261, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 267, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 273, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 279, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 285, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 291, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 297, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 96, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 316, .adv_w = 96, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 318, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 323, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 329, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 334, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 340, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 345, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 351, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 362, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 368, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 381, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 387, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 392, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 397, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 402, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 417, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 422, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 428, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 433, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 438, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 443, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 448, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 96, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 96, .box_w = 1, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 96, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 96, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 90, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 123, .range_length = 4, .glyph_id_start = 91,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_windysmm = {
#else
lv_font_t ui_font_windysmm = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_WINDYSMM*/

