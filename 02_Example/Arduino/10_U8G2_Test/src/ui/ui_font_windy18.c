/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font /Users/oliviabriggs/Desktop/assets/subset-x12y12pxMaruMinya.ttf -o /Users/oliviabriggs/Desktop/assets/ui_font_windy18.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_WINDY18
#define UI_FONT_WINDY18 1
#endif

#if UI_FONT_WINDY18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf, 0xc0,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x6c, 0x6c, 0x6c, 0xff, 0x6c, 0x6c, 0x6c, 0x6c,
    0x6c, 0xff, 0x6c, 0x6c, 0x6c,

    /* U+0024 "$" */
    0x18, 0x3f, 0x58, 0xd8, 0xd8, 0xd8, 0x3c, 0x1b,
    0x1b, 0x1b, 0xfc, 0x18, 0x18,

    /* U+0025 "%" */
    0x23, 0xdb, 0xdb, 0xdc, 0x44, 0x24, 0x18, 0x24,
    0x3b, 0x3b, 0xdb, 0xcc, 0xc4,

    /* U+0026 "&" */
    0x38, 0xc4, 0xc4, 0xc4, 0xd8, 0x60, 0x23, 0xdb,
    0xc4, 0xc4, 0xc4, 0x4c, 0x3b,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0xc, 0xc2, 0x8, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x8, 0x20, 0x81, 0x3,

    /* U+0029 ")" */
    0xc0, 0x82, 0x8, 0x1c, 0x30, 0xc3, 0xc, 0x30,
    0xcc, 0x20, 0x84, 0x30,

    /* U+002A "*" */
    0x18, 0xdb, 0x5c, 0x3c, 0xdb, 0x18, 0x18,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x2b, 0x0,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x3, 0x3, 0x3, 0x4, 0x4, 0x4, 0x18, 0x18,
    0x18, 0x20, 0x20, 0x20, 0xc0, 0xc0, 0xc0,

    /* U+0030 "0" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x44, 0x3c,

    /* U+0031 "1" */
    0x1f, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x80,

    /* U+0032 "2" */
    0x3c, 0xc3, 0xc3, 0xc3, 0x3, 0x4, 0x4, 0x18,
    0x20, 0x20, 0xc0, 0xc0, 0xff,

    /* U+0033 "3" */
    0x3c, 0xc3, 0x3, 0x3, 0x3, 0x4, 0x1c, 0x3,
    0x3, 0x3, 0xc3, 0x44, 0x3c,

    /* U+0034 "4" */
    0x7, 0x1b, 0x1b, 0x1b, 0x23, 0x23, 0x23, 0xc3,
    0xc3, 0xff, 0x3, 0x3, 0x3,

    /* U+0035 "5" */
    0xff, 0xc0, 0xc0, 0xc0, 0xfc, 0xc3, 0xc3, 0x3,
    0x3, 0x3, 0xc3, 0x44, 0x3c,

    /* U+0036 "6" */
    0x3c, 0xc3, 0xc0, 0xc0, 0xfc, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x44, 0x3c,

    /* U+0037 "7" */
    0xfc, 0x3, 0x3, 0x3, 0x4, 0x4, 0x4, 0x18,
    0x18, 0x18, 0x60, 0x60, 0x60,

    /* U+0038 "8" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0x44, 0x3c, 0xc3,
    0xc3, 0xc3, 0xc3, 0x44, 0x3c,

    /* U+0039 "9" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x3f,
    0x3, 0x3, 0x4, 0x8, 0x38,

    /* U+003A ":" */
    0xc0, 0x0, 0x30,

    /* U+003B ";" */
    0x20, 0x0, 0x0, 0x5, 0x60,

    /* U+003C "<" */
    0x4, 0x21, 0x88, 0xc3, 0xc, 0x10, 0x20, 0x60,
    0x81,

    /* U+003D "=" */
    0xff, 0x0, 0x0, 0x0, 0x0, 0xff,

    /* U+003E ">" */
    0xc1, 0x2, 0x6, 0x4, 0x10, 0x42, 0x18, 0x84,
    0x30,

    /* U+003F "?" */
    0xfc, 0x3, 0x3, 0x3, 0x4, 0x18, 0x18, 0x18,
    0x0, 0x0, 0x18, 0x18, 0x18,

    /* U+0040 "@" */
    0x3c, 0x44, 0xc3, 0xdf, 0xc3, 0xe3, 0xe3, 0xe3,
    0xdc, 0xc3, 0x44, 0x3c,

    /* U+0041 "A" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0042 "B" */
    0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc4, 0xfc, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc4, 0xfc,

    /* U+0043 "C" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc3, 0xc3, 0xc3, 0x44, 0x3c,

    /* U+0044 "D" */
    0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc4, 0xfc,

    /* U+0045 "E" */
    0x3f, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xc0,
    0xc0, 0xc0, 0xc0, 0x40, 0x3f,

    /* U+0046 "F" */
    0x3f, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x3f, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xdf, 0xc3,
    0xc3, 0xc3, 0xc3, 0x43, 0x3f,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0xff,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x3c,

    /* U+004B "K" */
    0xc3, 0xc3, 0xc3, 0xc4, 0xd8, 0xe0, 0xe0, 0xd8,
    0xc8, 0xc4, 0xc3, 0xc3, 0xc3,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0x3f,

    /* U+004D "M" */
    0xc3, 0xc3, 0xc3, 0xe7, 0xdb, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+004E "N" */
    0xc3, 0xc3, 0xc3, 0xe3, 0xdb, 0xcb, 0xc7, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+004F "O" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x44, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfc,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfb,
    0xc4, 0xc4, 0xc4, 0x4c, 0x3b,

    /* U+0052 "R" */
    0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc4, 0xcc, 0xf0,
    0xd0, 0xcc, 0xc3, 0xc3, 0xc3,

    /* U+0053 "S" */
    0x3f, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x3c, 0x3,
    0x3, 0x3, 0x3, 0x4, 0xfc,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x3c,

    /* U+0056 "V" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x24, 0x24,
    0x24, 0x24, 0x18, 0x18, 0x18,

    /* U+0057 "W" */
    0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb, 0x24, 0x24, 0x24, 0x24,

    /* U+0058 "X" */
    0xc3, 0xc3, 0xc3, 0x24, 0x24, 0x24, 0x18, 0x24,
    0x24, 0x24, 0xc3, 0xc3, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0xc3, 0xc3, 0xc3, 0x24, 0x24, 0x24, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0x3, 0x3, 0x4, 0x18, 0x20, 0x20, 0x20,
    0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x1f,

    /* U+005C "\\" */
    0xc0, 0xc0, 0xc0, 0x20, 0x20, 0x20, 0x18, 0x18,
    0x18, 0x4, 0x4, 0x4, 0x3, 0x3, 0x3,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x7f,

    /* U+005E "^" */
    0x18, 0x24, 0x44, 0xc3,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0xc8, 0x80,

    /* U+0061 "a" */
    0x3c, 0x3, 0x3, 0x3f, 0xc3, 0xc3, 0xc3, 0xc3,
    0x43, 0x3f,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xfc, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc4, 0xfc,

    /* U+0063 "c" */
    0x3c, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3,
    0x44, 0x3c,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3f, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x43, 0x3f,

    /* U+0065 "e" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xfc, 0xc0, 0xc0, 0xc3,
    0x44, 0x3c,

    /* U+0066 "f" */
    0x1f, 0x60, 0x60, 0x60, 0xff, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60,

    /* U+0067 "g" */
    0x3f, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x43,
    0x3f, 0x3, 0x4, 0x3c,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xe3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0x38, 0x0, 0x0, 0xe0, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0xff,

    /* U+006A "j" */
    0x7, 0x0, 0x0, 0x3c, 0x3, 0x3, 0x3, 0x3,
    0x3, 0x3, 0x3, 0x3, 0xc3, 0x44, 0x3c,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc7, 0xd8, 0xe0, 0xe0, 0xd8,
    0xc8, 0xc4, 0xc3, 0xc3, 0xc3,

    /* U+006C "l" */
    0xe0, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0xff,

    /* U+006D "m" */
    0xe4, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb, 0xdb,

    /* U+006E "n" */
    0xdc, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+006F "o" */
    0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c,

    /* U+0070 "p" */
    0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc4,
    0xfc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3f, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x43,
    0x3f, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0,

    /* U+0073 "s" */
    0x3f, 0xc0, 0xc0, 0xc0, 0x3c, 0x3, 0x3, 0x3,
    0x4, 0xfc,

    /* U+0074 "t" */
    0x60, 0x60, 0x60, 0xff, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x1f,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc7, 0x3b,

    /* U+0076 "v" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x24, 0x24,
    0x28, 0x18,

    /* U+0077 "w" */
    0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0x24,
    0x24, 0x24,

    /* U+0078 "x" */
    0xc3, 0xc3, 0xc3, 0x24, 0x18, 0x28, 0x24, 0xc3,
    0xc3, 0xc3,

    /* U+0079 "y" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x3f, 0x3,
    0x3, 0x3, 0x4, 0xfc,

    /* U+007B "{" */
    0xe, 0x60, 0x81, 0x2, 0x4, 0x8, 0x60, 0x20,
    0x40, 0x81, 0x2, 0x4, 0x4, 0x7,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe0, 0x61, 0x86, 0x18, 0x61, 0x81, 0x18, 0x61,
    0x86, 0x18, 0x62, 0x38,

    /* U+007E "~" */
    0x3b, 0x4c, 0xc4
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 144, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 144, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 5, .adv_w = 144, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 8, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 21, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 34, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 47, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 60, .adv_w = 144, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 11},
    {.bitmap_index = 61, .adv_w = 144, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 144, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 92, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 99, .adv_w = 144, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 144, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 102, .adv_w = 144, .box_w = 2, .box_h = 1, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 103, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 131, .adv_w = 144, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 140, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 153, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 166, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 179, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 192, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 205, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 218, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 231, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 244, .adv_w = 144, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 247, .adv_w = 144, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 144, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 261, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 267, .adv_w = 144, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 276, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 289, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 301, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 314, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 327, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 340, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 353, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 366, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 379, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 392, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 405, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 418, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 431, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 444, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 457, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 470, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 483, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 496, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 509, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 522, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 535, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 548, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 561, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 574, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 587, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 600, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 613, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 626, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 639, .adv_w = 144, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 144, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 144, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 678, .adv_w = 144, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 144, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 15},
    {.bitmap_index = 681, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 691, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 704, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 714, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 727, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 737, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 750, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 775, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 788, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 816, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 829, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 839, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 849, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 859, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 893, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 903, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 916, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 926, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 936, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 946, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 956, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 968, .adv_w = 144, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 982, .adv_w = 144, .box_w = 2, .box_h = 18, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 144, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 999, .adv_w = 144, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 8}
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
const lv_font_t ui_font_windy18 = {
#else
lv_font_t ui_font_windy18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_WINDY18*/

