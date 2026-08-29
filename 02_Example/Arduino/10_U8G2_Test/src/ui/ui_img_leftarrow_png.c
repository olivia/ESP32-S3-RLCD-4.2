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

#ifndef LV_ATTRIBUTE_IMAGE_UI_IMG_LEFTARROW_PNG
#define LV_ATTRIBUTE_IMAGE_UI_IMG_LEFTARROW_PNG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_UI_IMG_LEFTARROW_PNG uint8_t ui_img_leftarrow_png_map[] = {
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 
  0x00, 0x00, 
  0x01, 0xe0, 
  0x01, 0xe0, 
  0x07, 0xe0, 
  0x07, 0xe0, 
  0x1f, 0xe0, 
  0x1f, 0xe0, 
  0x07, 0xe0, 
  0x07, 0xe0, 
  0x01, 0xe0, 
  0x01, 0xe0, 
  0x00, 0x00, 
  0x00, 0x00, 
};

const lv_image_dsc_t ui_img_leftarrow_png = {
  .header.cf = LV_COLOR_FORMAT_I1,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.w = 14,
  .header.h = 14,
  .data_size = 36,
  .data = ui_img_leftarrow_png_map,
};
