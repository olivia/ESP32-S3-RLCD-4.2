idf_component_register(
    SRCS 
    "display_bsp.cpp" 
    PRIV_REQUIRES 
    driver
    esp_lcd
    esp_timer 
    INCLUDE_DIRS 
    "./")

target_compile_options(${COMPONENT_LIB} PRIVATE "-fpermissive")