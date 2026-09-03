/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /Users/oliviabriggs/Desktop/assets/7segment.ttf -o /Users/oliviabriggs/Desktop/assets/ui_font_segment12.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_SEGMENT12
#define UI_FONT_SEGMENT12 1
#endif

#if UI_FONT_SEGMENT12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0022 "\"" */
    0xc, 0x63, 0x10,

    /* U+0027 "'" */
    0x70,

    /* U+0028 "(" */
    0xf8, 0x88, 0x8, 0x88, 0xe0,

    /* U+0029 ")" */
    0x71, 0x11, 0x1, 0x11, 0xf0,

    /* U+002C "," */
    0xf0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+0030 "0" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0xf8,

    /* U+0031 "1" */
    0xf7, 0x80,

    /* U+0032 "2" */
    0x78, 0x42, 0x17, 0x42, 0x10, 0x70,

    /* U+0033 "3" */
    0x71, 0x11, 0xf1, 0x11, 0xf0,

    /* U+0034 "4" */
    0xc, 0x63, 0x1f, 0x8, 0x42, 0x0,

    /* U+0035 "5" */
    0x68, 0x88, 0xf1, 0x11, 0xf0,

    /* U+0036 "6" */
    0xf4, 0x21, 0xf, 0xc6, 0x31, 0xf8,

    /* U+0037 "7" */
    0x71, 0x11, 0x1, 0x11, 0x10,

    /* U+0038 "8" */
    0xfc, 0x63, 0x1f, 0xc6, 0x31, 0xf8,

    /* U+0039 "9" */
    0x7c, 0x63, 0x1f, 0x8, 0x42, 0xe0,

    /* U+003A ":" */
    0x88,

    /* U+003D "=" */
    0xf0, 0x0, 0xe0,

    /* U+003F "?" */
    0x78, 0x42, 0x17, 0x42, 0x10, 0x0,

    /* U+0041 "A" */
    0xfc, 0x63, 0x1f, 0xc6, 0x31, 0x8,

    /* U+0042 "B" */
    0xfc, 0x63, 0x1f, 0xc6, 0x31, 0xf8,

    /* U+0043 "C" */
    0xf8, 0x88, 0x8, 0x88, 0xe0,

    /* U+0044 "D" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0xf8,

    /* U+0045 "E" */
    0xf8, 0x88, 0xf8, 0x88, 0xe0,

    /* U+0046 "F" */
    0xf8, 0x88, 0xf8, 0x88, 0x0,

    /* U+0047 "G" */
    0xf4, 0x21, 0x0, 0x46, 0x31, 0xf8,

    /* U+0048 "H" */
    0xc, 0x63, 0x1f, 0xc6, 0x31, 0x8,

    /* U+0049 "I" */
    0xf7, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x46, 0x31, 0x78,

    /* U+004B "K" */
    0xc, 0x63, 0x1f, 0x42, 0x10, 0xf0,

    /* U+004C "L" */
    0x12, 0x41, 0x24, 0xe0,

    /* U+004D "M" */
    0x70, 0x0, 0x7, 0xc6, 0x31, 0x8,

    /* U+004E "N" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0x8,

    /* U+004F "O" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0xf8,

    /* U+0050 "P" */
    0xfc, 0x63, 0x1f, 0x42, 0x10, 0x0,

    /* U+0051 "Q" */
    0x7c, 0x63, 0x1f, 0x0, 0x0, 0xf0,

    /* U+0052 "R" */
    0xf8, 0x88, 0x8, 0x88, 0x0,

    /* U+0053 "S" */
    0x68, 0x88, 0xf1, 0x11, 0xf0,

    /* U+0054 "T" */
    0x71, 0x11, 0x1, 0x11, 0x10,

    /* U+0055 "U" */
    0xc, 0x63, 0x10, 0x46, 0x31, 0xf8,

    /* U+0056 "V" */
    0xc, 0x63, 0x10, 0x0, 0x0, 0xf0,

    /* U+0057 "W" */
    0xc, 0x63, 0x1f, 0xc6, 0x31, 0xf8,

    /* U+0058 "X" */
    0x70, 0x0, 0xf0, 0x0, 0xe0,

    /* U+0059 "Y" */
    0xc, 0x63, 0x1f, 0x8, 0x42, 0xe0,

    /* U+005A "Z" */
    0x78, 0x42, 0x17, 0x42, 0x10, 0x70,

    /* U+005B "[" */
    0xf8, 0x88, 0x8, 0x88, 0xe0,

    /* U+005D "]" */
    0x71, 0x11, 0x1, 0x11, 0xf0,

    /* U+005F "_" */
    0xe0,

    /* U+0060 "`" */
    0x70,

    /* U+0061 "a" */
    0x78, 0x42, 0x17, 0xc6, 0x31, 0x78,

    /* U+0062 "b" */
    0x4, 0x21, 0xf, 0xc6, 0x31, 0xf8,

    /* U+0063 "c" */
    0x78, 0x88, 0x60,

    /* U+0064 "d" */
    0x8, 0x42, 0x17, 0xc6, 0x31, 0x78,

    /* U+0065 "e" */
    0xfc, 0x63, 0x1f, 0x42, 0x10, 0xf0,

    /* U+0066 "f" */
    0xf8, 0x88, 0xf8, 0x88, 0x0,

    /* U+0067 "g" */
    0x7c, 0x63, 0x1f, 0x8, 0x42, 0xe0,

    /* U+0068 "h" */
    0x4, 0x21, 0xf, 0xc6, 0x31, 0x8,

    /* U+0069 "i" */
    0xf0,

    /* U+006A "j" */
    0x11, 0x11, 0x1, 0x11, 0xf0,

    /* U+006B "k" */
    0xf4, 0x21, 0xf, 0xc6, 0x31, 0x8,

    /* U+006C "l" */
    0x12, 0x41, 0x24, 0xe0,

    /* U+006D "m" */
    0x70, 0x0, 0x7, 0xc6, 0x31, 0x8,

    /* U+006E "n" */
    0x7c, 0x63, 0x10, 0x80,

    /* U+006F "o" */
    0x7c, 0x63, 0x17, 0x80,

    /* U+0070 "p" */
    0xfc, 0x63, 0x1f, 0x42, 0x10, 0x0,

    /* U+0071 "q" */
    0x7c, 0x63, 0x1f, 0x8, 0x42, 0x0,

    /* U+0072 "r" */
    0x78, 0x88, 0x0,

    /* U+0073 "s" */
    0x8, 0x88, 0xf1, 0x11, 0x10,

    /* U+0074 "t" */
    0x8, 0x88, 0xf8, 0x88, 0xe0,

    /* U+0075 "u" */
    0x8c, 0x62, 0xf0,

    /* U+0076 "v" */
    0xc, 0x63, 0x10, 0x0, 0x0, 0xf0,

    /* U+0077 "w" */
    0xc, 0x63, 0x1f, 0xc6, 0x31, 0xf8,

    /* U+0078 "x" */
    0x70, 0x0, 0xf0, 0x0, 0xe0,

    /* U+0079 "y" */
    0xc, 0x63, 0x1f, 0x8, 0x42, 0xe0,

    /* U+007A "z" */
    0x78, 0x42, 0x17, 0x42, 0x10, 0x70,

    /* U+007C "|" */
    0xf7, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 90, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 90, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 5, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 90, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 90, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 17, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 90, .box_w = 1, .box_h = 9, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 34, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 72, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 90, .box_w = 1, .box_h = 9, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 90, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 90, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 90, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 236, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 90, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 90, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 90, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 0, 1, 0, 0, 0, 0, 2,
    3, 4, 0, 0, 5, 6, 7, 0,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 0, 0, 19, 0, 20,
    0, 21, 22, 23, 24, 25, 26, 27,
    28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43,
    44, 45, 46, 47, 0, 48, 0, 49,
    50, 51, 52, 53, 54, 55, 56, 57,
    58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 0, 77
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 93, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 93, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    8, 8
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    23
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
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
const lv_font_t ui_font_segment12 = {
#else
lv_font_t ui_font_segment12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_SEGMENT12*/

