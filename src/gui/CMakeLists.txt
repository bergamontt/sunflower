add_library(gui STATIC)
    
target_sources(gui PUBLIC
    main_window.h
    main_window.cpp
)

target_include_directories(
    gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    gui 
    PUBLIC 
        Qt6::Widgets
    PRIVATE
        Qt6::Svg
)

qt_add_resources(gui "gui"
    PREFIX "/gui"
    BASE "resources"
    FILES resources/sunflower.svg
)