SET(SOURCES ui_Screen1.c
    ui_Screen2.c
    ui_theme_manager.c
    ui_themes.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    fonts/ui_font_Font1.c)

add_library(ui ${SOURCES})
