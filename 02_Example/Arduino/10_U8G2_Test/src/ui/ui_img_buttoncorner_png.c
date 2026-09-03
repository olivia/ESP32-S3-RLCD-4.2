#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMAGE_UI_IMG_BUTTONCORNER_PNG
#define LV_ATTRIBUTE_IMAGE_UI_IMG_BUTTONCORNER_PNG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_UI_IMG_BUTTONCORNER_PNG uint8_t ui_img_buttoncorner_png_map[] = {
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x1f, 0x80, 
  0x1f, 0x80, 
  0x1f, 0x80, 
  0xe3, 0x80, 
  0xe3, 0x80, 
  0xe3, 0x80, 
  0x1c, 0x00, 
  0x1c, 0x00, 
  0x1c, 0x00, 
};

const lv_image_dsc_t ui_img_buttoncorner_png = {
  .header.cf = LV_COLOR_FORMAT_I1,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.w = 9,
  .header.h = 9,
  .data_size = 26,
  .data = ui_img_buttoncorner_png_map,
};
