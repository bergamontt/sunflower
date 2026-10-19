add_library(gui STATIC)
    
target_sources(
    gui
    PUBLIC
        mainwindow.h
    PRIVATE
        mainwindow.cpp
        mainwindow.ui

        analytics_widget/analyticswidget.h
        analytics_widget/analyticswidget.cpp
        analytics_widget/analyticswidget.ui

        block_widget/blockwidget.h
        block_widget/blockwidget.cpp
        block_widget/blockwidget.ui

        settings_widget/settingswidget.h
        settings_widget/settingswidget.cpp
        settings_widget/settingswidget.ui
)   

target_include_directories(
    gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/analytics_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/block_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/settings_widget
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