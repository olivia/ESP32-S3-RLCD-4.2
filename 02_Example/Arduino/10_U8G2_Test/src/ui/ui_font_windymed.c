/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font /Users/oliviabriggs/SquareLine/assets/subset-x12y12pxMaruMinya.ttf -o /Users/oliviabriggs/SquareLine/assets/ui_font_windymed.c --format lvgl --symbols 東南西北 --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_WINDYMED
#define UI_FONT_WINDYMED 1
#endif

#if UI_FONT_WINDYMED

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+5317 "北" */
    0x3, 0x30, 0x0, 0xcc, 0x0, 0x33, 0xf, 0xfc,
    0xc4, 0xff, 0x31, 0x0, 0xcf, 0x80, 0x33, 0x0,
    0xc, 0xc0, 0x3, 0x30, 0x0, 0xcc, 0x0, 0x33,
    0x0, 0x3c, 0xc3, 0xf, 0x30, 0xc4, 0xcc, 0x31,
    0x33, 0xf, 0x8c, 0xc3, 0xe3, 0x30, 0xc0, 0xc3,
    0xc0,

    /* U+5357 "南" */
    0x0, 0xc0, 0x0, 0x18, 0x3, 0xff, 0xff, 0x80,
    0x60, 0x0, 0xc, 0x0, 0x7f, 0xff, 0x31, 0x2,
    0x1e, 0x20, 0x43, 0xc3, 0x30, 0x78, 0x66, 0xf,
    0x7f, 0xf9, 0xe0, 0x60, 0x3c, 0xc, 0x7, 0xbf,
    0xfc, 0xf0, 0x30, 0x1e, 0x6, 0x3, 0xc0, 0xc0,
    0x78, 0x18, 0xf0,

    /* U+6771 "東" */
    0x0, 0x40, 0x0, 0x10, 0xf, 0xff, 0xfc, 0x1,
    0x0, 0x0, 0x40, 0x7, 0xff, 0x86, 0x4, 0x19,
    0x81, 0x6, 0x7f, 0xff, 0x98, 0x10, 0x66, 0x4,
    0x18, 0x81, 0x8, 0x1f, 0xfe, 0x0, 0x7c, 0x0,
    0x1f, 0x0, 0x79, 0x38, 0x1e, 0x4e, 0x38, 0x10,
    0x70,

    /* U+897F "西" */
    0xff, 0xff, 0xc1, 0x8c, 0x0, 0x63, 0x0, 0x18,
    0xc0, 0x6, 0x30, 0xf, 0xff, 0xec, 0x63, 0xf,
    0x18, 0xc3, 0xc6, 0x30, 0xf1, 0x8c, 0x3c, 0x63,
    0x1f, 0x18, 0xc7, 0xf8, 0xe, 0xf0, 0x0, 0x3c,
    0x0, 0xf, 0x0, 0x3, 0xc0, 0x0, 0xcf, 0xff,
    0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 320, .box_w = 19, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 320, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 320, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x40, 0x145a, 0x3668
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 21271, .range_length = 13929, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t ui_font_windymed = {
#else
lv_font_t ui_font_windymed = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_WINDYMED*/

