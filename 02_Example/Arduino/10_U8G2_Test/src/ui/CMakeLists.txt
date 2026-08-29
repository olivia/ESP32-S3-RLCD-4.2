SET(SOURCES ui_comp_bar.c
    ui_comp_blicon.c
    ui_comp_player.c
    ui_comp.c
    ui_Screen1.c
    ui_Screen2.c
    ui_theme_manager.c
    ui_themes.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_buttoncorner6x6tl_png.c
    ui_img_buttoncorner6x6tr_png.c
    ui_img_buttoncorner6x6_png.c
    ui_img_buttoncorner6x6br_png.c
    ui_img_leftarrow_png.c
    ui_img_rightarrow_png.c
    ui_img_rightarrow_invert_png.c
    fonts/ui_font_windylg.c
    fonts/ui_font_windymed.c)

add_library(ui ${SOURCES})
