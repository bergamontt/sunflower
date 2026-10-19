add_library(gui STATIC)
    
target_sources(
    gui
    PUBLIC
        mainwindow.h
    PRIVATE
        mainwindow.cpp
        mainwindow.ui

        widgets/analytics/analyticswidget.h
        widgets/analytics/analyticswidget.cpp
        widgets/analytics/analyticswidget.ui

        widgets/block/blockwidget.h
        widgets/block/blockwidget.cpp
        widgets/block/blockwidget.ui

        widgets/settings/settingswidget.h
        widgets/settings/settingswidget.cpp
        widgets/settings/settingswidget.ui
)   

target_include_directories(
    gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/analytics
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/block
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets/settings
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